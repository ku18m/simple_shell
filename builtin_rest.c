#include "main.h"

/**
 * bi_exit - builtin command to exit the shell,
 * with speciefied error num.
 *
 * @data: pointer to data structure.
 * @idx: the command index.
 *
 * Return: 1 if nothing OR STD error.
 */
int bi_exit(data_t *data, int idx)
{

	int code;

	if (data->cmd[idx + 1] != NULL)
	{
		if (_isdigit(data->cmd[idx + 1]))
		{
			code = _atoi(data->cmd[idx + 1]);
			free_data(data);
			exit(code);
		}
		else
		{
			_puts(data->progName, STDERR_FILENO);
			_puts(": ", STDERR_FILENO);
			print_number(data->cmdCounter, STDERR_FILENO);
			_puts(": ", STDERR_FILENO);
			_puts(data->cmd[idx], STDERR_FILENO);
			_puts(": Illegal number: ", STDERR_FILENO);
			_puts(data->cmd[idx + 1], STDERR_FILENO);
			_puts("\n", STDERR_FILENO);
			free_data(data);
			exit(2);
		}
	}
	free_data(data);
	exit(errno);
	return (1);
}

/**
 * bi_env - print environement variables.
 *
 * @data: a pointer to data structure.
 * @idx: command index.
 *
 * Return: Always 1 (Success).
 */
int bi_env(data_t *data, int idx)
{
	int i;
	(void)idx;

	i = 0;
	while (data->envp[i])
		_puts(data->envp[i], STDOUT_FILENO), _putchar('\n'), i++;
	return (1);
}

/**
 * bi_unsetenv - print environement variables.
 *
 * @data: a pointer to data structure.
 * @idx: command index.
 *
 * Return: Always 1 (Success).
 */
int bi_unsetenv(data_t *data, int idx)
{
	char *envName;
	int i, o;

	envName = data->cmd[idx + 1];
	if (envName != NULL)
	{
		for (i = 0; data->envp[i] != NULL; i++)
		{
			if (_strcmp(data->envp[i], envName) == 0)
			{
				free(data->envp[i]);
				for (o = i; data->envp[o] != NULL; o++)
				{
					data->envp[o] = data->envp[o + 1];
				}
				break;
			}
		}
	}
	return (1);
}
