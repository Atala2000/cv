#include "shell.h"
/**
 * concatenateStrings - joins two strings 
 * @str1: s1
 * @str2: s2
 * Return: return
 */
char *concatenateStrings(char *str1, char *str2)
{
	int len1 = getStringLength(str1);
	int len2 = getStringLength(str2);
	char *result = malloc(len1 + len2 + 1); 

	if (result == NULL)
	{
		perror("Failed to allocate memory for concatenated string");
		exit(1);
	}
	result = myStrcpy(result, str1);
	result = myStrcat(result, str2);
	return (result);
}

/**
 * myStrcpy - cp string 
 * @dest: dest
 * @src: src
 * Return:return
 */
char *myStrcpy(char *dest, const char *src)
{
	char *originalDest = dest; 

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (originalDest);
}

/**
 * myStrcat - concatenates two strings
 * @dest: dsr
 * @src: srct
 * Return: rtrn
 */
char *myStrcat(char *dest, const char *src)
{
	char *originalDest = dest;

	while (*dest != '\0')
	{
		dest++;
	}
	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (originalDest);
}

/**
 * myStrncmp - compares two strings
 * @s1: s1
 * @s2: s2
 * @n: n
 * Return: 0 
 */
int myStrncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (*s1 == '\0' || *s1 != *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
	}
	return (0);
}
/**
 * my_strdup - memory recoeves content
 * @str: str
 * Return: return
 */
char *my_strdup(const char *str)
{
	size_t len = getStringLength(str) + 1;
	char *new_str = malloc(len);

	if (new_str == NULL)
		return (NULL);
	memcpy(new_str, str, len);
	return (new_str);
}
