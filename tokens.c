#include "main.h"

/**
 * tok_cmp - comapare given token.
 *
 * @token: the given token to compare.
 * @sep: separator.
 *
 * Return: 1 if it's op OR 0 if it's not.
 */
int tok_cmp(char *token, int *sep)
{
	if (_strcmp(token, ";") == 0)
	{
		*sep = 1;
		return (1);
	}
	else if (_strcmp(token, "&&") == 0)
	{
		*sep = 2;
		return (1);
	}
	else if (_strcmp(token, "||") == 0)
	{
		*sep = 4;
		return (1);
	}
	return (0);
}

/**
 * tok_check - check if the token is op.
 *
 * @token: the token to check.
 *
 * Return: 1 if it's op OR 0 if not.
 */
int tok_check(char *token)
{
	if (_strcmp(token, ";") == 0)
		return (1);
	else if (_strcmp(token, "&&") == 0)
		return (1);
	else if (_strcmp(token, "||") == 0)
		return (1);

	return (0);
}

/**
 * tok_count - counts number of tokens.
 *
 * @inputString: tokens holder
 * @delimiter: delimiter.
 *
 * Return: number of tokens
 */
int tok_count(char *inputString, const char *delimiter)
{
	int i, strLength, count = 0;

	if (inputString == NULL || delimiter == NULL)
		return (0);

	strLength = _strlen(inputString);
	for (i = 0; i < strLength; i++)
	{
		if (!_isdelim(inputString[i], delimiter))
		{
			count++;
			i += tok_len(inputString, delimiter, i);
		}
	}
	return (count);
}

/**
 * tok_len - gets token length.
 *
 * @token: the token to check.
 * @delim: tokens delim.
 * @index: token index.
 *
 * Return: Token length.
 */
int tok_len(char *token, const char *delim, int index)
{
	int len;

	for (len = 0; token[index + len] && token[index + len] != '\n'; len++)
	{
		if (_isdelim(token[index + len], delim))
		{
			break;
		}
	}
	return (len);
}

/**
 * _isdelim - check if the given char is delim.
 *
 * @c: character to check.
 * @delim: delimiters.
 *
 * Return: 1 if it's delim OR 0 if it's not.
 */
int _isdelim(char c, const char *delim)
{
	int i, del_len;

	del_len = _strlen(delim), i = 0;
	while (i < del_len)
	{
		if (c == delim[i])
			return (1);
		i++;
	}
	return (0);
}
