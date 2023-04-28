#include "shell.h"
/**
 * free_list - lls is free
 * @head: head
 */
void free_list(LL *head)
{
	LL *temp;

	while (head != NULL)
	{
		temp = head; 
		head = head->next; 
		free(temp->str); 
		free(temp); 
	}
}
/**
 * add_node - node is added
 * @head_ref: head_ref
 * @str: str
 */
void add_node(LL **head_ref, char *str)
{
	LL *new_node = (LL *)malloc(sizeof(LL)); 

	new_node->str = str; 
	new_node->next = *head_ref; 
	*head_ref = new_node; 
}
/**
 * path_list - pathlist
 * Return: return
 */
LL *path_list(void)
{
	LL *head = NULL;
	char *path = getenv("PATH");
	char *path_copy = my_strdup(path);
	LL *node;
	char *token;

	if (!path_copy)
	{
		perror("malloc failure");
		return (NULL);
	}
	token = strtok(path_copy, ":");

	while (token != NULL)
	{
		node = malloc(sizeof(LL));
		if (!node)
		{
			perror("malloc failure");
			free_list(head);
			free(path_copy);
			return (NULL);
		}

		node->str = my_strdup(token);
		node->next = head;
		head = node;

		token = strtok(NULL, ":");
	}
	free(path_copy);

	return (head);
}
/**
 * find_executable - checker for occ of file
 * @command: command
 * @path_list: ls
 * Return: return
 */
char *find_executable(char *command, LL *path_list)
{
	char *executable_path = NULL;
	char *path = NULL;
	int command_len = getStringLength(command);
	int path_len;
	int new_len;
	char *new_path;

	while (path_list != NULL)
	{
		path = path_list->str;
		path_len = getStringLength(path);
		new_len = path_len + command_len + 2; 
		new_path = malloc(new_len * sizeof(char));
		if (new_path == NULL)
		{
			perror("malloc error");
			exit(1);
		}
		myStrcpy(new_path, path);
		myStrcat(new_path, "/");
		myStrcat(new_path, command);
		if (access(new_path, X_OK) == 0) 
		{
			executable_path = new_path;
		break;
		}
		free(new_path);
		path_list = path_list->next;
	}
	return (executable_path);
}
/**
 * _getenv - name
 * @name: name
 * Return: return
 */
char *_getenv(const char *name)
{
	int i, len; 
	char *env_val; 

	len = getStringLength(name); 

	for (i = 0; environ[i] != NULL; i++)
	{
		if (myStrncmp(name, environ[i], len) == 0 && environ[i][len] == '=')
		
		{
			env_val = &environ[i][len + 1];
		
			return (env_val);
		}
	}

	return (NULL);
}
