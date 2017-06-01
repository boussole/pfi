/*
 * Develop your version of the ls utility. Only the ’ls -l’ functionality is needed.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <grp.h>
#include <linux/limits.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define PERM_STRING_LEN (sizeof("-rwxrwxrwx"))

static const char *app = NULL;

void usage(int err, const char *msg)
{
	if (msg)
		fprintf(stderr, KRED"Error: %s (%d)\n"KNRM, msg, err);

	fprintf(stderr, "Usage: ls [FILE]\n");
	exit(err);
}

const char * permissions_to_string(struct stat *st, char *perm_string)
{
	static const unsigned int perm[] = {
		S_IRUSR, S_IWUSR, S_IXUSR,
		S_IRGRP, S_IWGRP, S_IXGRP,
		S_IROTH, S_IWOTH, S_IXOTH
	};

	static const char perm_char[] = "rwxrwxrwx";

	static const int len = sizeof(perm) / sizeof(perm[0]);

	memset(perm_string, '-', PERM_STRING_LEN - 1);
	perm_string[0] = '?';
	perm_string[PERM_STRING_LEN - 1] = 0;

	const char *color = KNRM;
	if (S_ISDIR(st->st_mode)) {
		perm_string[0] = 'd';
		color = KCYN;
	}
	else if (S_ISCHR(st->st_mode))
		perm_string[0] = 'c';
	else if (S_ISBLK(st->st_mode))
		perm_string[0] = 'b';
	else if (S_ISREG(st->st_mode))
		perm_string[0] = '-';
	else if (S_ISFIFO(st->st_mode))
		perm_string[0] = 'f';
	else if (S_ISLNK(st->st_mode)) {
		perm_string[0] = 'l';
		color = KGRN;
	}
	else if (S_ISSOCK(st->st_mode))
		perm_string[0] = 's';

	for (int i = 0; i < len; ++i) {
		if ((st->st_mode & perm[i]) == perm[i])
			perm_string[i + 1] = perm_char[i];
	}

	if (S_ISREG(st->st_mode) && (st->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)))
		color = KYEL;

	return color;
}

void print_unstated_dentry(const char *name, unsigned int d_type)
{
	const char *color = KNRM;
	char type;
	switch (d_type) {
	case (DT_BLK):
		type = 'b';
		break;
	case (DT_CHR):
		type = 'c';
		break;
	case (DT_DIR):
		type = 'd';
		color = KCYN;
		break;
	case (DT_FIFO):
		type = 'f';
		break;
	case (DT_LNK):
		type = 'l';
		color = KGRN;
		break;
	case (DT_REG):
		type = '-';
		break;
	case (DT_SOCK):
		type = 's';
		break;
	default:
		type = '?';
		break;
	}

	printf("%c????????? ? ? ? 0 0 0 00:00 %s%s\n"KNRM, type, color, name);
}

void print_stated_dentry(int fd, const char *name, struct stat *st)
{
	struct tm *tm = localtime(&st->st_mtim.tv_sec);
	char time_str[128];
	strftime(time_str, sizeof(time_str), "%x %X", tm);

	char *usr_name, *grp_name;

	char uid_str[128];
	snprintf(uid_str, sizeof(uid_str), "%d", st->st_uid);
	usr_name = uid_str;

	struct passwd *passwd = getpwuid(st->st_uid);
	if (passwd)
		usr_name = passwd->pw_name;

	char gid_str[128];
	snprintf(gid_str, sizeof(gid_str), "%d", st->st_gid);
	grp_name = gid_str;

	struct group *grp = getgrgid(st->st_gid);
	if (grp)
		grp_name = grp->gr_name;

	char perm[PERM_STRING_LEN];
	const char *color = permissions_to_string(st, perm);

	char link_path[PATH_MAX];
	if (S_ISLNK(st->st_mode) && (readlinkat(fd, name, link_path, sizeof(link_path)) > 0))
		printf("%s %lu\t%s\t%s\t%lu\t%s %s%s -> %s\n"KNRM, perm, st->st_nlink, usr_name, grp_name, st->st_size, time_str, color, name, link_path);
	else
		printf("%s %lu\t%s\t%s\t%lu\t%s %s%s\n"KNRM, perm, st->st_nlink, usr_name, grp_name, st->st_size, time_str, color, name);
}

int list_dir(int fd, const char *path)
{
	int r = 0;
	struct stat st;

	DIR *d = fdopendir(fd);
	if (!d) {
		r = errno;
		if (r != ENOTDIR)
			fprintf(stderr, KRED"%s: cannot open directory: %s (%d)\n"KNRM, app, strerror(r), r);
		else {
			if ((r = fstat(fd, &st)) == 0)
				print_stated_dentry(fd, path, &st);
			else
				print_unstated_dentry(path, DT_WHT);
		}
		goto out;
	}

	struct dirent entry;
	struct dirent *res = NULL;
	for (r = readdir_r(d, &entry, &res); r == 0 && res != NULL; r = readdir_r(d, &entry, &res)) {
		if (entry.d_name[0] == '.') {
			/* skip ".", ".." and hidden dentries, `ls -l` doesn't show them */
			continue;
		}

		if (fstatat(fd, entry.d_name, &st, AT_SYMLINK_NOFOLLOW) == 0)
			print_stated_dentry(fd, entry.d_name, &st);
		else
			print_unstated_dentry(entry.d_name, entry.d_type);
	}

	if (r) {
		fprintf(stderr, KRED"%s: cannot read directory: %s (%d)\n"KNRM, app, strerror(r), r);
		goto out;
	}

out:
	if (d)
		closedir(d);

	return r;
}

int main(int argc, char **argv)
{
	int r = EXIT_SUCCESS;

	if (argc > 2)
		usage(EXIT_FAILURE, NULL);

	app = strrchr(*argv, '/');
	if (!app)
		app = *argv;
	else
		++app;

	int fd = -1;
	const char *path = argv[1];
	if (argc == 1)
		path = ".";

	/* yes, it might be not a path in the current dir, but openat works like usual open in that case*/
	fd = openat(AT_FDCWD, path, 0, O_RDONLY);
	if (fd < 0) {
		r = errno;
		fprintf(stderr, KRED"%s: cannot open directory '%s': %s (%d)\n"KNRM, app, argv[1], strerror(r), r);
		goto out;
	}

	r = list_dir(fd, path);

out:
	if (fd > -1)
		close(fd);

	return r;
}



