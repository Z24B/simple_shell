#include "shell.h"

/**
 * duplicate - duplicate characters
 * @path: PATH string
 * @str: starting index
 * @stop: stopping index
 * Return: void
 */
char duplicate(char *path, int str, int stop)
{
	static char buffer[1024];
	int x = 0;
	int y = 0;

	for (y = 0, x = start; x < stop; x++)
		if (path[x] != ':')
			buffer[y++] = path[x];
	buffer[y] = 0;
	return (buffer);
}

/**
 * exe_cmd - if file is executable command
 * @info: info struct
 * @path: file path
 * Return: void
 */
int exe_cmd(info_t *info, char *path)
{
	struct stat x;

	(void)info;
	if (!path || stat(path, &x))
		return (0);

	if (x.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * path_find - find command in path string
 * @info: info struct
 * @pstr: PATH string
 * @command: command to find
 * Return: void
 */
char *path_find(info_t *info, char *pstr, char *command)
{
	int x = 0;
	int p = 0;
	char *path;

	if (!pstr)
		return (NULL);
	if ((_strlen(command) > 2) && starts_with(command, "./"))
	{
		if (exe_cmd(info, command))
			return (command);
	}
	while (1)
	{
		if (!pstr[x] || pstr[x] == ':')
		{
			path = duplicate(pstr, p, x);
			if (!*path)
				_strcat(path, command);
			else
			{
				_strcat(path, "/");
				_strcat(path, command);
			}
			if (exe_cmd(info, path))
				return (path);
			if (!pstr[x])
				break;
			p = x;
		}
		x++;
	}
	return (NULL);
}
