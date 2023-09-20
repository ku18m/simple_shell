#include "main.h"

/**
 * cleanup - help prompt to clean it's garbage.
 *
 * @data: pointer to data structure.
 *
 * Return: Nothing.
 */
void cleanup(data_t *data)
{
	free(data->lineptr);
	free_array(data->alias, 24);
	free_array(data->envp, 64);
}

/**
 * prompt - shell ui.
 *
 * @data: pointer to data structure.
 * @n: buffer size.
 * @stream: input stream.
 *
 * Return: number of chars have been read OR -1 if failed.
 */
int prompt(data_t *data, int *n, int stream)
{
	int val;

	if (data->modo)
		_puts("$ ", STDOUT_FILENO);
	val = _getline(data, n, stream);
	if (!data->modo && val == 0)
	{
		cleanup(data);
		exit(errno);
	}
	if (val == EOF)
		exit(errno);
	if (val == 1 || val == -1)
	{
		cleanup(data);
		exit(val == 1 ? errno : EXIT_FAILURE);
	}
	if (!blankline(data->lineptr))
		return (val);
	return (0);
}
