#include "shell.h"

/**
 * get_history_file - file history
 * @info: parameter
 * Return: void
 */
char *get_history_file(info_t *info)
{
	char *buffer, *x;

	x = _getenv(info, "HOME=");
	if (!x)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(x) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, x);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - append or create file
 * @info: parameter
 * Return: void
 */
int write_history(info_t *info)
{
	ssize_t x;
	char *fn = get_history_file(info);
	list_t *y = NULL;

	if (!fn)
		return (-1);

	x = open(fn, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fn);
	if (x == -1)
		return (-1);
	for (y = info->history; y; y = y->next)
	{
		_putsfd(y->str, x);
		_putfd('\n', x);
	}
	_putfd(BUFFER_FLUSH, x);
	close(fd);
	return (1);
}

/**
 * read_history - read file history
 * @info: parameter
 * Return: void
 */
int read_history(info_t *info)
{
	int x, ls = 0, lc = 0;
	ssize_t a, b, c = 0;
	struct stat st;
	char *buf = NULL, *fn = get_history_file(info);

	if (!fn)
		return (0);

	a = open(fn, O_RDONLY);
	free(fn);
	if (a == -1)
		return (0);
	if (!fstat(a, &st))
		c = st.st_size;
	if (c < 2)
		return (0);
	buf = malloc(sizeof(char) * (c + 1));
	if (!buf)
		return (0);
	b = read(a, buf, c);
	buf[c] = 0;
	if (b <= 0)
		return (free(buf), 0);
	close(fd);
	for (x = 0; x < c; x++)
		if (buf[x] == '\n')
		{
			buf[x] = 0;
			build_history_list(info, buf + ls, lc++);
			ls = x + 1;
		}
	if (ls != x)
		build_history_list(info, buf + ls, lc++);
	free(buf);
	info->histcount = lc;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - add entries to list
 * @info: parameter
 * @buffer: buffer
 * @lc: linecount
 * Return: void
 */
int build_history_list(info_t *info, char *buffer, int lc)
{
	list_t *n = NULL;

	if (info->history)
		n = info->history;
	add_node_end(&n, buffer, lc);

	if (!info->history)
		info->history = n;
	return (0);
}

/**
 * renumber_history - renumbers the list
 * @info: parameter
 * Return: void
 */
int renumber_history(info_t *info)
{
	list_t *n = info->history;
	int x = 0;

	while (n)
	{
		n->num = i++;
		n = n->next;
	}
	return (info->histcount = x);
}
