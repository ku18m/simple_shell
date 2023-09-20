#include "main.h"

/**
  * handle_sig - handle sign.
  *
  * @num: syntax, unused.
  *
  * Return: Nothing.
  */
void handle_sig(int num)
{
	char *p = "\n$ ";
	(void)num;

	write(STDOUT_FILENO, p, 3);
}


/**
  * start_env - assign environment.
  *
  * @data: pointer to data structure.
  *
  * Return: Nothing.
  */
void start_env(data_t *data)
{
	int i;

	data->envp = malloc(sizeof(char *) * 64);
	for (i = 0; i < 64; i++)
		data->envp[i] = NULL;
	env_cp(data->envp);
	environ = data->envp;
}

/**
  * start_alias - assign alias data.
  *
  * @data: pointer to data structure.
  *
  * Return: Nothing.
  */
void start_alias(data_t *data)
{
	int i;

	data->alias = malloc(sizeof(char *) * 24);
	i = 0;
	while (i < 24)
		data->alias[i] = NULL, i++;
}

/**
  * start_data - assign data.
  *
  * @data: pointer to data structure.
  * @argv: arguments vector.
  *
  * Return: Nothing.
  */
void start_data(data_t *data, char *argv[])
{
	data->progName = argv[0];
	data->argv = argv;
	start_env(data);
	start_alias(data);
	data->lineptr = NULL;
	data->cmd = NULL;
	data->cmdSize = 0;
	data->cmdCounter = 0;
}

/**
 * main - Entry point.
 *
 * @argc: number of arguments.
 * @argv: arguments vector.
 *
 * Return: 0 if success OR STD Error.
 */
int main(int argc, char *argv[])
{
	data_t data;

	signal(SIGINT, handle_sig);
	if (isatty(STDIN_FILENO) && argc == 1)
		data.modo = 1;
	else
		data.modo = 0;
	errno = 0;
	start_data(&data, argv);
	start_interactive(argc, &data);
	return (0);
}
