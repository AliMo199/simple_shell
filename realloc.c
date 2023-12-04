#include "shell.h"

/**
 **_memset - fill memory with constant byte
 *@s: pointer to the memory area
 *@b: byte to fill *s with
 *@n: amount of bytes to be filled
 *Return: a pointer to memory area s
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - free string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **s = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(s);
}

/**
 * _realloc - reallocate block of memory
 * @ptr: pointer to previous malloc'ated block
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *pt;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	pt = malloc(new_size);
	if (!pt)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		pt[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (pt);
}
