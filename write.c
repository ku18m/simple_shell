#include "main.h"

/**
 * _puts - prints a string, to a given screen.
 *
 * @s: a pointer to the string.
 * @stream: output screen.
 *
 * Return: void.
 */
void _puts(char *s, int stream)
{
	write(stream, s, _strlen(s));
}

/**
 * _putchar - writes the character c to stdout.
 *
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(STDOUT_FILENO, &c, 1));
}

/**
 * print_number - print numbers.
 *
 * @n: integer to print
 * @stream: output screen.
 *
 * Return: Nothing.
 */
void print_number(int n, int stream)
{
	char buffer[20];
	int i = 0;
	int is_negative = n < 0;

	if (is_negative)
		n *= -1;
	do {
		buffer[i++] = n % 10 + '0';
	} while ((n /= 10) > 0);
	if (is_negative)
		buffer[i++] = '-';
	while (i > 0)
		write(stream, &buffer[--i], 1);
}
