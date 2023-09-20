#include "main.h"

/**
 * bi_aliases - handle alias command.
 *
 * @data: struct data.
 * @idx: command index.
 *
 * Return: 1 if success OR 127 if fails.
 */
int bi_aliases(data_t *data, int idx)
{
	int result, i;
	char *cmd;

	if (data->cmd[idx + 1] == NULL)
	{
		printAliases(data, NULL);
		return (1);
	}
	i = 0;
	while (data->cmd[idx + 1 + i])
	{
		cmd = data->cmd[idx + 1 + i];
		if (_istrchr(cmd, '='))
			addAlias(data, cmd);
		else
		{
			result = printAliases(data, cmd);
			if (!result)
			{
				_puts("alias: ", 2);
				_puts(cmd, 2);
				_puts(" not found\n", 2);
				errno = 127;
			}
		}
		i++;
	}
	return (1);
}

/**
 * aliasHandler - handle aliases.
 *
 * @data: a pointer to data structure.
 * @pos: alias position.
 *
 * Return: created alias.
 */
char *aliasHandler(data_t *data, int pos)
{
	int i, cmdlen, newlen;

	cmdlen = _strlen(data->cmd[pos]);
	for (i = 0; data->alias[i]; i++)
	{
		if (_strncmp(data->alias[i], data->cmd[pos], cmdlen) == 0
		&& data->alias[i][cmdlen] == '=')
		{
			free(data->cmd[pos]);
			newlen = _strlen(data->alias[i]) - cmdlen - 1;
			data->cmd[pos] = malloc(sizeof(char) * (newlen + 1));
			_strncpy(data->cmd[pos], data->alias[i] + cmdlen + 1, newlen);
			data->cmd[pos][newlen] = '\0';
		}
	}
	return (data->cmd[pos]);
}

/**
 * printAlias - print aliases.
 *
 * @alias: alias to print.
 *
 * Return: Nothing.
 */
void printAlias(char *alias)
{
	int j, qflag = 0;
	int len = _strlen(alias);

	for (j = 0; j < len; j++)
	{
		if (alias[j] == '=')
			qflag = 1;
		_putchar(alias[j]);
		if (qflag == 1)
		{
			_putchar('\'');
			qflag = 0;
		}
		if (j == len - 1)
		{
			_putchar('\'');
			_putchar('\n');
			break;
		}
	}
}

/**
 * printAliases - print aliases.
 *
 * @data: pointer to data structure.
 * @alias: alias to print.
 *
 * Return: 1 if success OR 0 if it fails.
 */
int printAliases(data_t *data, char *alias)
{
	int i, flag = 0;

	for (i = 0; data->alias[i] != NULL; i++)
	{
		if (alias)
		{
			if (_strncmp(data->alias[i], alias, _strlen(alias)) == 0
					&& data->alias[i][_strlen(alias)] == '=')
				flag = 1;
			else
				continue;
		}
		printAlias(data->alias[i]);
		if (flag == 1)
			return (1);
	}
	return (0);
}

/**
 * addAlias - add alias or overwrite existing.
 *
 * @data: pointer to data structure.
 * @alia: alias to be added.
 *
 * Return: Nothing.
 */
void addAlias(data_t *data, char *alia)
{
	int i = 0, pos = 0;
	size_t len;

	pos = _istrchr(alia, '=');
	while (data->alias[i] != NULL)
	{
		if (_strncmp(data->alias[i], alia, pos) == 0)
		{
			free(data->alias[i]);
			break;
		}
		i++;
	}
	len = _strlen(alia);
	data->alias[i] = malloc(sizeof(char) * (len + 1));
	if (data->alias[i] == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return;
	}
	_strncpy(data->alias[i], alia, len);
	data->alias[i][len] = '\0';
}
