#include "shell.h"

/**
 * shell_main - main shell loop
 * @info: info struct
 * @av: argument vector
 * Return: void
 */

int shell_main(info_t *info, char **av)
{
	ssize_t x = 0;
	int builtin = 0;

	while (x != -1 && builtin != -2)
	{
		clearenv(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUFFER_FLUSH);
		x = get_input(info);
		if (x != -1)
		{
			set_info(info, av);
			builtin = find_builtin(info);
			if (builtin == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (builtin == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin);
}

/**
 * find_builtin - finds a builtin command
 * @info: pararmeter
 * Return: void
 */
int find_builtin(info_t *info)
{
	int x, built_in = -1;
	builtin_table builtintbl[] = {
		{"exit", _exit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _unsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtintbl[x].type; x++)
		if (_strcmp(info->argv[0], builtintbl[x].type) == 0)
		{
			info->line_count++;
			built_in = builtintbl[x].func(info);
			break;
		}
	return (built_in);
}

/**
 * find_cmd - find command
 * @info: parameter
 * Return: void
 */
void find_cmd(info_t *info)
{
	char *p = NULL;
	int x, y;

	info->p = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (x = 0, y = 0; info->arg[x]; x++)
		if (!is_delim(info->arg[x], " \t\n"))
			y++;
	if (!y)
		return;

	p = find_path(info, getenv(info, "PATH="), info->argv[0]);
	if (p)
	{
		info->p = p;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
					|| info->argv[0][0] == '/') && find_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}

/**
 * fork_cmd - forks a an exec thread
 * @info: parameter
 * Return: void
 */
void fork_cmd(info_t *info)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("Error:");
		return;
	}
	if (pid == 0)
	{
		if (execve(info->path, info->argv, int get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}
