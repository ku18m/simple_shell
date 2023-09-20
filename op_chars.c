#include "main.h"

/**
 * insertChars - assign chars.
 *
 * @nline: created line.
 * @i: line index.
 * @j: newline index.
 * @c: char to assign.
 *
 * Return: Nothing
 */
void insertChars(char *nline, int *i, int *j, char c)
{
	nline[*i + (*j)++] = ' ';
	nline[(*i)++ + *j] = c;
	if (c != ';')
		nline[(*i)++ + *j] = c;
	nline[*i + (*j)++] = ' ';
}

/**
 * op_chars - separate chars with spaces.
 *
 * @line: command line to check.
 * @nline: created line,
 * @idx: line index.
 * @jmp: newline index.
 *
 * Return: Nothing
 */
void op_chars(char *line, char *nline, int *idx, int *jmp)
{
	int i = *idx, j = *jmp;

	if (line[i] == '|' && line[i + 1] == '|')
	{
		insertChars(nline, &i, &j, '|');
	}
	else if (line[i] == '&' && line[i + 1] == '&')
	{
		insertChars(nline, &i, &j, '&');
	}
	else if (line[i] == ';')
	{
		insertChars(nline, &i, &j, ';');
	}
	*idx = i;
	*jmp = j;
}
