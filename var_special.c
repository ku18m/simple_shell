#include "main.h"

/**
 * handleSpecialVar1 - handle $$ variable.
 *
 * @data: pointer to data structure.
 * @i: var index.
 * @buffer: the given line.
 *
 * Return: Nothing.
 */
void handleSpecialVar1(data_t *data, int i, char *buffer)
{
	int val;

	val = getpid();
	free(data->cmd[i]);
	_itocmd(buffer, val);
}

/**
 * handleSpecialVar2 - handle $? variable.
 *
 * @data: pointer to data structure.
 * @i: var index.
 * @buffer: the given line.
 *
 * Return: Nothing.
 */
void handleSpecialVar2(data_t *data, int i, char *buffer)
{
	free(data->cmd[i]);
	_itocmd(buffer, errno);
}
/**
 * var_special - handle special vars.
 *
 * @data: pointer to data structure.
 *
 * Return: Nothing.
 */
void var_special(data_t *data)
{
	int i;
	char buffer[24] = {'\0'};
	int flag = 0;

	for (i = 0; data->cmd[i] != NULL; i++)
	{
		if (_strcmp(data->cmd[i], SPECIAL_VAR_1) == 0)
		{
			handleSpecialVar1(data, i, buffer);
			flag = 1;
		}
		else if (_strcmp(data->cmd[i], SPECIAL_VAR_2) == 0)
		{
			handleSpecialVar2(data, i, buffer);
			flag = 1;
		}
		else if (data->cmd[i][0] == '$'
			&& data->cmd[i][1] != ' ' && data->cmd[i][1] != '\0')
		{
			var_getvalue(data, i);
			flag = 0;
		}
		if (flag)
		{
			data->cmd[i] = malloc(_strlen(buffer) + 1);
			data->cmd[i] = _strcpy(data->cmd[i], buffer);
			flag = 0;
		}
	}
}

/**
 * var_getvalue - gets var value.
 *
 * @data: pointer to data structure.
 * @idx: line index.
 *
 * Return: Nothing.
 */
void var_getvalue(data_t *data, int idx)
{
	int i;
	char name[48] = {'\0'}, *ptr = NULL;

	i = 1;
	while (data->cmd[idx][i])
	{
		name[i - 1] = data->cmd[idx][i];
		i++;
	}
	name[i] = '\0';
	ptr = _getenv(name, data);
	if (ptr != NULL)
	{
		free(data->cmd[idx]);
		data->cmd[idx] = malloc(_strlen(ptr) + 1);
		_strcpy(data->cmd[idx], ptr + _strlen(name) + 1);
	}
	else
		data->cmd[idx][0] = '\0';
}

/**
 * _itocmd - convert integer into string.
 *
 * @cmd: line to assign the value.
 * @convert: the integer to convert.
 *
 * Return: Nothing.
 */
void _itocmd(char *cmd, int convert)
{
	int i;

	i = 0;
	do {
		cmd[i++] = convert % 10 + '0';
	} while ((convert /= 10) > 0);
	cmd[i] = '\0';
	rev_string(cmd);
}
