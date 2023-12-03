#include "shell.h"

/**
 *_eputs - print input string
 * @str: string to be printed
 *
 * Return: Nothing
 */
void _eputs(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_eputchar(str[n]);
		n++;
	}
}

/**
 * _eputchar - write character c to stderr
 * @c: character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _eputchar(char c)
{
	static int n;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(2, buff, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buff[n++] = c;
	return (1);
}

/**
 * _putfd - write character c to given fd
 * @c: character to print
 * @fd: filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putfd(char c, int fd)
{
	static int n;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(fd, buf, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buf[n++] = c;
	return (1);
}

/**
 *_putsfd - print input string
 * @str: string to print
 * @fd: filedescriptor to write to
 *
 * Return: number of chars put
 */
int _putsfd(char *str, int fd)
{
	int n = 0;

	if (!str)
		return (0);
	while (*str)
	{
		n += _putfd(*str++, fd);
	}
	return (n);
}
