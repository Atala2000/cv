#ifndef _SHELL_H_
#define _SHELL_H_
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>

#define END_OF_FILE -2
#define EXIT -3

/* Global environemnt */
extern char **environ;
/* Global program name */
char *name;
/* Global history counter */
int hist;

/**
 * struct list_s - A new struct type defining a linked list.
 * @dir: A directory path.
 * @next: A pointer to another struct list_s.
 */
typedef struct list_s
{
	char *dir;
	struct list_s *next;
} list_t;

/**
 * struct builtin_s - A new struct type defining builtin cmds.
 * @name: The name of the builtin cmd.
 * @f: A function pointer to the builtin cmd's function.
 */
typedef struct builtin_s
{
	char *name;
	int (*f)(char **argv, char **front);
} builtin_t;

/**
 * struct alias_s - A new struct defining aliases.
 * @name: The name of the alias.
 * @value: The value of the alias.
 * @next: A pointer to another struct alias_s.
 */
typedef struct alias_s
{
	char *name;
	char *value;
	struct alias_s *next;
} alias_t;

/* Global aliases linked list */
alias_t *aliases;

/* Main Helpers */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char **_strtok(char *line, char *delim);
char *get_location(char *cmd);
list_t *get_path_dir(char *path);
int execute(char **ars, char **front);
void free_list(list_t *head);
char *_itoa(int num);

/* Input Helpers */
voidhl_lin(char **line, ssize_t read);
void variable_replacement(char **ars, int *exe_ret);
char *get_ars(char *line, int *exe_ret);
int call_ars(char **ars, char **front, int *exe_ret);
int run_ars(char **ars, char **front, int *exe_ret);
int handle_ars(int *exe_ret);
int check_ars(char **ars);
void free_ars(char **ars, char **front);
char **replace_aliases(char **ars);

/* String functions */
int _strlen(const char *s);
char *_strcat(char *dest, const char *src);
char *_strncat(char *dest, const char *src, size_t n);
char *_strcpy(char *dest, const char *src);
char *_strchr(char *s, char c);
int _strspn(char *s, char *accept);
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);

/* Builtins */
int (*get_builtin(char *cmd))(char **ars, char **front);
int my_exit(char **ars, char **front);
int my_env(char **ars, char __attribute__((__unused__)) **front);
int my_setenv(char **ars, char __attribute__((__unused__)) **front);
int my_unsetenv(char **ars, char __attribute__((__unused__)) **front);
int my_cd(char **ars, char __attribute__((__unused__)) **front);
int my_alias(char **ars, char __attribute__((__unused__)) **front);
int my_help(char **ars, char __attribute__((__unused__)) **front);

/* Builtin Helpers */
char **_copyenv(void);
void free_env(void);
char **_getenv(const char *var);

/* Error Handling */
int create_error(char **ars, int err);
char *error_env(char **ars);
char *error_1(char **ars);
char *error_2_exit(char **ars);
char *error_2_cd(char **ars);
char *error_2_syntax(char **ars);
char *error_126(char **ars);
char *error_127(char **ars);

/* Linkedlist Helpers */
alias_t *add_alias_nd(alias_t **head, char *name, char *value);
void free_al_li(alias_t *head);
list_t *add_nd_d(list_t **head, char *dir);
void free_list(list_t *head);

void help_all(void);
void help_alias(void);
void help_cd(void);
void help_exit(void);
void help_help(void);
void help_env(void);
void help_setenv(void);
void help_unsetenv(void);
void help_history(void);

int prfil_cmd(char *file_path, int *exe_ret);
#endif /* _SHELL_H_ */
