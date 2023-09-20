#include "main.h"

/**
 * exe_path - look for exe path and add it if found.
 *
 * @command: the entered command line.
 * @data: pointer to data structure.
 *
 * Return: full exe path.
 */
char *exe_path(char *command, data_t *data)
{
	char *executablePath;

	if (command[0] == '/' || command[0] == '.')
	{
		data->flag = 0;
		if (access(command, X_OK) == 0)
			executablePath = command;
		else
			return (NULL);
	}
	else
		data->flag = 1, executablePath = _which(command, data);
	return (executablePath);
}

/**
 * line_counter - check for commands number.
 *
 * @data: pointer to data structure.
 *
 * Return: number of commands entered.
 */
int line_counter(data_t *data)
{
	char *validCommands[] = {"&&", "||", ";"};
	size_t i, j, count = 1;

	for (i = 0; data->cmd[i + 1] != NULL; i++)
	{
		for (j = 0; j < sizeof(validCommands) / sizeof(validCommands[0]); j++)
		{
			if (_strcmp(data->cmd[i], validCommands[j]) == 0)
			{
			count++;
			break;
			}
		}
	}
	return (count);
}

/**
 * _isdir - look for a directory for a given path.
 *
 * @path: the given path to check.
 *
 * Return: 1 if it's a directory OR 0 if it's not.
 */
int _isdir(char *path)
{
	int status;
	struct stat dirstat;

	status = stat(path, &dirstat);
	if (status == 0)
	{
		if (S_ISDIR(dirstat.st_mode))
			return (1);
	}
	return (0);
}

/**
 * blankline - check if it's blank line.
 *
 * @line: the line to check.
 *
 * Return: 1 if it's blank OR 0 if it's not.
 */
int blankline(char *line)
{
	int i = 0;

	while (line[i])
	{
		if (line[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

/**
 * handle_comment - handle comment lines.
 *
 * @data: pointer to data structure.
 *
 * Return: Nothing.
 */
void handle_comment(data_t *data)
{
	int i;

	if (data->lineptr[0] == '#')
	{
		data->lineptr[0] = '\0';
		return;
	}
	i = 1;
	while (data->lineptr[i] != '\0')
	{
		if (data->lineptr[i] == '#' && data->lineptr[i - 1] == ' ')
		{
			data->lineptr[i] = '\0';
			return;
		}
		i++;
	}
}
