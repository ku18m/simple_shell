#include "main.h"

/**
 * builtin_check - look for & run builtin commands.
 *
 * @data: pointer to data structure.
 * @cmd: the command to look for it's function.
 * @idx: line index.
 *
 * Return: 1 if found & run successfully OR 0 if not.
 */
int builtin_check(data_t *data, char *cmd, int idx)
{
	int (*bi_fun)(data_t*, int);

	bi_fun = get_builtin(cmd);
	if (bi_fun)
		bi_fun(data, idx);
	else
		return (0);
	return (1);
}

/**
 * get_builtin - look for built in commands functions.
 *
 * @cmd: the command to look for it's function.
 *
 * Return: The correct function if found OR 0 if not found.
 */
int (*get_builtin(char *cmd))(data_t*, int)
{
	builtin_t bis[] = {
		{"exit", bi_exit},
		{"cd", bi_cd},
		{"env", bi_env},
		{"setenv", bi_setenv},
		{"unsetenv", bi_unsetenv},
		{"alias", bi_aliases},
		{NULL, NULL}
	};
	int i;

	i = 0;
	while (bis[i].command != NULL)
	{
		if (_strcmp(cmd, bis[i].command) == 0)
			return (bis[i].fun);
		i++;
	}
	return (0);
}
