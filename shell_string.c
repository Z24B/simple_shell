#include "shell.h"

/**
 * _strcat - function concatenates 2 strings
 * @dbuf: destination buffer
 * @srcbuf: source buffer
 * Return: void
 */
char *_strcat(char *dbuf, char *srcbuf)
{
	char *x = dbuf;

	while (*dbuf)
		dbuf++;
	while (*srcbuf)
		*dbuf++ = *srcbuf++;
	*dbuf = *srcbuf;
	return (x);
}

/**
 * _starts - checks if string starts with a specified prefix
 * @str: string
 * @substr: substring
 * Return: void
 */
char _starts(const char *str, const chat *substr)
{
	while (*substr)
		if (*substr++ != *str++)
			return (NULL);
	return ((char *)str);
}

/**
 * _strlen - length of string
 * @str: string
 * Return: void
 */
int _strlen(char *str)
{
	int x = 0;

	if (!str)
		return (0);

	while (*str++)
		x++;
	return (x);
}

/**
 * _strcmp - lexicogarphic comparison of 2 strings
 * @str1: first string
 * @str2: second string
 * Return: void
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}
