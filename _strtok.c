#include "shell.h"

/**
 * is_delim - delimiters 
 * @c: chars 
 * @delim: charachter
 * Return: 0 or -1
 */
unsigned int is_delim(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}

/**
 * my_strtok - clone 
 * @srcString: string
 * @delim: delimiter
 * Return: 0 or -1
 */
char *my_strtok(char *srcString, char *delim)
{
	static char *backup_string;
	char *ret;

	if (!srcString)
	{
		srcString = backup_string;
	}
	if (!srcString)
	{
		return (NULL);
	}
	while (1)
	{
		if (is_delim(*srcString, delim))
		{
			srcString++;
			continue;
		}
		if (*srcString == '\0')
		{
			return (NULL);
		}
		break;
	}
	ret = srcString;
	while (1)
	{
		if (*srcString == '\0')
		{
			backup_string = srcString;
			return (ret);
		}
		if (is_delim(*srcString, delim))
		{
			*srcString = '\0';
			backup_string = srcString + 1;
			return (ret);
		}
		srcString++;
	}
}



