#include "shell.h"

/**
 * _myenv - print current environment
 * @info: Structure containing potential args. Used to maintain
 *          constant func prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - get value of environ variable
 * @info: Structure containing potential args. Used to maintain
 * @name: env var name
 *
 * Return: value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node1 = info->env;
	char *p;

	while (node1)
	{
		p = starts_with(node1->str, name);
		if (p && *p)
			return (p);
		node1 = node1->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize new environment variable,
 *             or modify existing one
 * @info: Structure containing potential args. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * populate_env_list - populate environment linked list
 * @info: Structure containing potential args. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node1 = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node1, environ[i], 0);
	info->env = node1;
	return (0);
}
