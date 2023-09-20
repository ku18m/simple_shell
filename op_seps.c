#include "main.h"

/**
 * countoperators - counts op's in the given line.
 *
 * @line: given line.
 * @op: op to count.
 *
 * Return: number of ops.
 */
int countoperators(char *line, char op)
{
	int i, count = 0;

	for (i = 0; line[i]; i++)
	{
		if (line[i] == op)
		{
			if (op == '$')
				i++;
			count++;
		}
	}
	return (count);
}

/**
 * op_seps - separate op's with spaces.
 *
 * @data: pointer to data structure.
 *
 * Return: pointer to separated line.
 */
char *op_seps(data_t *data)
{
	int operatorCount, newLen, jump, i, j, len = _strlen(data->lineptr);
	char *newLine, *line = data->lineptr;
	char operators[OP_COUNT] = {'|', '&', ';', '$'};

	operatorCount = 0;
	for (j = 0; j < OP_COUNT; j++)
		operatorCount += countoperators(line, operators[j]);
	if (operatorCount == 0)
		return (line);
	newLen = len + operatorCount * 2;
	newLine = malloc(sizeof(char) * (newLen + 1));
	for (i = 0, jump = 0; i < len; i++)
	{
		op_chars(line, newLine, &i, &jump);
		if (line[i] == operators[3])
			op_special(line, newLine, &i, &jump);
		newLine[i + jump] = line[i];
	}
	newLine[i + jump] = '\0';
	free(line);
	return (newLine);
}
