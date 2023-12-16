#include "shell.h"

/**
 * get_node_index - get index of node
 * @h: list head
 * @n: node
 * Return: void
 */
ssize_t get_node_index(list_t *h, list_t *n)
{
	size_t x = 0;

	while (h)
	{
		if (h == n)
			return (x);
		h = h->next;
		x++;
	}
	return (-1);
}

/**
 * list_len - linked list length
 * @h: head node
 * Return: void
 */
size_t list_len(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		h = h->next;
		x++;
	}
	return (x);
}

/**
 * node_starts_with - return node start with prefix
 * @h: head node
 * @pfx: string
 * @c: character
 * Return: void
 */
list_t *node_starts_with(list_t *h, char *pfx, char c)
{
	char *x = NULL;

	while (h)
	{
		x = starts_with(h->str, pfx);
		if (x && ((c == -1) || (*x == c)))
			return (h);
		h = h->next;
	}
	return (NULL);
}

/**
 * list_to_strings - return array of strings
 * @h: head node
 * Return: void
 */
char **list_to_strings(list_t *h)
{
	list_t *node = h;
	size_t x = list_len(h), j;
	char **s1;
	char *s2;

	if (!h || !x)
		return (NULL);
	s1 = malloc(sizeof(char *) * (x + 1));
	if (!s1)
		return (NULL);
	for (x = 0; node; node = node->next, x++)
	{
		s2 = malloc(_strlen(node->str) + 1);
		if (!s2)
		{
			for (j = 0; j < x; j++)
				free(s1[j]);
			free(s1);
			return (NULL);
		}

		s2 = _strcpy(s2, node->str);
		s1[x] = s2;
	}
	s1[x] = NULL;
	return (s1);
}

/**
 * print_list - prints all elements of list_t
 * @h: head node
 * Return: void
 */
size_t print_list(const list_t *h)
{
	size_t x = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		x++;
	}
	return (x);
}
