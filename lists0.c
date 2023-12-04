#include "shell.h"

/**
 * add_node - add node to start of list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node indx used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *n_head;

	if (!head)
		return (NULL);
	n_head = malloc(sizeof(list_t));
	if (!n_head)
		return (NULL);
	_memset((void *)n_head, 0, sizeof(list_t));
	n_head->num = num;
	if (str)
	{
		n_head->str = _strdup(str);
		if (!n_head->str)
		{
			free(n_head);
			return (NULL);
		}
	}
	n_head->next = *head;
	*head = n_head;
	return (n_head);
}

/**
 * add_node_end - add node to end of list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node indx used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *n_node, *node1;

	if (!head)
		return (NULL);

	node1 = *head;
	n_node = malloc(sizeof(list_t));
	if (!n_node)
		return (NULL);
	_memset((void *)n_node, 0, sizeof(list_t));
	n_node->num = num;
	if (str)
	{
		n_node->str = _strdup(str);
		if (!n_node->str)
		{
			free(n_node);
			return (NULL);
		}
	}
	if (node1)
	{
		while (node1->next)
			node1 = node1->next;
		node1->next = n_node;
	}
	else
		*head = n_node;
	return (n_node);
}

/**
 * print_list_str - print only str element of list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t n = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		n++;
	}
	return (n);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prv_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (i == index)
		{
			prv_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		prv_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - free all nodes of list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node1, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node1 = head;
	while (node1)
	{
		next_node = node1->next;
		free(node1->str);
		free(node1);
		node1 = next_node;
	}
	*head_ptr = NULL;
}
