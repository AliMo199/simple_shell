#include "shell.h"

/**
 *_myhistory - shows the history list, one command per line, preceded
 *             with line numbers, starting at 0.
 *@data: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: Always 0
 */
int _myhistory(info_t *data)
{
	print_list(data->history);
	return (0);
}

/**
 *unset_alias - removes alias from string
 *@data: parameter struct
 *@str: the string alias
 *
 *Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *data, char *str)
{
	char *p, c;
	int res;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	res = delete_node_at_index(&(data->alias),
		get_node_index(data->alias, node_starts_with(data->alias, str, -1)));
	*p = c;
	return (res);
}

/**
 *set_alias - assigns alias to string
 *@data: parameter struct
 *@str: the string alias
 *
 *Return: Always 0 on success, 1 on error
 */
int set_alias(info_t *data, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(data, str));

	unset_alias(data, str);
	return (add_node_end(&(data->alias), str, 0) == NULL);
}

/**
 *print_alias - displays an alias string
 *@node: the alias node
 *
 *Return: Always 0 on success, 1 on error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (a = node->str; a <= p; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}

	return (1);
}

/**
 *_myalias - replicates the alias builtin (man alias)
 *@data: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: Always 0
 */
int _myalias(info_t *data)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (data->argc == 1)
	{
		node = data->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}

		return (0);
	}

	for (i = 1; data->argv[i]; i++)
	{
		p = _strchr(data->argv[i], '=');
		if (p)
			set_alias(data, data->argv[i]);
		else
			print_alias(node_starts_with(data->alias, data->argv[i], '='));
	}

	return (0);
}
