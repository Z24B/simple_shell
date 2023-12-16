#include "shell.h"

/**
 * interactive - if shell is interactive return true
 * @info: pointer
 * Return: void
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readrv <= 2);
}

/**
 * delimeter - check if character is delimeter
 * @chtr: char
 * @dstr: delimeter string
 * Return: void
 */
int delimeter(char chtr, char *dstr)
{
	while (*dstr)
		if (*dstr++ == chtr)
			return (1);
	return (0);
}

/**
 * _alpha - alphabetic character check
 * @chtr: input character
 * Return: void
 */
int _alpha(int chtr)
{
	if ((chtr >= 'a' && chtr <= 'z') || (chtr >= 'A' && chtr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - inverts string to int
 * @str: string
 * Return: void
 */
int _atoi(char *str)
{
	int x, sign = 1, flag = 0, output;
	unsigned int output = 0;

	for (x = 0; str[x] != '\0' && flag != 2; i++)
	{
		if (str[x] == '-')
			sign *= -1;

		if (str[x] >= '0' && str[x] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[x] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}
	if (sign == -1)
		output = -result;
	else
		output = result;
	return (output);
}
