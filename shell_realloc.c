#include "shell.h"

/**
 * _memset - set bytes of memory
 * @pn: pointer
 * @byte: byte to fill
 * @num: number of bytes
 * Return: void
 */
char *_memset(char *pn, char byte, unisgned int num)
{
	unsigned int x;

	for (x = 0; x < num; x++)
		pn[x] = byte;
	return (pn);
}

/**
 * _free - free string
 * @s: string of strings
 * Return: void
 */
void _free(char **s)
{
	char **x = s;

	if (!s)
		return;
	while (*s)
		free(*s++);
	free(x);
}

/**
 * _realloc - reallocates a block of memory
 * @pointer: pointer
 * @old: byte size of previous block
 * @new: byte size of new block
 * Return: void
 */
void *_realloc(void *pointer, unsigned int old, unsigned int new)
{
	char *x;

	if (!pointer)
		return (malloc(new));
	if (!new)
		return (free(pointer), NULL);
	if (new == old)
		return (pointer);

	x = malloc(new);
	if (!x)
		return (NULL);

	old = old < new ? old : new;
	while (old--)
		x[old] = ((char *)pointer)[old];
	free(pointer);
	return (x);
}
