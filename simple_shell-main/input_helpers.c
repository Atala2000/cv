#include "shell.h"

char *get_ars(char *line, int *exe_ret);
int call_ars(char **ars, char **front, int *exe_ret);
int run_ars(char **ars, char **front, int *exe_ret);
int handle_ars(int *exe_ret);
int check_ars(char **ars);

/**
 * get_ars - Gets a cmd from standard input.
 * @line: A buffer to store the cmd.
 * @exe_ret: The return value of the last executed cmd.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the stored cmd.
 */
char *get_ars(char *line, int *exe_ret)
{
	size_t n = 0;
	ssize_t read;
	char *prompt = "$ ";

	if (line)
		free(line);

	read = _getline(&line, &n, STDIN_FILENO);
	if (read == -1)
		return (NULL);
	if (read == 1)
	{
		hist++;
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 2);
		return (get_ars(line, exe_ret));
	}

	line[read - 1] = '\0';
	variable_replacement(&line, exe_ret);
	handle_line(&line, read);

	return (line);
}

/**
 * call_ars - Partitions operators from cmds and calls them.
 * @ars: An array of arguments.
 * @front: A double pointer to the beginning of ars.
 * @exe_ret: The return value of the parent process' last executed cmd.
 *
 * Return: The return value of the last executed cmd.
 */
int call_ars(char **ars, char **front, int *exe_ret)
{
	int ret, index;

	if (!ars[0])
		return (*exe_ret);
	for (index = 0; ars[index]; index++)
	{
		if (_strncmp(ars[index], "||", 2) == 0)
		{
			free(ars[index]);
			ars[index] = NULL;
			ars = replace_aliases(ars);
			ret = run_ars(ars, front, exe_ret);
			if (*exe_ret != 0)
			{
				ars = &ars[++index];
				index = 0;
			}
			else
			{
				for (index++; ars[index]; index++)
					free(ars[index]);
				return (ret);
			}
		}
		else if (_strncmp(ars[index], "&&", 2) == 0)
		{
			free(ars[index]);
			ars[index] = NULL;
			ars = replace_aliases(ars);
			ret = run_ars(ars, front, exe_ret);
			if (*exe_ret == 0)
			{
				ars = &ars[++index];
				index = 0;
			}
			else
			{
				for (index++; ars[index]; index++)
					free(ars[index]);
				return (ret);
			}
		}
	}
	ars = replace_aliases(ars);
	ret = run_ars(ars, front, exe_ret);
	return (ret);
}

/**
 * run_ars - Calls the execution of a cmd.
 * @ars: An array of arguments.
 * @front: A double pointer to the beginning of ars.
 * @exe_ret: The return value of the parent process' last executed cmd.
 *
 * Return: The return value of the last executed cmd.
 */
int run_ars(char **ars, char **front, int *exe_ret)
{
	int ret, i;
	int (*builtin)(char **ars, char **front);

	builtin = get_builtin(ars[0]);

	if (builtin)
	{
		ret = builtin(ars + 1, front);
		if (ret != EXIT)
			*exe_ret = ret;
	}
	else
	{
		*exe_ret = execute(ars, front);
		ret = *exe_ret;
	}

	hist++;

	for (i = 0; ars[i]; i++)
		free(ars[i]);

	return (ret);
}

/**
 * handle_ars - Gets, calls, and runs the execution of a cmd.
 * @exe_ret: The return value of the parent process' last executed cmd.
 *
 * Return: If an end-of-file is read - END_OF_FILE (-2).
 *         If the input cannot be tokenized - -1.
 *         O/w - The exit value of the last executed cmd.
 */
int handle_ars(int *exe_ret)
{
	int ret = 0, index;
	char **ars, *line = NULL, **front;

	line = get_ars(line, exe_ret);
	if (!line)
		return (END_OF_FILE);

	ars = _strtok(line, " ");
	free(line);
	if (!ars)
		return (ret);
	if (check_ars(ars) != 0)
	{
		*exe_ret = 2;
		free_ars(ars, ars);
		return (*exe_ret);
	}
	front = ars;

	for (index = 0; ars[index]; index++)
	{
		if (_strncmp(ars[index], ";", 1) == 0)
		{
			free(ars[index]);
			ars[index] = NULL;
			ret = call_ars(ars, front, exe_ret);
			ars = &ars[++index];
			index = 0;
		}
	}
	if (ars)
		ret = call_ars(ars, front, exe_ret);

	free(front);
	return (ret);
}

/**
 * check_ars - Checks if there are any leading ';', ';;', '&&', or '||'.
 * @ars: 2D pointer to tokenized cmds and arguments.
 *
 * Return: If a ';', '&&', or '||' is placed at an invalid position - 2.
 *	   Otherwise - 0.
 */
int check_ars(char **ars)
{
	size_t i;
	char *cur, *nex;

	for (i = 0; ars[i]; i++)
	{
		cur = ars[i];
		if (cur[0] == ';' || cur[0] == '&' || cur[0] == '|')
		{
			if (i == 0 || cur[1] == ';')
				return (create_error(&ars[i], 2));
			nex = ars[i + 1];
			if (nex && (nex[0] == ';' || nex[0] == '&' || nex[0] == '|'))
				return (create_error(&ars[i + 1], 2));
		}
	}
	return (0);
}
