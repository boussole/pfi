/*
 * file_utils.h
 *
 * Утилиты для работы с файловой системой
 *
 *  Created on: 17.10.2010
 *      Author: knight
 */

#ifndef FILE_UTILS_H_
#define FILE_UTILS_H_

//-
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
//-
//-

namespace filesystem
{

	/** получить размер файла */
	int get_file_size(const char * fileName);

} /** namespace */

#endif /* FILE_UTILS_H_ */
