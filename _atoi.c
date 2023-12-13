#include "shell.h"

/**
 *is_interactive - checks if the shell is in interactive mode
 *@info: pointer to the shell information structure
 *
 *Return: 1 if interactive mode, 0 otherwise
 */
int is_interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 *is_delimiter - checks if a character is a delimiter
 *@ch: the character to check
 *@delim: the delimiter string
 *Return: 1 if true, 0 if false
 */
int is_delimiter(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 *is_alpha - checks for alphabetic character
 *@ch: the character to check
 *Return: 1 if ch is alphabetic, 0 otherwise
 */

int is_alpha(int ch)
{
	if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *str_to_int - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int str_to_int(char *str)
{
	int i, sign = 1, state = 0, num;
	unsigned int value = 0;

	for (i = 0; str[i] != '\0' && state != 2; i++)
	{
		if (str[i] == '-')
			sign *= -1;

		if (str[i] >= '0' && str[i] <= '9')
		{
			state = 1;
			value *= 10;
			value += (str[i] - '0');
		}
		else if (state == 1)
			state = 2;
	}

	if (sign == -1)
		num = -value;
	else
		num = value;

	return (num);
}
