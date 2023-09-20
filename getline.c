#include "main.h"

/**
 * _getline - Get the input line from the user.
 *
 * @data: pointer to data structure.
 * @size: buffer size.
 * @stream: screen to read from.
 *
 * Return: number of characters have been read OR -1 if failed.
 */
int _getline(data_t *data, int *size, int stream)
{
	int i, stat, check;
	char c = '\0', *tmp = NULL;

	stat = 0, check = 0;
	if (data->lineptr == NULL)
		*size = 0;
	for (i = 0; c != EOF && c != '\n'; i++)
	{
		if (i >= *size)
		{
			*size += BUFFSIZE;
			tmp = _realloc(data->lineptr, *size - BUFFSIZE, *size);
			if (tmp == NULL)
			{
				free(data->lineptr), data->lineptr = NULL;
				return (-1);
			} data->lineptr = tmp;
		}
		fflush(stdout);
		stat = read(stream, &c, 1);
		stat = check_reading(data, stat, i);
			if (stat == 0)
				break;
		if (stat == -1)
			return (-1);
		if (check == 0 && c == ' ')
		{
			i--;
			continue;
		} else
			check = 1;
		if (c == '\n')
		{
			data->lineptr[(i++)] = c;
			break;
		} data->lineptr[i] = c;
	} data->lineptr[i] = '\0';
	return (i);
}

/**
 * check_reading - handle reading.
 *
 * @data: pointer to data structure.
 * @stat: reading status.
 * @i: length.
 *
 * Return: given reading status.
 */
int check_reading(data_t *data, int stat, int i)
{
	if (stat == 0)
	{
		if (i == 0)
		{
			free(data->lineptr);
			free_array(data->envp, 64);
			free_array(data->alias, 24);
			exit(errno);
		}
		return (0);
	}
	if (stat == -1)
	{
		free(data->lineptr);
		data->lineptr = NULL;
		return (-1);
	}
	return (stat);
}
