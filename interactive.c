#include "main.h"

/**
 * start_interactive - start interactive mode.
 *
 * @ac: number of arguments.
 * @data: pointer to data structure.
 *
 * Return: Nothing.
 */
void start_interactive(int ac, data_t *data)
{
	int size, line, id;

	id = 0;
	if (!data->modo && ac == 2)
		id = file_open(data);
	while ((line = prompt(data, &size, id)) != -1 || data->lineptr)
	{
		data->cmdCounter++;
		if (line == 0)
			continue;
		handle_comment(data);
		data->lineptr = op_seps(data);
		data->cmd = _strtow(data->lineptr, " \t\n", &data->cmdSize);
		if (data->cmdSize > 0)
		{
			var_special(data);
			processor(data);
			free_array(data->cmd, data->cmdSize);
			data->cmd = NULL;
			free(data->lineptr);
			data->lineptr = NULL;
		}
	}
	if (!data->modo && ac == 2)
		file_close(data, id);
	free_data(data);
}
