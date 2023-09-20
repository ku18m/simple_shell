#include "main.h"


/**
 * processor - handle processes.
 *
 * @data: pointer to data structure.
 *
 * Return: Nothing.
 */
void processor(data_t *data)
{
	int st = 0, i, pos = 0, count = line_counter(data), k = 0, j;
	int cmp2 = 0, cmp = 0, sep = 0, isbi = 0, m, Cpos;
	char *exe = NULL, *ptr[MAX_PTR_SIZE];
	bool isFOSCZ, isSASZ, isSASNZ, isSO;

	for (i = 0; i < count; i++)
	{
		j = cache(data, ptr, &i, &pos, &count, &cmp2);
		isFOSCZ = i == 0 || (st == 0 && cmp == 0);
		isSASZ = (sep & STAT_CONDITION) && st == 0;
		isSASNZ = (sep & CMP_CONDITION) && st != 0, isSO = sep & CMP2_CONDITION;
		if (isFOSCZ || isSASZ || isSASNZ || isSO)
		{
			Cpos = cmp2 == 0 ? 0 : 1, ptr[0] = aliasHandler(data, pos);
			if (i == count - 1)
			{
				for (m = 0; ptr[m] != NULL; m++)
				;
				if (_strcmp(ptr[m - 1], ";") == 0)
					ptr[m - 1] = NULL;
			}
			isbi = builtin_check(data, ptr[0], i + Cpos);
			if (isbi)
				continue;
			exe = exe_path(ptr[0], data);
			if (!isbi && !_isdir(ptr[0]) && exe != NULL)
				handle_fork(data, ptr, exe, &st);
			else
				not_found(data);
		}
		for (sep = 0; i < count - 1 && data->cmd[pos + k] != NULL; k++)
		{
			cmp = tok_cmp(data->cmd[pos + k], &sep);
			if (cmp != 0)
			{
				k--;
				break;
			}
		} pos += j + 1;
	}
}

/**
 * cache - check for seps or ops.
 *
 * @data: pointer to data structure.
 * @av: first argument.
 * @i: number of commands.
 * @location: command position.
 * @c: i.
 * @cmp2: pointer to seperators or operators.
 *
 * Return: number of seps or ops.
 */
int cache(data_t *data, char **av, int *i, int *location,
		  int *c, int *cmp2)
{
	int j;

	j = 0;
	while (data->cmd[(*location) + j] != NULL)
	{
		if ((*i) < (*c) - 1)
		{
			*cmp2 = tok_check(data->cmd[(*location) + j]);
			if ((*cmp2) != 0)
				break;
		}
		av[j] = data->cmd[(*location) + j];
		j++;
	}
	av[j] = NULL;
	return (j);
}

/**
 * handle_fork - handle fork process.
 *
 * @data: pointer to data structure.
 * @command: command line.
 * @exe: the complete exe path.
 * @stat: pointer to status flag.
 *
 * Return: Nothing.
 */
void handle_fork(data_t *data, char **command, char *exe, int *stat)
{
	pid_t pid;

	pid = fork();
	if (pid == 0)
	{
		*stat = execve(exe, command, data->envp);
		if (*stat == -1)
		{
			perror(exe);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(stat);
		if (WIFEXITED(*stat))
			errno = WEXITSTATUS(*stat);
		if (data->flag)
			free(exe);
		exe = NULL;
	}
}
