#include "shell.h"

/**
 * _putchar - character to stdout
 * @ch: character
 * Return: void
 */
int _putchar(char ch)
{
	static int x;
	static char buffer[WRITE_BUFFER_SIZE];

	if (ch == BUFFER_FLUSH || X >= WRITE_BUFFER_SIZE)
	{
		write(1, buffer, x);
		x = 0;
	}
	if (ch != BUFFER_FLUSH)
		buffer[x++] = ch;
	return (1);
}

/**
 * _puts - print input string
 * @str: string
 * Return: void
 */
void _puts(char *str)
{
	int x = 0;

	if (!str)
		return;
	while (str[x] != '\0')
	{
		_putchar(str[x]);
		x++;
	}
}

/**
 * _strcpy - copy string
 * @dstr: destination
 * @src: source
 * Return: void
 */
char *_strcpy(char *dstr, char *src)
{
	int x = 0;

	if (dstr == src || src == 0)
		return (dest);
	while (src[x])
	{
		dstr[x] = src[x];
		x++
	}
	dstr[x] = 0;
	return (dstr);
}

/**
 * _strdup - duplicates string
 * @str: string
 * Return: void
 */
char *_strdup(const char *str)
{
	int len = 0;
	char *x;

	if (str == NULL)
		return (NULL);
	while (*str++)
		len++;
	x = malloc(sizeof(char) * (len + 1));
	if (!x)
		return (NULL);
	for (len++; len--;)
		x[len] = *--str;
	return (x);
}
