#include "shell.h"

/**
 * _env - print current environment
 * @info: parameter
 * Return: void
 */
int _env(info_t *info)
{
	print_lst(info->env);
	return (0);
}

/**
 * get_env - gets variable value
 * @info: parameter
 * @name: env var name
 * Return: void
 */
char *get_env(info_t *info, const char *name)
{
	char *x;
	list_t *y = info->env;

	while (y)
	{
		x = starts_with(y->str, name);
		if (x && *x)
			return (x);
		y = y->next;
	}
	return (NULL);
}

/**
 * set_env - start new environment variable
 * @info: parameter
 * Return: void
 */
int set_env(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (set_env(info, info->argv[1], info->argv[2]))
		return (0);
	return (0);
}

/**
 * rmv_env - remove environment variable
 * @info: parameter
 * Return: void
 */
int rmv_env(info_t *info)
{
	int x;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (x = 1; x <= info->argc; x++)
		_unsetenv(info, info->argv[x]);

	return (0);
}

/**
 * pop_env - populate env list
 * @info: parameter
 * Return: void
 */
int pop_env(info_t *info)
{
	list_t *x = NULL;
	size_t y;

	for (y = 0; environ[y]; y++)
		add_node_end(&x, environ[y], 0);
	info->env = x;
	return (0);
}
