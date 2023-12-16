#include "shell.h"

/**
 * is_chain - test current char
 * @info: parameter
 * @buffer: buffer
 * @p: position
 * Return: void
 */
int is_chain(info_t *info, char *buffer, size_t *p)
{
	size_t x = *p;

	if (buffer[x] == '|' && buffer[x + 1] == '|')
	{
		buffer[x] = 0;
		x++;
		info->cmd_buf_type = COMMAND_OR;
	}
	else if (buffer[x] == '&' && buffer[x + 1] == '&')
	{
		buffer[x] = 0;
		x++;
		info->cmd_buf_type = COMMAND_AND;
	}
	else if (buffer[x] == ';')
	{
		buffer[x] = 0;
		info->cmd_buf_type = COMMAND_CHAIN;
	}
	else
		return (0);
	*p = x;
	return (1);
}

/**
 * check_chain - last status checks
 * @info: parameter
 * @buffer: buffer
 * @p: position
 * @start: start position
 * @len: length
 * Return: void
 */
void check_chain(info_t *info, char *buffer, size_t *p,
		size_t start, size_t len)
{
	size_t x = *p;

	if (info->cmd_buf_type == COMMAND_AND)
	{
		if (info->status)
		{
			buffer[start] = 0;
			x = len;
		}
	}
	*p = x;
}

/**
 * replace_alias - replace aliases tokenized string
 * @info: parameter
 * Return: void
 */
int replace_alias(info_t *info)
{
	int x;
	char *p;
	list_t *n;

	for (x = 0; x < 10; x++)
	{
		n = starts_with(info->alias, info->argv[0], '=');
		if (!n)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars -  replaces the vars in string
 * @info: parameter
 * Return: void
 */
int replace_vars(info_t *info)
{
	int x = 0;
	list_t *n;

	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			replace_string(&(info->argv[x]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		n = node_starts_with(info->env, &info->argv[x][1], '=');
		if (n)
		{
			replace_string(&(info->argv[x]),
					_strdup(_strchr(n->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replace old string
 * @oldstr: old string
 * @newstr: new string
 * Return: void
 */
int replace_string(char **oldstr, char *newstr)
{
	free(*oldstr);
	*oldstr = newstr;
	return (1);
}
