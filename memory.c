#include "shell.h"

/**
 * bfree - frees a pointer and sets the address to NULL
 * @ptr: address of the pointer to free
 *
 * Return: 1 if freed, 0 otherwise
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
}
	return (0);
}
