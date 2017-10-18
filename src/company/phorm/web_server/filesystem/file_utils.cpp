/*
 * file_utils.cpp
 *
 *  Created on: 17.10.2010
 *      Author: knight
 */

#include "file_utils.h"

namespace filesystem
{

	/** получить размер файла */
	int get_file_size(const char * fileName)
	{
		int file_size = -1;
		struct stat st;
		if (!stat(fileName, &st))
			{   file_size = st.st_size;   }
		return file_size;
	}

}
