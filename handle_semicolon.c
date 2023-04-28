#include "shell.h"

/**
 * handle_semicolon - ";" separator
 * @input: input string
 */
void handle_semicolon(char *input)
{
	char *commands[MAX_ARGS];
	char *args[MAX_ARGS];
	pid_t pid;
	int j, status;

	delim_tokenize(input, commands, MAX_NUM_TOKENS, ";");

	/* Execute each command in sequence */
	for (j = 0; commands[j] != NULL; j++)
	{
		delim_tokenize(commands[j], args, MAX_NUM_TOKENS, " \t\n");
		if (args[0] != NULL)
		{
			pid = fork();
			if (pid == 0)
			{
				execute(args);
				exit(0);
			}
			else if (pid < 0)
			{
				perror("fork failed");
				exit(1);
			}
			else
			{
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));

			}
		}
	}
}

/**
 * delim_tokenize - breaks a string i
 * @input: input string
 * @tokens: tok
 * @max_tokens: max_tok
 * @delim: delim
 * Return: return
 */
int delim_tokenize(char *input, char **tokens, int max_tokens, char *delim)
{
	int num_tokens = 0;
	char *token = strtok(input, delim);

	while (token != NULL && num_tokens < max_tokens)
	{
		tokens[num_tokens] = token;
		num_tokens++;
		token = strtok(NULL, delim);
	tokens[num_tokens] = NULL;
	return (num_tokens);
	}
}


