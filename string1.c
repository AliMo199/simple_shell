#include "shell.h"

/**
 * _strcpy - copy string
 * @dest: destination
 * @src: source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *dest, char *src)
{
	int n = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[n])
	{
		dest[n] = src[n];
		n++;
	}
	dest[n] = 0;
	return (dest);
}

/**
 * _strdup - duplicate string
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	ret = malloc(sizeof(char) * (len + 1));
	if (!ret)
		return (NULL);
	for (len++; len--;)
		ret[len] = *--str;
	return (ret);
}

/**
 *_puts - print input string
 *@str: string to print
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int n = 0;

	if (!str)
		return;
	while (str[n] != '\0')
	{
		_putchar(str[n]);
		n++;
	}
}

/**
 * _putchar - write character c to stdout
 * @c: character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int n;
	static char buff[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || n >= WRITE_BUF_SIZE)
	{
		write(1, buff, n);
		n = 0;
	}
	if (c != BUF_FLUSH)
		buff[n++] = c;
	return (1);
}
