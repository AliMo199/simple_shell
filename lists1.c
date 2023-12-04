#include "shell.h"

/**
 * list_len - determine length of linked list
 * @h: pointer to first_node
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * list_to_strings - return array of strings of list->str
 * @head: pointer to first node
 *
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node1 = head;
	size_t i = list_len(head), j;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node1; node1 = node1->next, i++)
	{
		str = malloc(_strlen(node1->str) + 1);
		if (!str)
		{
			for (j = 0; j < i; j++)
				free(strs[j]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node1->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - print all elements of list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * node_starts_with - return node where string start with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to evaluate
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *po = NULL;

	while (node)
	{
		po = starts_with(node->str, prefix);
		if (po && ((c == -1) || (*po == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - get the index of node
 * @head: pointer to list head
 * @node: pointer to node
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t n = 0;

	while (head)
	{
		if (head == node)
			return (n);
		head = head->next;
		n++;
	}
	return (-1);
}
