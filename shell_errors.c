#include "shell.h"

/**
 * _eputs - print input string
 * @str: string
 * Return: void
 */
void _eputs(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_eputchar(str[x]);
		x++;
	}
}

/**
 * _eputchar - character c to stderr
 * @ch: character
 * Return: void
 */
int _eputchar(char ch)
{
	static int x;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || x >= WRITE_BUFFER_SIZE)
	{
		write(2, buffer, x);
		x = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[x++] = ch;
	return (1);
}

/**
 * _putsfd - print input string
 * @str: string
 * @fd: file descriptor
 * Return: void
 */
int _putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (00);
	while (*str)
	{
		x += _putsfd(*str++, fd);
	}
	return (x);
}

/**
 * _putfd - character c to fd
 * @ch: character
 * @fd: file descriptor
 * Return: void
 */
int _putfd(char ch, int fd)
{
	static int x;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || x >= WRITE_BUFFER_SIZE)
	{
		write(fd, buffer, x);
		x = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[x++] = ch;
	return (1);
}
