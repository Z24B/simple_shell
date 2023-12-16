#include "shell.h"

/**
 * _strchr - locate string character
 * @str: string
 * @ch: character
 * Return:void
 */
char _strchr(char *str, char ch)
{
	do {
		if (*str == ch)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}

/**
 * _strncpy - copy string
 * @dstr: string destination
 * @src: string source
 * @num: number of characters
 * Return: void
 */
char _strncpy(char *dstr, char *src, int num)
{
	int x;
	int y;
	char *z = dstr;

	x = 0;
	while (src[x] != '\0' && x < num - 1)
	{
		dstr[x] = src[x];
		x++;
	}
	if (x < num)
	{
		y = x;
		while (y < num)
		{
			dstr[y] = '\0';
			y++;
		}
	}
	return (z);
}

/**
 * _strncat - concatenates 2 strings
 * @str1: first string
 * @str2: second string
 * @num: number of bytes
 * Return: void
 */
char _strncat(char *str1, char *str2, int num)
{
	int x;
	int y;
	char *z = str1;

	x = 0;
	y = 0;
	while (str1[x] != '\0')
		x++;
	while (str2[y] != '\0' && y < num)
	{
		str1[x] = str2[y];
		x++;
		y++;
	}
	if (y < num)
		str1[x] = '\0';
	return (z);
}
