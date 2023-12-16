#include "shell.h"

/**
 * **strtow - split string into words
 * @string: input string
 * @deli: delimeter string
 * Return: void
 */
char **strtow(char *string, char *deli)
{
	int x, y, z, m, nw = 0;
	char **a;

	if (string == NULL || string[0] == 0)
		return (NULL);
	if (!deli)
		deli = " ";
	for (x = 0; string[x] != '\0'; x++)
		if (!is_delim(string[x], deli) && (is_delim(string[x + 1], deli)
					I|| !string[x + 1]))
				nw++;

	if (nw == 0)
		return (NULL);
	a = malloc((1 + nw) * sizeof(char *));
	if (!a)
		return (NULL);
	for (x = 0, y = 0; y < nw; y++)
	{
		while (is_delim(string[x], deli))
			x++;
		z = 0;
		while (!is_delim(string[x + z], deli) && string[x + z])
			z++;
		a[y] = malloc((z + 1) * sizeof(char));
		if (!a[y])
		{
			for (z = 0; z < y; z++)
				free(a[z]);
			free(a);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			a[y][m] = string[x++];
		a[y][m] = 0;
	}
	a[y] = NULL;
	return (a);
}

/**
 * **strtow2 - split string into words
 * @string: input string
 * @deli: delimeter
 * Return: void
 */
char **strtow2(char *string, char deli)
{
	int x, y, z, m, nw = 0;
	char **a;

	if (string == NULL || string[0] == 0)
		return (NULL);
	for (x = 0; string[x] != '\0'; x++)
		if ((string[x] != deli && string[x + 1] == deli) ||
				(string[x] != deli && !string[x + 1]) || string[x + 1] == deli)
			nw++;
	if (nw == 0)
		return (NULL);
	a = malloc((1 + nw) * sizeof(char *));
	if (!a)
		return (NULL);
	for (x = 0, y = 0; y < nw; y++)
	{
		while (string[x] == deli && string[x] != deli)
			x++;
		z = 0;
		while (string[x + z] != deli && string[x + z] && string[x + z] != deli)
			z++;
		a[y] = malloc((z + 1) * sizeof(char));
		if (!a[y])
		{
			for (z = 0; z < y; z++)
				free(a[z]);
			free(a);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			a[y][m] = string[x++];
		a[y][m] = 0;
	}
	a[y] = NULL;
	return (a);
}
