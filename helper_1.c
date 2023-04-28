#include "shell.h"

/**
 * read_input - read_input
 * Return: return
 */
char *read_input()
{
	char *input = NULL;
	size_t input_size = 0;

	if (getline(&input, &input_size, stdin) == -1)
	{
		free(input);
		return (NULL);
	}
	return (input);
}

/**
 * printString - wstdin recieves text
 * @str: str
 */
void printString(char *str)
{
	size_t len = getStringLength(str);

	write(STDOUT_FILENO, str, len);
}

/**
 * getStringLength -  strLwngth
 * @str: str
 * Return: return
 */
int getStringLength(const char *str)
{
	int length = 0;

	while (*str != '\0')
	{
		length++;
		str++;
	}
	return (length);
}

/**
 * writeStringToStderr - wstd
 * @str: Error
 */
void writeStringToStderr(char *str)
{
	size_t len = getStringLength(str);

	write(STDERR_FILENO, str, len);
}

/**
 * my_strcmp - compares two strings
 * @str1: s1
 * @str2: s2
 * Return: return
 **/
int my_strcmp(const char *str1, const char *str2)
{
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
