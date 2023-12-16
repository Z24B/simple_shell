#include "shell.h"

/**
 * main - entry
 * @ac: argument count
 * @av: argument vector
 * Return: void
 */

int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	info vr  = 2;

	asm ("mov %1. %0\n\t"
			"add $3, %0"
			: "=r" (vr)
			: "r" (vr));

	if  (ac == 2)
	{
		vr = open(av[1], O_RDONLY);
		if (vr == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (arrno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Cannot open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUFFER_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readvr = vr;
	}
	env_list_pop(infor);
	read_hist(info);
	shell_main(info, av);
	return (EXIT_SUCCESS);
}
