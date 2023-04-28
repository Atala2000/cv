#include "shell.h"

char *error_env(char **ars);
char *error_1(char **ars);
char *error_2_exit(char **ars);
char *error_2_cd(char **ars);
char *error_2_syntax(char **ars);
/**
 * error_env - Creates an error message for my_env errors.
 * @ars: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_env(char **ars)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	ars--;
	len = _strlen(name) + _strlen(hist_str) + _strlen(ars[0]) + 45;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, ars[0]);
	_strcat(error, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (error);
}

/**
 * error_1 - Creates an error message for my_alias errors.
 * @ars: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_1(char **ars)
{
	char *error;
	int len;

	len = _strlen(name) + _strlen(ars[0]) + 13;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
		return (NULL);

	_strcpy(error, "alias: ");
	_strcat(error, ars[0]);
	_strcat(error, " not found\n");

	return (error);
}

/**
 * error_2_exit - Creates an error message for my_exit errors.
 * @ars: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_2_exit(char **ars)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(ars[0]) + 27;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": exit: Illegal number: ");
	_strcat(error, ars[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_cd - Creates an error message for my_cd errors.
 * @ars: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_2_cd(char **ars)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	if (ars[0][0] == '-')
		ars[0][2] = '\0';
	len = _strlen(name) + _strlen(hist_str) + _strlen(ars[0]) + 24;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	if (ars[0][0] == '-')
		_strcat(error, ": cd: Illegal option ");
	else
		_strcat(error, ": cd: can't cd to ");
	_strcat(error, ars[0]);
	_strcat(error, "\n");

	free(hist_str);
	return (error);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @ars: An array of arguments passed to the cmd.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **ars)
{
	char *error, *hist_str;
	int len;

	hist_str = _itoa(hist);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(ars[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, ars[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}
