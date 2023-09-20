#include "main.h"

/**
 * _getenv - gets environment variable.
 *
 * @name: varaible name.
 * @data: pointer to data structure.
 *
 * Return: pointer to var value OR NULL if failed.
 */
char *_getenv(char *name, data_t *data)
{
	int length, i;

	length = _strlen(name);
	for (i = 0; data->envp[i]; i++)
	{
		if (_strncmp(data->envp[i], name, length) == 0)
			return (data->envp[i]);
	}
	return (NULL);
}

/**
 * env_cp - make a copy of the environement.
 *
 * @copy: vector to write environment in.
 *
 * Return: Copied vector OR NULL if failed.
 */
char **env_cp(char **copy)
{
	int i;

	if (environ == NULL)
		return (NULL);
	i = 0;
	while (environ[i])
		copy[i] = _strdup(environ[i]), i++;
	return (copy);
}

/**
 * env_check - check if the variable exist.
 *
 * @env: environment variables.
 * @var: the variable to check it's exist.
 *
 * Return: variable pointer if found OR NULL if not.
 */
char *env_check(char *env, char *var)
{
	int length;

	if (env == NULL || var == NULL)
		return (NULL);
	length = _strlen(var);
	if (_strncmp(var, env, length) == 0 && env[length] == '=')
		return (env);
	return (NULL);
}

/**
 * envs - count environment variables.
 *
 * @data: pointer to data structure.
 *
 * Return: variables number.
 */
int envs(data_t *data)
{
	int i;

	i = 0;
	while (data->envp[i])
		i++;
	return (i);
}
