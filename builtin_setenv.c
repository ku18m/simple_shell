#include "main.h"

/**
 * findEnvIndex - finding env index.
 *
 * @data: pointer to data structure.
 * @env: environement variables.
 *
 * Return: env index OR -1 (not found).
 */
int findEnvIndex(data_t *data, char *env)
{
	int i;

	for (i = 0; data->envp[i] != 0; i++)
	{
		if (env_check(data->envp[i], env))
			return (i);
	}
	return (-1);
}
/**
 * findEmptyEnvIndex - finding empty env index.
 *
 * @data: pointer to data structure.
 *
 * Return: env index OR -1 (not found).
 */
int findEmptyEnvIndex(data_t *data)
{
	int i;

	for (i = 0; data->envp[i] != 0; i++)
	{
		if (data->envp[i][0] == '\0')
			return (i);
	}
	return (-1);
}

/**
 * bi_setenv - set environement variable.
 *
 * @data: pointer to data structure.
 * @idx: command index.
 *
 * Return: Always (1) Success.
 */
int bi_setenv(data_t *data, int idx)
{
	int i, len;
	char flag = 0;

	if (data->cmd[idx + 1] != NULL && data->cmd[idx + 2] != NULL)
	{
		i = findEnvIndex(data, data->cmd[idx + 1]);
		if (i != -1)
			free(data->envp[i]), flag = 1;
		else
			i = findEmptyEnvIndex(data);
		len = _strlen(data->cmd[idx + 1]) + _strlen(data->cmd[idx + 2]) + 1;
		data->envp[i] = malloc(len + 1);
		if (data->envp[i] == NULL)
		{
			errno = ENOMEM;
			perror("Error");
			return (1);
		}
		_strcpy(data->envp[i], data->cmd[idx + 1]);
		_strcat(data->envp[i], "=");
		_strcat(data->envp[i], data->cmd[idx + 2]);
		data->envp[i][len] = '\0';
		if (!flag)
			data->envp[i + 1] = NULL;
	}
	return (1);
}
