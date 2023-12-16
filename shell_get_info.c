#include "shell.h"

/**
 * clear_info - clear or reset info_t structure
 * @info: parameter
 * Return: void
 */
void clear_info(info_t *info)
{
	info->path = NULL;
	info->arg = NULL;
	info->argv = NULL;
	info->argc = 0;
}

/**
 * set_info - prepares and processes command-line arguments
 * @info: parameter
 * @av: argument vector
 * Return: void
 */
void set_info(info_t *info, char **av)
{
	int x = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (!info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}

		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;

		replace_vars(info);
		replace_alias(info);
	}
}

/**
 * free_info -  freeing memory of info_t structure
 * @info: parameter
 * @allmem: free all memory
 * Return: void
 */
void free_info(info_t *info, int allmem)
{
	ffree(info->argv);
	info->argv = NULL;
	info->pth = NULL;
	if (allmem)
	{
		if (!info->cmd_buffer)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
		info->environ = NULL;
		bfree((void **)info->cmd_buffer);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUFFER_FLUSH);
	}
}
