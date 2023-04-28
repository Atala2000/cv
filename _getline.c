#include "shell.h"
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>


#define INIT_BUF_SIZE 128

/**
 * my_getline - gets the string
 * @lineptr: buffer for strings
 * @n: buffer size
 * @fd: it contains a value that the string reads from
 *
 * Return: -1 or number of char's read
 */
ssize_t my_getline(char **lineptr, size_t *n, int fd)
{
	ssize_t len = 0;
	size_t buf_size = *n;
	char *buf = *lineptr;
	char c = 0;

	if (lineptr == NULL || n == NULL)
	{
		errno = EINVAL;
		return (-1);
	}
	if (buf == NULL)
	{
		buf_size = INIT_BUF_SIZE;
		buf = allocate_buffer(buf_size);
		if (buf == NULL)
		return (-1);
		*lineptr = buf;
	}
	while (read(fd, &c, 1) > 0)
	{
		if (len + 1 >= (ssize_t)buf_size)
		{
			char *newBuf = expand_buffer(buf, buf_size);

			if (newBuf == NULL)
			return (-1);
			buf = newBuf;
			*lineptr = buf;
			buf_size *= 2;
		}
		buf[len++] = c;
		if (c == '\n')
			break;
	}
	if (is_empty_line(len, buf))
		return (handle_empty_line(buf, lineptr));
	terminate_buffer(len, buf);
	return (len);
}




