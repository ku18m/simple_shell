#include "main.h"

/**
 * _strcmp -  compares two strings.
 *
 * @s1: a pointer to the first string.
 * @s2: a pointer to the second string.
 *
 * Return: (result) s1[a] - s2[a] when a difference found.
 */
int _strcmp(char *s1, char *s2)
{
	int a = 0, result = 0;

	while (s1[a] != '\0' && s2[a] != '\0')
	{
		if (s1[a] != s2[a])
		{
			result = (s1[a] - s2[a]);
			break;
		}
		a++;
	}
	return (result);
}

/**
 * _strncmp - Compare n bytes from a string.
 *
 * @s1: first string.
 * @s2: second string.
 * @n: n bytes.
 *
 * Return: 0 (equal) 1 (s1 greater) -1 (s2 greater)
 */
int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i] || s1[i] == '\0' || s2[i] == '\0')
		{
			return (s1[i] - s2[i]);
		}
	}
	return (0);
}

/**
 * _strcpy -  copies the string pointed to by src, including (\0),
 * to the buffer pointed to by dest.
 *
 * @dest: a pointer to the string.
 * @src: an array of chars.
 *
 * Return: (dest) coppied array.
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	while (src[a] != '\0')
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

/**
 * _istrchr - locates a character in a string.
 *
 * @s: the pointer to search.
 * @c: the character to look for.
 *
 * Return: given character index.
 */

int _istrchr(char *s, char c)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
	{
		if (s[i] == c)
			return (i);
	}
	if (s[i] == c)
		return (i);
	return (0);
}
/**
 * _strcat -  concatenates two strings.
 *
 * @dest: a pointer to the first string.
 * @src: a pointer to the second string.
 *
 * Return: (dest) concatenated array.
 */
char *_strcat(char *dest, char *src)
{
	int a = 0, i = 0;

	while (dest[a] != '\0')
	{
		a++;
	}
	while (src[i] != 0)
	{
		dest[a] = src[i];
		i++;
		a++;
	}
	return (dest);
}
