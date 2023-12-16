#include "shell.h"

/**
 * hist_list - display history list
 * @info: parameter
 * Return: void
 */
int hist_list(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * str_alias - sets alias to a string
 * @info: parameter:
 * @str: string
 * Return: void
 */
int str_alias(info_t *info, char *str)
{
	char *x, y;
	int output;

	x = _strchr(str, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	output = delete_index_node(&(info->alias),
			get_index_node(info->alias, node_start(info->laias, str, -1)));
	*x = y;
	return (output);
}

/**
 * set_str_alias - sets alias to string
 * @info: parameter
 * @str: string
 * Return: void
 */
int set_str_alias(info_t *info, char *str)
{
	char *x;

	x = _strchr(str, '=');
	if (!x)
		return (1);
	if (!*++x)
		return (str_alias(info, str));

	str_alias(info, str);
	return (add_end_node(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - prints an alias string
 * @node: alias node
 * Return: void
 */
int print_alias(list_t *node)
{
	char *x = NULL, *y = NULL;

	if (node)
	{
		x = _strchr(node->str, '=');
		for (y = node->str; y <= x; y++)
			_putchar(*y);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _alias - replicates alias builtin
 * @info: parameter
 * Return: void
 */
int _alias(info_t *info)
{
	int x = 0;
	char *i = NULL;
	list_t *nd = NULL;

	if (info->argc == 1)
	{
		nd = info->alias;
		while (nd)
		{
			print_alias(nd);
			nd = nd->next;
		}
		return (0);
	}
	for (x = 1; info->argv[x]; x++)
	{
		i = _strchr(info->argv[x], '=');
		if (i)
			set_str_alias(info, info->argv[x]);
		else
			print_alias(start_node(info->alias, info->argv[x], '='))
	}
	return (0);
}
