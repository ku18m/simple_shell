#include "main.h"

/**
 * _which - find the path of a file.
 *
 * @cmd: filename to find it's path.
 * @data: pointer to data structure.
 *
 * Return: the file's path OR NULL if not found.
 */
char *_which(char *cmd, data_t *data)
{
	char *path, **pathToken, *buff = NULL;
	int i, size = 0, l1 = _strlen(cmd), l2;

	path = _getenv("PATH", data);

	if (path == NULL)
		return (NULL);
	pathToken = _strtow(path + 5, ":", &size);
	i = 0;
	while (i < size)
	{
		l2 = _strlen(pathToken[i]);
		buff = malloc(sizeof(char) * (l1 + l2 + 2));
		if (buff == NULL)
		{
			free_array(pathToken, size);
			return (NULL);
		}
		_memcpy(buff, pathToken[i], l2);
		buff[_strlen(pathToken[i])] = '/';
		_memcpy(buff + _strlen(pathToken[i]) + 1, cmd, l1);
		buff[l1 + l2 + 1] = '\0';
		if (access(buff, X_OK) == 0)
		{
			free_array(pathToken, size);
			return (buff);
		}
		free(buff);
		i++;
	}
	free_array(pathToken, size);
	return (NULL);
}

/**
 * not_found - handle file not found error.
 *
 * @data: pointer to data structure.
 *
 * Return: Nothing.
 */
void not_found(data_t *data)
{
	_puts(data->progName, 2);
	_puts(": ", 2);
	print_number(data->cmdCounter, 2);
	_puts(": ", 2);
	_puts(data->cmd[0], 2);
	_puts(": not found\n", 2);
	if (!data->modo)
	{
		free_data(data);
		exit(127);
	}
}
