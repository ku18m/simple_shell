#include "main.h"

/**
 * file_errors - handle close and open file errors.
 *
 * @data: pointer to data structure.
 * @flag: situation indicator if close or open error.
 *
 * Return: Nothing.
 */
void file_errors(data_t *data, int flag)
{
	if (flag == 0)
	{
		free_data(data);
		_puts(data->progName, 2);
		_puts(": ", 2);
		print_number(data->cmdCounter, 2);
		_puts(": Can't open ", 2);
		_puts(data->argv[1], 2);
		_puts("\n", 2);
		exit(127);
	}
	else if (flag == 1)
	{
		_puts(data->progName, 2);
		_puts(": ", 2);
		print_number(data->cmdCounter, 2);
		_puts(": Can't close ", 2);
		_puts(data->argv[1], 2);
		_puts("\n", 2);
		exit(EXIT_FAILURE);
	}
}
/**
 * file_open - open the given file name.
 *
 * @data: pointer to data structure.
 *
 * Return: file id.
 */
int file_open(data_t *data)
{
	int id;

	id = open(data->argv[1], O_RDONLY);
	if (id == -1)
		file_errors(data, 0);
	return (id);
}

/**
 * file_close - close the given file id.
 *
 * @data: pointer to data structure.
 * @id: the id of the file to close.
 *
 * Return: Nothing.
 */
void file_close(data_t *data, int id)
{
	if (close(id) == -1)
		file_errors(data, 1);
}
