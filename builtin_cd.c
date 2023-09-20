#include "main.h"

/**
 * bi_cd - built in function to change dir.
 *
 * @data: pointer to data structure.
 * @idx: command index.
 *
 * Return: 1 if success OR STD error.
 */
int bi_cd(data_t *data, int idx)
{
	char *homeDirectory = _getenv("HOME=", data);
	char oldpwd[128] = {'\0'}, *previousDirectory = NULL;
	int status;
	(void)idx;

	if (data->cmd[1])
	{
		if (_strcmp(data->cmd[1], "-") == 0)
		{
			previousDirectory = _getenv("OLDPWD=", data);
			if (previousDirectory != NULL)
			{
				status = _setpwd(data, previousDirectory, 1);
			}
			else
			{
				_setenv(data, "OLDPWD", getcwd(oldpwd, 128));
				_puts(oldpwd + _istrchr(oldpwd, '='), STDOUT_FILENO);
				_putchar('\n');
				status = 0;
			}
		}
		else
		{
			status = _setpwd(data, data->cmd[1], 0);
		}
	}
	else
	{
		if (homeDirectory == NULL)
		{
			homeDirectory = getcwd(oldpwd, 128);
			status = _setpwd(data, homeDirectory, 0);
		}
		else
		{
			status = _setpwd(data, homeDirectory + 5, 0);
		}
	}
	return (status);
}

/**
 * _setenv - set env variable.
 *
 * @name: variable name.
 * @value: variable value.
 * @data: pointer to data structure.
 *
 * Return: Nothing.
 */
void _setenv(data_t *data, char *name, char *value)
{
	int i, length, flag = 0;

	if (name != NULL && value != NULL)
	{
		for (i = 0; data->envp[i] != 0; i++)
		{
			if (env_check(data->envp[i], name))
			{
				free(data->envp[i]);
				flag = 1;
				break;
			}
		}
		length = _strlen(name) + _strlen(value) + 1;
		data->envp[i] = malloc(length + 1);
		if (data->envp[i] == NULL)
		{
			errno = ENOMEM;
			perror("Error");
			exit(128);
		}
		_strcpy(data->envp[i], name);
		_strcat(data->envp[i], "=");
		_strcat(data->envp[i], value);
		data->envp[i][length] = '\0';
		if (!flag)
			data->envp[i + 1] = NULL;
	}
}

/**
 * _setpwd - set working directory.
 *
 * @data: pointer to data structure.
 * @newdir: directory to be set.
 * @flag: indicator.
 *
 * Return: 0 if success OR 1 if not.
 */
int _setpwd(data_t *data, char *newdir, int flag)
{
	int check = 0, position = 0;
	char prevdir[128] = "";

	getcwd(prevdir, 128);
	if (_strcmp(prevdir, newdir) != 0)
	{
		position = _istrchr(newdir, '=');
		check = chdir(newdir + position + flag);
		if (check == -1)
		{
			_puts(data->progName, STDERR_FILENO);
			_puts(": ", STDERR_FILENO);
			print_number(data->cmdCounter, STDERR_FILENO);
			_puts(": cd: can't cd to ", STDERR_FILENO);
			_puts(newdir + position +  flag, STDERR_FILENO);
			_puts("\n", STDERR_FILENO);
			errno = 2;
			return (1);
		}
		_setenv(data, "PWD", newdir + position + flag);
	}
	if (flag)
	{
		_puts(newdir + position + flag, STDOUT_FILENO);
		_puts("\n", STDOUT_FILENO);
	}
	position = _istrchr(prevdir, '=');
	_setenv(data, "OLDPWD", prevdir + position);
	return (0);
}
