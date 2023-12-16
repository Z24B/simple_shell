#include "shell.h"

/**
* free_ptr - free pointer and NULL address
* @pointer: pointer address
* Return: void
*/

int free_ptr(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
