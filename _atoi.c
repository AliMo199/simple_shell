#include "shell.h"

/**
 *interactive - checks if shell is in interactive mode
 *@data: struct pointer
 *
 *Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *data)
{
	return (isatty(STDIN_FILENO) && data->readfd <= 2);
}

/**
 *is_delim - verifies if character is a delimeter
 *@ch: the char to verify
 *@delim: the delimeter string
 *Return: 1 if true, 0 if false
 */
int is_delim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 *_isalpha - determines if character is alphabetic
 *@ch: The character to input
 *Return: 1 if ch is alphabetic, 0 otherwise
 */

int _isalpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - transforms a string to an integer
 *@str: the string to be transformed
 *Return: 0 if no numbers in string, transformed number otherwise
 */

int _atoi(char *str)
{
	int i, sign = 1, state = 0, output;
	unsigned int num = 0;

	for (i = 0; str[i] != '\0' && state != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			state = 1;
			num *= 10;
			num += (str[i] - '0');
		}
		else if (state == 1)
			state = 2;
	}

	if (sign == -1)
		output = -num;
	else
		output = num;

	return (output);
}
