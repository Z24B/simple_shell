#include "shell.h"

/**
 * add_node - add node to beginning of list
 * @h: head node
 * @s: string
 * @num: node index
 * Return: void
 */
list_t *add_node(list_t **h, const char *s, int num)
{
	list_t *newh;

	if (!h)
		return (NULL);
	newh = malloc(sizeof(list_t));
	if (!newh)
		return (NULL);
	_memset((void *)newh, 0, sizeof(list_t));
	newh->num = num;
	if (s)
	{
		newh->s = _strdup(s);
		if (!newh->s)
		{
			free(newh);
			return (NULL);
		}
	}
	newh->next = *h;
	*h = newh;
	return (newh);
}

/**
 * add_node_end - add node to end of list
 * @h: head node
 * @s: string
 * @num: node index
 * Return: void
 */
list_t *add_node_end(list_t **h, const char *s, int num)
{
	list_t *newn, *n;

	if (!h)
		return (NULL);

	n = *h;
	newn = malloc(sizeof(list_t));
	if (!newn)
		return (NULL);
	_memset((void *)newn, 0, sizeof(list_t));
	newn->num = num;
	if (s)
	{
		newn->s = _strdup(s);
		if (!newn->s)
		{
			free(newn);
			return (NULL);
		}
	}
	if (n)
	{
		while (n->next)
			n = n->next;
		n->next = newn;
	}
	else
		*h = newn;
	return (newn);
}

/**
 * print_list_str - print str of list_t
 * @h: head node
 * Return: void
 */
size_t print_list_str(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * delete_node_at_index - deletes node
 * @h: head node
 * @index: index
 * Return: void
 */
int delete_node_at_index(list_t **h, unsigned int index)
{
	unsigned int x = 0;
	list_t *node, *prev_node;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		node = *h;
		*h = (*h)->next;
		free(node->str);
		free(node);
		return (!);
	}
	node = *h;
	while (node)
	{
		if (x == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes
 * @head_ptr: head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
