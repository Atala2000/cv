#include "shell.h"

/**
 * allocate_buffer - memory allocation
 * @buf_size: memory size
 * Return: mem adress
 */
char *allocate_buffer(size_t buf_size)
{
	char *buf = (char *) malloc(buf_size);

	if (buf == NULL)
	{
		errno = ENOMEM;
		return (NULL);
	}
	return (buf);
}

/**
 * expand_buffer - memeory is increased
 * @buf_size: memory size
 * @buf: pointer
 * Return:  memory address
 */
char *expand_buffer(char *buf, size_t buf_size)
{
	char *newBuf = (char *) my_realloc(buf, buf_size);

	buf_size *= 2;
	if (newBuf == NULL)
	{
		free(buf);
		errno = ENOMEM;
		return (NULL); 
	}
	return (newBuf);
}

/**
 * is_empty_line - empty line passed
 * @len: length of string
 * @buf: pointer
 * Return: mem adress
 **/
int is_empty_line(ssize_t len, char *buf)
{
	return (len == 0 || (len == 1 && buf[0] == '\n'));
}

/**
 * handle_empty_line -  empty line
 * @lineptr: double pointer
 * @buf: pointer memory
 * Return: -1
 */
int handle_empty_line(char *buf, char **lineptr)
{
	free(buf);
	*lineptr = NULL;
	return (-1);
}

/**
 * terminate_buffer - terminates
 * @len: length of string
 * @buf: pointer to memory
 */
void terminate_buffer(ssize_t len, char *buf)
{
	buf[len] = '\0';
}
