#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the target string to be copied to
 *@src: the source string
 *@n: the number of characters to be copied
 *Return: the copied string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *t = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}

	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (t);
}

/**
 **_strncat - joins two strings
 *@dest: the first string
 *@src: the second string
 *@n: the maximum amount of bytes to be used
 *Return: the joined string
 */
char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *t = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}

	if (j < n)
		dest[i] = '\0';
	return (t);
}

/**
 **_strchr - finds a character in a string
 *@s: the string to be searched
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
