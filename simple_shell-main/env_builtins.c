#include "shell.h"

int my_env(char **ars, char __attribute__((__unused__)) **front);
int my_setenv(char **ars, char __attribute__((__unused__)) **front);
int my_unsetenv(char **ars, char __attribute__((__unused__)) **front);

/**
 * my_env - Prints the current environment.
 * @ars: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of ars.
 *
 * Return: If an error occurs - -1.
 *	   Otherwise - 0.
 *
 * Description: Prints one variable per line in the
 *              format 'variable'='value'.
 */
int my_env(char **ars, char __attribute__((__unused__)) **front)
{
	int index;
	char nc = '\n';

	if (!environ)
		return (-1);

	for (index = 0; environ[index]; index++)
	{
		write(STDOUT_FILENO, environ[index], _strlen(environ[index]));
		write(STDOUT_FILENO, &nc, 1);
	}

	(void)ars;
	return (0);
}

/**
 * my_setenv - Changes or adds an environmental variable to the PATH.
 * @ars: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of ars.
 * Description: ars[1] is the name of the new or existing PATH variable.
 *              ars[2] is the value to set the new or changed variable to.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_setenv(char **ars, char __attribute__((__unused__)) **front)
{
	char **env_var = NULL, **new_environ, *new_value;
	size_t size;
	int index;

	if (!ars[0] || !ars[1])
		return (create_error(ars, -1));

	new_value = malloc(_strlen(ars[0]) + 1 + _strlen(ars[1]) + 1);
	if (!new_value)
		return (create_error(ars, -1));
	_strcpy(new_value, ars[0]);
	_strcat(new_value, "=");
	_strcat(new_value, ars[1]);

	env_var = _getenv(ars[0]);
	if (env_var)
	{
		free(*env_var);
		*env_var = new_value;
		return (0);
	}
	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * (size + 2));
	if (!new_environ)
	{
		free(new_value);
		return (create_error(ars, -1));
	}

	for (index = 0; environ[index]; index++)
		new_environ[index] = environ[index];

	free(environ);
	environ = new_environ;
	environ[index] = new_value;
	environ[index + 1] = NULL;

	return (0);
}

/**
 * my_unsetenv - Deletes an environmental variable from the PATH.
 * @ars: An array of arguments passed to the shell.
 * @front: A double pointer to the beginning of ars.
 * Description: ars[1] is the PATH variable to remove.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_unsetenv(char **ars, char __attribute__((__unused__)) **front)
{
	char **env_var, **new_environ;
	size_t size;
	int index, index2;

	if (!ars[0])
		return (create_error(ars, -1));
	env_var = _getenv(ars[0]);
	if (!env_var)
		return (0);

	for (size = 0; environ[size]; size++)
		;

	new_environ = malloc(sizeof(char *) * size);
	if (!new_environ)
		return (create_error(ars, -1));

	for (index = 0, index2 = 0; environ[index]; index++)
	{
		if (*env_var == environ[index])
		{
			free(*env_var);
			continue;
		}
		new_environ[index2] = environ[index];
		index2++;
	}
	free(environ);
	environ = new_environ;
	environ[size - 1] = NULL;

	return (0);
}
