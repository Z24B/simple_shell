#include "shell.h"

/**
 * handle_sigint - block ctrl-c
 * @num: signal number
 * Return: void
 */
void handle_sigint(__attribute__((unused))int num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFFER_FLUSH);
}

/**
 * input_buffer - read user input
 * @info: parameter
 * @buffer: buffer address
 * @length: len var
 * Return: void
 */
ssize_t input_buffer(info_t *info, char *buffer, size_t *length)
{
	ssize_t x = 0;
	size_t len = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sigint);
#if USE_GETLINE
		x = getline(buffer, &len, stdin);
#else
		x = _getline(info, buffer, &len);
#endif
		if (x > 0)
		{
			if ((*buffer)[x - 1] == '\n')
			{
				(*buffer)[x - 1] = '\0';
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			{
				*length = x;
				info->cmd_buffer = buffer;
			}
		}
	}
	return (x);
}

/**
 * get_input - buffer initialisation, readinf input, handling command
 * chain and no command chains
 * @info: parameter
 * Return: void
 */
ssize_t get_input(info_t *info)
{
	ssize_t x = 0;
	char **buf = &(info->arg), *var;
	static char *buf1;
	static size_t a, b, len;

	_putchar(BUFFER_FLUSH);
	x = input_buffer(info, &buf1, &len);
	if (x == -1)
		return (-1);
	if (len)
	{
		b = a;
		var = bufr + a;

		check_chain(info, buf1, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buf1, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf = var;
		return (_strlen(var));
	}

	*buf = buf1;
	return (x);
}

/**
 * read_buffer - reads buffer
 * @info: parameter
 * @buf: buffer
 * @s: size
 * Return: void
 */
ssize_t read_buffer(info_t *info, char *buf, size_t *s)
{
	ssize_t x = 0;

	if (*s)
		return (0);
	x = read(info->readfd, buf, READ_BUFFER_SIZE);
	if (x >= 0)
		*s = x;
	return (x);
}

/**
 * _getline -  read a line of input from a source
 * @info: parameter
 * @pointer: pointer
 * @len: size
 * Return: void
 */
int _getline(info_t *info, char **pointer, size_t *len)
{
	size_t x;
	ssize_t y = 0, z = 0;
	char *p = NULL, *pp = NULL, *i;
	static char buf[READ_BUFFER_SIZE];
	static size_t r, l;

	p = *pointer;
	if (p && len)
		z = *len;
	if (r == l)
		r = l = 0;

	y = read_buffer(info, buf, &l);
	if (y == -1 || (y == 0 && l == 0))
		return (-1);

	i = _strchr(buf + r, '\n');
	x = i ? 1 + (unsigned int)(i - buf) : l;
	pp = _realloc(p, z, z ? z + x : x + 1);
	if (!pp)
		return (p ? free(p), -1 : -1);

	if (z)
		_strncat(pp, buf + r, x - r);
	else
		_strncpy(pp, buf + r, x - r + 1);

	z += x - r;
	r = x;
	p = pp;

	if (len)
		*len = z;
	*pointer = p;
	return (z);
}
