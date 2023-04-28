#include "shell.h"

/**
 * file_input -  file input
 * @argc: argc
 * @argv: argv
 * Return: 0 on success
 */
int file_input(int argc, char **argv)
{
	char *input = NULL;        
	char *tokens[MAX_NUM_TOKENS];   
	int num_tokens;
	size_t input_size = 0;
	FILE *file;

	if (argc != 2)
	{
		char error_message[] = "Usage: ";

		write(STDERR_FILENO, error_message, sizeof(error_message) - 1);
		write(STDERR_FILENO, argv[0], strlen(argv[0]));
		write(STDERR_FILENO, " filename\n", 10);
		exit(1);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		perror("fopen");
		exit(1);
	}

	while (getline(&input, &input_size, file) != -1)
	{
		num_tokens = tokenize(input, tokens, MAX_NUM_TOKENS);
		if (num_tokens > 0) 
		{
			execute(tokens); 
		}
	}
	free(input);
	fclose(file);
	return (0);
}
