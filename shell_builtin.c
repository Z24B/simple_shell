#include "shell.h"

/**
 * exit_shell - function to exit shell
 * @info: parameter
 * Return: void
 */
int exit_shell(info_t *info)
{
	int x;

	if (info->argv[1])
	{
		x = _erratoi(info->argv[1]);
		if (x == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * change_cd - changes current directory
 * @info: parameter
 * Return: void
 */
int change_cd(info_t *info)
{
	char *x, *dr, buffer[1024];
	int ch_dir;

	x = getcwd(buffer, 1024);
	if (!x)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dr = _getenv(info, "Home=");
		if (!dr)
			ch_dir = chdir((dr = _getenv(info, "PWD=")) ? dr : "/");
		else
		ch_dir = chdir(dr);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		ch_dir = chdir((dr = _getenv(info, "OLDPWD=")) ? dr : "/");
	}
	else
		ch_dir = chdir(info->argv[1]);
	if (ch_dir == -1)
	{
		print_error(info, "cannot change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * help_cd - Display a help message
 * @info: parameter
 * Return: void
 */
int help_cd(info_t *info)
{
	char **array;

	array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*array);
	return (0);
}
