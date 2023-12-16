#include "shell.h"

/**
 * get_environ - return copy of string array
 * @info: parameter
 * Return: void
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = lists_to_strings(info->env);
		info->env_changed = 0;
	}
	return (info->environ);
}

/**
 * _setenv - modify or initialize new environment
 * @info: parameter
 * @str1: string
 * @val: string value
 * Return: void
 */
int _setenv(info_t *info, char *str1, char *val)
{
	list_t *x;
	char *buffer = NULL;
	char *y;

	if (!str1 || !val)
		return (0);

	buffer = malloc(_strlen(str1) + _strlen(val) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, str1);
	_strcat(buffer, "=");
	_strcat(buffer, val);
	x = info->env;
	while (x)
	{
		y = starts_with(x->str, str1);
		if (y && *y == '+')
		{
			free(x->str);
			x->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		x = x->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}

/**
 * _unsetenv - remove environ variable
 * @info: parameter
 * @stvar: string environ variable property
 * Return: void
 */
int _unsetenv(info_t *info, char *stvar)
{
	char *x;
	list_t *y = info->env;
	size_t z = 0;

	if (!y || !stvar)
		return (0);

	while (y)
	{
		x = starts_with(y->str, stvar);
		if (x && *x == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), z);
			z = 0;
			y = info->env;
			continue;
		}
		y = y->next;
		z++;
	}
	return (info->env_changed);
}
