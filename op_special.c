#include "main.h"

/**
 * op_special - separate special chars with spaces.
 *
 * @srcLine: given command line.
 * @newLine: new line.
 * @currentIndex: given line index.
 * @jumpidx: new line index.
 *
 * Return: Nothing.
 */
void op_special(char *srcLine, char *newLine, int *currentIndex, int *jumpidx)
{
	int sourceIndex = *currentIndex;
	int newLineIndex = *jumpidx;

	newLine[sourceIndex + (newLineIndex++)] = ' ';
	if (srcLine[sourceIndex + 1] == '$')
	{
		newLine[(sourceIndex++) + newLineIndex] = '$';
		newLine[(sourceIndex++) + newLineIndex] = '$';
	}
	else if (srcLine[sourceIndex + 1] == '?')
	{
		newLine[(sourceIndex++) + newLineIndex] = '$';
		newLine[(sourceIndex++) + newLineIndex] = '?';
	}
	else
	{
		while (srcLine[sourceIndex] != ' ' && srcLine[sourceIndex] != '\n'
			&& srcLine[sourceIndex] != '&'
			&& srcLine[sourceIndex] != '|' && srcLine[sourceIndex] != ';'
			&& srcLine[sourceIndex] != '$' && srcLine[sourceIndex] != '\0')
		{
			newLine[sourceIndex + newLineIndex] = srcLine[sourceIndex];
			sourceIndex++;
		}
	}

	newLine[sourceIndex + (newLineIndex++)] = ' ';

	*currentIndex = sourceIndex;
	*jumpidx = newLineIndex;
}
