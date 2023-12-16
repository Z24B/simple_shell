#include "shell.h"

/**
 * print_error - print error message
 * @info: parameter
 * @str: string
 * Return: void
 */
void print_error(info_t *info, char *str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * _erratoi - converts a string to an integer
 * @str: string
 * Return: void
 */
int _erratoi(char *str)
{
	int x = 0;
	unsigned long int y = 0;

	if (*str == '+')
		str++;
	for (x = 0; str[x] != '\0'; x++)
	{
		if (str[x] >= '0' && str[x] <= '9')
		{
			y *= 10;
			y += (str[x] - '0');
			if (y > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (y);
}

/**
 * print_d - function prints a decimal (integer) number (base 10)
 * @input: input
 * @fd: file descriptor
 * Return: void
 */
int print_d(int input, int fd)
{
	unsigned int x, y;
	int a, b = 0;
	int (*__putchar)(char) = _putchar;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		x = -input;
		__putchar('-');
		b++;
	}
	else
		x = input;
	y = x;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (x / a)
		{
			__putchar('0' + y / a);
			b++;
		}
		y %= a;
	}
	__putchar('0' + y);
	b++;

	return (b);
}

/**
 * convert_number - converter
 * @num: number
 * @b: base
 * @f: argument flags
 * Return: void
 */
char *convert_number(long int num, int b, int f)
{
	char *p;
	char sign = 0;
	unsigned long n = num;
	static char *array;
	static char buffer[50];

	if (!(f & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	array = f & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buffer[49];
	*p = '\0';

	do {
		*--p = array[n % b];
		n /= b;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}

/**
 * remove_comments - replace # with '\0'
 * @str: string
 * Return: void
 */
void remove_comments(char *str)
{
	int x;

	for (x = 0; str[x] != '\0'; x++)
		if (str[x] == '#' && (!x || str[x - 1] == ' '))
		{
			str[x] = '\0';
			break;
		}
}
