/*
  Write linux kernel module, which writes time to a file '/tmp/current_time' every minute
  in a format hh:mm (i.e., 11:58 or 22:07)
 */

#define pr_fmt(fmt) "time_logger: "fmt

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/time.h>
#include <linux/syscalls.h>
#include <linux/file.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <asm/uaccess.h>

MODULE_LICENSE("GPL");

#define LOGGER_INTERVAL_SEC (60)

static struct task_struct *time_logger_task = NULL;
static int stop = 0;

/**
 * Based on
 * http://www.linuxjournal.com/article/8110?page=0,0
 */
static ssize_t write_file(char *filename, char *data)
{
	int r;
	struct file *file;
	loff_t pos = 0;

	mm_segment_t old_fs = get_fs();
	set_fs(KERNEL_DS);

	file = filp_open(filename, O_WRONLY|O_CREAT|O_APPEND, 0644);
	if (IS_ERR(file)) {
		r = PTR_ERR(file);
		pr_err("open failed: %d", r);
		goto out;
	}

	r = vfs_write(file, data, strlen(data), &pos);

	filp_close(file, NULL);

out:
	set_fs(old_fs);

	return r;
}

static int time_logger_fn(void *data)
{
	int r = 0;
	struct timeval tv;
	struct tm tm;
	char time_buf[sizeof("23:59\n")];

	allow_signal(SIGUSR1);

	while (!ACCESS_ONCE(stop)) {
		do_gettimeofday(&tv);
		time_to_tm(tv.tv_sec, sys_tz.tz_minuteswest * 60, &tm);

		sprintf(time_buf, "%02d:%02d\n", tm.tm_hour, tm.tm_min);

		if ((r = write_file("/tmp/current_time", time_buf)) != sizeof(time_buf) - 1) {
			if (r >= 0)
				r = -ENOSPC;

			pr_err("time writing failed: %d", r);
		}

		msleep_interruptible(LOGGER_INTERVAL_SEC * 1000);
	}

	return r;
}

int __init init_time_logger(void)
{
	time_logger_task = kthread_run(time_logger_fn, NULL, "time_logger");

	if (IS_ERR(time_logger_task))
		pr_info("failed to start");
	else
		pr_info("started");

	return PTR_ERR_OR_ZERO(time_logger_task);
}

void __exit cleanup_time_logger(void)
{
	ACCESS_ONCE(stop) = 1;
	send_sig(SIGUSR1, time_logger_task, 0);
	kthread_stop(time_logger_task);

	pr_info("stopped");
}

module_init(init_time_logger);
module_exit(cleanup_time_logger);

