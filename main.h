#ifndef MAIN
#define MAIN
/********headers********/
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdarg.h>
#include <fcntl.h>

/********defines********/
#define MAX_PTR_SIZE 64
#define CMP2_CONDITION 1
#define STAT_CONDITION 2
#define CMP_CONDITION 4
#define OP_COUNT 4
#define BUFFSIZE 128
#define COMMENT_MARKER '#'
#define NULL_TERMINATOR '\0'
#define SPECIAL_VAR_1 "$$"
#define SPECIAL_VAR_2 "$?"

/********global evironement variable********/
extern char **environ;

/**
 * struct data_t - struct holding program's data.
 *
 * @progName: program's name.
 * @argv: arguments vector.
 * @lineptr: line pointer.
 * @cmd: command line tokenized.
 * @cmdSize: line length.
 * @cmdCounter: line index.
 * @envp: environment.
 * @alias: added alias.
 * @flag: holds command flag.
 * @modo: mode indicator if interactive or not.
 * @pewd: working dir.
 */
typedef struct data_t
{
	char *progName;
	char **argv;
	char *lineptr;
	char **cmd;
	int cmdSize;
	int cmdCounter;
	char **envp;
	char **alias;
	int flag;
	int modo;
	char *pewd;
} data_t;

/**
 * struct builtin_t - built-ins name and function.
 *
 * @command: name of the built-in.
 * @fun: the built-in's function.
 */
typedef struct builtin_t
{
	char *command;
	int (*fun)(data_t*, int);
} builtin_t;

/****************************************/
/***************functions***************/

/********0x0B********/
char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strdup(char *str);
void free_data(data_t *data);
void free_array(char **arr, int size);

/********builtin_alias********/
int bi_aliases(data_t *data, int idx);
char *aliasHandler(data_t *data, int pos);
void printAlias(char *alias);
int printAliases(data_t *data, char *alias);
void addAlias(data_t *data, char *alia);

/********builtin_cd********/
int bi_cd(data_t *data, int idx);
void _setenv(data_t *data, char *name, char *value);
int _setpwd(data_t *data, char *newDir, int p);

/********builtin_main********/
int builtin_check(data_t *data, char *cmd, int idx);
int (*get_builtin(char *cmd))(data_t*, int);

/********builtin_rest********/
int bi_exit(data_t *data, int idx);
int bi_env(data_t *data, int idx);
int bi_unsetenv(data_t *data, int idx);

/********builtin_setenv********/
int findEnvIndex(data_t *data, char *env);
int findEmptyEnvIndex(data_t *data);
int bi_setenv(data_t *data, int idx);

/********env_handler********/
char *_getenv(char *name, data_t *data);
char **env_cp(char **copy);
char *env_check(char *env, char *var);
int envs(data_t *data);

/********file_handler********/
void file_errors(data_t *data, int flag);
int file_open(data_t *data);
void file_close(data_t *data, int id);

/********getline********/
int _getline(data_t *data, int *size, int stream);
int check_reading(data_t *data, int stat, int i);

/********interactive********/
void start_interactive(int ac, data_t *data);

/********line_handling********/
char *exe_path(char *command, data_t *data);
int line_counter(data_t *data);
int _isdir(char *path);
int blankline(char *line);
void handle_comment(data_t *data);

/********main********/
void handle_sig(int num);
void start_env(data_t *data);
void start_alias(data_t *data);
void start_data(data_t *data, char *argv[]);

/********op_chars********/
void insertChars(char *nline, int *i, int *j, char c);
void op_chars(char *line, char *nline, int *idx, int *jmp);

/********op_seps********/
int countoperators(char *line, char op);
char *op_seps(data_t *data);

/********op_special********/
void op_special(char *srcLine, char *newLine, int *currentIndex, int *jumpidx);

/********processor********/
void processor(data_t *data);
int cache(data_t *data, char **ptr, int *i, int *pos,
		  int *c, int *cmp2);
void handle_fork(data_t *data, char **command, char *exe, int *stat);

/********prompt********/
void cleanup(data_t *data);
int prompt(data_t *data, int *n, int stream);

/********strings-2********/
int _strcmp(char *s1, char *s2);
int _strncmp(const char *s1, const char *s2, size_t n);
char *_strcpy(char *dest, char *src);
int _istrchr(char *s, char c);
char *_strcat(char *dest, char *src);

/********strings********/
char *_strncpy(char *dest, char *src, int n);
int _isdigit(char *c);
int _atoi(char *s);
void rev_string(char *s);
int _strlen(const char *s);

/********strtow********/
char **_strtow(char *str, const char *delim, int *size);

/********tokens********/
int tok_cmp(char *token, int *sep);
int tok_check(char *token);
int tok_count(char *inputString, const char *delimiter);
int tok_len(char *token, const char *delim, int index);
int _isdelim(char c, const char *delim);

/********var_special********/
void handleSpecialVar1(data_t *data, int i, char *buffer);
void handleSpecialVar2(data_t *data, int i, char *buffer);
void var_special(data_t *data);
void var_getvalue(data_t *data, int idx);
void _itocmd(char *cmd, int convert);

/********which********/
char *_which(char *cmd, data_t *data);
void not_found(data_t *data);

/********write********/
void _puts(char *s, int stream);
int _putchar(char c);
void print_number(int n, int stream);

#endif
