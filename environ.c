#include "shell.h"

/**
 * _myenv - afunction that prints the current environment
 * @info: Structure containing potential arguments.
 * Used for maintaining constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}
/**
 * _getenv - function that gets the value of an environment variable
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * @name: env var name
 * Return: Pointer to the value of the environment variable
 * or NULL if the variable is not found.
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *ptr;

	while (node)
	{
		ptr = starts_with(node->str, name);
		if (ptr && *ptr)
		return (ptr);
		node = node->next;
	}
	return (NULL);
}
/**
 * _mysetenv - a function that sets a new environment variable
 * or modifies an existing one
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguments\n");
		return (1);/* Return error if the number of arguments is not 3*/

	} /*Call the _setenv function to initialize or modify the environment variable*/



	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - a function that emoves an environment variable
 * @info: Structure containing potential arguments
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc < 2)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}


	for (i = 1; i < info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}
/**
 * populate_env_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i = 0;

	for (; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
