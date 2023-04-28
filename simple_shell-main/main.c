#include "shell.h"

void signal_handler(int signal);
int execute(char **ars, char **front);

/**
 * signal_handler - Prints a new prompt upon a signal.
 * @sig: The signal.
 */
void signal_handler(int signal)
{
	char *new_prompt = "\n$ ";

	(void)signal;
	signal(SIGINT, signal_handler);
	write(STDIN_FILENO, new_prompt, 3);
}

/**
 * execute - Executes a cmd in a child process.
 * @ars: An array of arguments.
 * @front: A double pointer to the beginning of ars.
 *
 * Return: If an error occurs - a corresponding error code.
 *         O/w - The exit value of the last executed cmd.
 */
int execute(char **ars, char **front)
{
	pid_t child_pid;
	int status, flag = 0, ret = 0;
	char *cmd = ars[0];

	if (cmd[0] != '/' && cmd[0] != '.')
	{
		flag = 1;
		cmd = get_location(cmd);
	}

	if (!cmd || (access(cmd, F_OK) == -1))
	{
		if (errno == EACCES)
			ret = (create_error(ars, 126));
		else
			ret = (create_error(ars, 127));
	}
	else
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			if (flag)
				free(cmd);
			perror("Error child:");
			return (1);
		}
		if (child_pid == 0)
		{
			execve(cmd, ars, environ);
			if (errno == EACCES)
				ret = (create_error(ars, 126));
			free_env();
			free_ars(ars, front);
			free_al_li(aliases);
			_exit(ret);
		}
		else
		{
			wait(&status);
			ret = WEXITSTATUS(status);
		}
	}
	if (flag)
		free(cmd);
	return (ret);
}

/**
 * main - Runs a simple UNIX cmd interpreter.
 * @argc: The number of arguments supplied to the program.
 * @argv: An array of pointers to the arguments.
 *
 * Return: The return value of the last executed cmd.
 */
int main(int argc, char *argv[])
{
	int ret = 0, retn;
	int *exe_ret = &retn;
	char *prompt = "$ ", *new_line = "\n";

	name = argv[0];
	hist = 1;
	aliases = NULL;
	signal(SIGINT, signal_handler);

	*exe_ret = 0;
	environ = _copyenv();
	if (!environ)
		exit(-100);

	if (argc != 1)
	{
		ret = prfil_cmd(argv[1], exe_ret);
		free_env();
		free_al_li(aliases);
		return (*exe_ret);
	}

	if (!isatty(STDIN_FILENO))
	{
		while (ret != END_OF_FILE && ret != EXIT)
			ret = handle_ars(exe_ret);
		free_env();
		free_al_li(aliases);
		return (*exe_ret);
	}

	while (1)
	{
		write(STDOUT_FILENO, prompt, 2);
		ret = handle_ars(exe_ret);
		if (ret == END_OF_FILE || ret == EXIT)
		{
			if (ret == END_OF_FILE)
				write(STDOUT_FILENO, new_line, 1);
			free_env();
			free_al_li(aliases);
			exit(*exe_ret);
		}
	}

	free_env();
	free_al_li(aliases);
	return (*exe_ret);
}
