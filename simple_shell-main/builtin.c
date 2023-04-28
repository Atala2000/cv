#include "shell.h"
int (*get_builtin(char *cmd))(char **ars, char **front);
int my_exit(char **ars, char **front);
int my_cd(char **ars, char __attribute__((__unused__)) **front);
int my_help(char **ars, char __attribute__((__unused__)) **front);

/**
 * get_builtin - Matches a cmd with a corresponding
 *               my builtin function.
 * @cmd: The cmd to match.
 *
 * Return: A function pointer to the corresponding builtin.
 */
int (*get_builtin(char *cmd))(char **ars, char **front)
{
	builtin_t funcs[] = {
		{ "exit", my_exit },
		{ "env", my_env },
		{ "setenv", my_setenv },
		{ "unsetenv", my_unsetenv },
		{ "cd", my_cd },
		{ "alias", my_alias },
		{ "help", my_help },
		{ NULL, NULL }
	};
	int i;

	for (i = 0; funcs[i].name; i++)
	{
		if (_strcmp(funcs[i].name, cmd) == 0)
			break;
	}
	return (funcs[i].f);
}

/**
 * my_exit - Causes normal process termination
 *                for the my shell.
 * @ars: An array of arguments containing the exit value.
 * @front: A double pointer to the beginning of ars.
 *
 * Return: If there are no arguments - -3.
 *         If the given exit value is invalid - 2.
 *         O/w - exits with the given status value.
 *
 * Description: Upon returning -3, the program exits back in the main function.
 */
int my_exit(char **ars, char **front)
{
	int i, len_of_int = 10;
	unsigned int num = 0, max = 1 << (sizeof(int) * 8 - 1);

	if (ars[0])
	{
		if (ars[0][0] == '+')
		{
			i = 1;
			len_of_int++;
		}
		for (; ars[0][i]; i++)
		{
			if (i <= len_of_int && ars[0][i] >= '0' && ars[0][i] <= '9')
				num = (num * 10) + (ars[0][i] - '0');
			else
				return (create_error(--ars, 2));
		}
	}
	else
	{
		return (-3);
	}
	if (num > max - 1)
		return (create_error(--ars, 2));
	ars -= 1;
	free_ars(ars, front);
	free_env();
	free_al_li(aliases);
	exit(num);
}

/**
 * my_cd - Changes the current directory of the my process.
 * @ars: An array of arguments.
 * @front: A double pointer to the beginning of ars.
 *
 * Return: If the given string is not a directory - 2.
 *         If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_cd(char **ars, char __attribute__((__unused__)) **front)
{
	char **dir_info, *new_line = "\n";
	char *oldpwd = NULL, *pwd = NULL;
	struct stat dir;

	oldpwd = getcwd(oldpwd, 0);
	if (!oldpwd)
		return (-1);

	if (ars[0])
	{
		if (*(ars[0]) == '-' || _strcmp(ars[0], "--") == 0)
		{
			if ((ars[0][1] == '-' && ars[0][2] == '\0') ||
					ars[0][1] == '\0')
			{
				if (_getenv("OLDPWD") != NULL)
					(chdir(*_getenv("OLDPWD") + 7));
			}
			else
			{
				free(oldpwd);
				return (create_error(ars, 2));
			}
		}
		else
		{
			if (stat(ars[0], &dir) == 0 && S_ISDIR(dir.st_mode)
					&& ((dir.st_mode & S_IXUSR) != 0))
				chdir(ars[0]);
			else
			{
				free(oldpwd);
				return (create_error(ars, 2));
			}
		}
	}
	else
	{
		if (_getenv("HOME") != NULL)
			chdir(*(_getenv("HOME")) + 5);
	}

	pwd = getcwd(pwd, 0);
	if (!pwd)
		return (-1);

	dir_info = malloc(sizeof(char *) * 2);
	if (!dir_info)
		return (-1);

	dir_info[0] = "OLDPWD";
	dir_info[1] = oldpwd;
	if (my_setenv(dir_info, dir_info) == -1)
		return (-1);

	dir_info[0] = "PWD";
	dir_info[1] = pwd;
	if (my_setenv(dir_info, dir_info) == -1)
		return (-1);
	if (ars[0] && ars[0][0] == '-' && ars[0][1] != '-')
	{
		write(STDOUT_FILENO, pwd, _strlen(pwd));
		write(STDOUT_FILENO, new_line, 1);
	}
	free(oldpwd);
	free(pwd);
	free(dir_info);
	return (0);
}

/**
 * my_help - Displays information about my builtin cmds.
 * @ars: An array of arguments.
 * @front: A pointer to the beginning of ars.
 *
 * Return: If an error occurs - -1.
 *         Otherwise - 0.
 */
int my_help(char **ars, char __attribute__((__unused__)) **front)
{
	if (!ars[0])
		help_all();
	else if (_strcmp(ars[0], "alias") == 0)
		help_alias();
	else if (_strcmp(ars[0], "cd") == 0)
		help_cd();
	else if (_strcmp(ars[0], "exit") == 0)
		help_exit();
	else if (_strcmp(ars[0], "env") == 0)
		help_env();
	else if (_strcmp(ars[0], "setenv") == 0)
		help_setenv();
	else if (_strcmp(ars[0], "unsetenv") == 0)
		help_unsetenv();
	else if (_strcmp(ars[0], "help") == 0)
		help_help();
	else
		write(STDERR_FILENO, name, _strlen(name));

	return (0);
}
