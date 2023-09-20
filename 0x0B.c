#include "main.h"

char *_memcpy(char *dest, char *src, unsigned int n);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
char *_strdup(char *str);
void free_data(data_t *data);
void free_array(char **arr, int size);

/**
 * _memcpy - copies memory area.
 *
 * @dest: the pointer to be filled with copied area.
 * @src: the pointer of characters to copy from.
 * @n: the num of index to fill.
 *
 * Return: the copied pointer.
 */
char *_memcpy(char *dest, char *src, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		dest[i] = src[i];
	}
	return (dest);
}

/**
 * _realloc - reallocates a memory block using malloc and free.
 *
 * @old_size: the old size of the array.
 * @new_size: the new size of the array.
 * @ptr: the array to reallocate.
 *
 * Return: the created ptr or NULL if it fails.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	unsigned int i;
	char *store, *new;

	if (new_size == old_size)
	{
		return (ptr);
	}
	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		if (ptr == NULL)
		{
			free(ptr);
			return (NULL);
		}
		return (ptr);
	}
	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	store = ptr;
	new = malloc(new_size);
	if (new == NULL)
	{
		free(new);
		return (ptr);
	}
	i = 0;
	while (i < old_size)
	{
		new[i] = store[i];
		i++;
	}
	free(ptr);
	return (new);
}

/**
 * _strdup - returns a pointer to a newly allocated space in memory
 * which contains a copy of the string given as a parameter.
 *
 * @str: the address of memory to create a copy of it.
 *
 * Return: the created ptr.
 */
char *_strdup(char *str)
{
	unsigned int i, o;
	char *ptr;

	if (str == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	ptr = malloc((sizeof(char) * i) + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	o = 0;
	while (o < i)
	{
		ptr[o] = str[o];
		o++;
	}
	return (ptr);
}

/**
 * free_data - frees data structure.
 *
 * @data: pointer to data structure.
 *
 * Return: Nothing
 */
void free_data(data_t *data)
{
	free_array(data->cmd, data->cmdSize);
	data->cmd = NULL;
	free(data->lineptr);
	data->lineptr = NULL;
	free_array(data->envp, 64);
	data->envp = NULL;
	free_array(data->alias, 24);
}
/**
 * free_array - frees 2d array.
 *
 * @vector: the 2d array to free.
 * @size: size of the array.
 *
 * Return: Nothing.
 */
void free_array(char **vector, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		free(vector[i]);
		vector[i] = NULL;
		i++;
	}
	free(vector);
}
