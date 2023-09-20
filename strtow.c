#include "main.h"

/**
 * _strtow - splits a string into words.
 *
 * @str: string to split.
 * @delim: array of delimiters.
 * @size: buff size.
 *
 * Return: pointer to an array of strings or NULL.
 */
char **_strtow(char *str, const char *delim, int *size)
{
	char **words;
	int i, j = 0, k, len = 0;

	if (str == NULL || delim == NULL || str[0] == '\0')
		return (NULL);
	*size = tok_count(str, delim);
	if (*size == 0)
		return (NULL);
	words = malloc(sizeof(char *) * (*size + 1));
	if (words == NULL)
		return (NULL);
	for (i = 0; i < *size; i++)
	{
		while (_isdelim(str[j], delim))
			j++;

		len = tok_len(str, delim, j);
		words[i] = malloc(sizeof(char) * (len + 1));
		if (words[i] == NULL)
		{
			free_array(words, *size);
			return (NULL);
		}

		for (k = 0; k < len; k++)
		{
			words[i][k] = str[j];
			j++;
		}
		words[i][k] = '\0';
	} words[i] = NULL;
	return (words);
}
