#include "main.h"

/**
 * _strncpy -  copies the string pointed to by n of src.
 *
 * @dest: a pointer to the string.
 * @src: an array of chars.
 * @n: number of chars to copy.
 *
 * Return: (dest) coppied array.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a = 0, b = 0;

	while (n > 0)
	{
		if (src[b] != '\0')
		{
			dest[a] = src[a];
			b++;
		}
		else
		{
			dest[a] = '\0';
		}
		a++;
		n--;
	}
	return (dest);
}

/**
 * _isdigit - check if the string is digit or not.
 *
 * @c: The string to check.
 *
 * Return: 0 (If not a digit), 1 (If digit).
 */
int _isdigit(char *c)
{
	int i;

	i = 0;
	while (c[i])
	{
		if (c[i] < '0' || c[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

/**
 * _atoi - converts a string to an integer.
 *
 * @s: string input parameter.
 *
 * Return: converted integer from string.
*/
int _atoi(char *s)
{
	unsigned int i = 0;
	int neg = 1;

	while (*s != '\0')
	{
		if (*s < 58 && *s > 47)
		{
			i = (*s - 48) + (i * 10);
		}
		else if (*s == '-')
		{
			neg = neg * -1;
		}
		else if (i > 0)
		{
			break;
		}
		s++;
	}
	i = i * neg;

	return (i);
}

/**
 * rev_string - reverse a string.
 *
 * @s: a pointer to the string.
 *
 * Return: void.
 */
void rev_string(char *s)
{
	char *rev1 = s, *rev2 = s, r;

	while (*rev1 != '\0')
	{
		rev1++;
	}
	rev1--;
	while (rev2 < rev1)
	{
		r = *rev2;
		*rev2 = *rev1;
		*rev1 = r;
		rev1--;
		rev2++;
	}
}

/**
 * _strlen - returns the length of a string.
 *
 * @s: a pointer to the string.
 *
 * Return: void.
 */
int _strlen(const char *s)
{
	unsigned int i = 0;

	while (*s != '\0')
	{
		s++;
		i++;
	}
	return (i);
}
