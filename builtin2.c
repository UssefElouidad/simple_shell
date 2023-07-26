#include "shell.h"
/**
 * _myhistory - prints the history list, a command by line
 * precede with line numbers, starting at 0.
 * @info: Structure containing potential arguments
 * Used for maintaining constant function prototype.
 * Return: Always 0
 */

int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - it removes an alias from the alias linked list
 * @info: parameter struct
 * @str: the string alias to be removed
 *
 * Return: 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *equal_sign, temp_char;
	int ret;

	equal_sign = _strchr(str, '=');

	if (!equal_sign)
		return (1);

	temp_char = *equal_sign;
	*equal_sign = '\0';

	ret = delete_node_at_index(
		&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1))
	);

	*equal_sign = temp_char;

	return (ret);
}
/**
 * set_alias - function that sets or updates an alias in the alias linked list
 * @info: parameter struct
 * @str: the string alias to be set or updated
 *
 * Return: 0 on success, 1 on failure.
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}
/**
 * print_alias - a function that prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
 */

int print_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		if (p)
		{
			for (a = node->str; a < p; a++)
				_putchar(*a);
			_putchar('\'');
			_puts(p + 1);
			_putchar('\'');
			_putchar('\n');
			return (0);
		}
	}
	return (1);
}
/**
 * _myalias - function thta mimics the alias builtin (man alias)
 * @info: the structure containing potential arguments
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myalias(info_t *info)
{
	int i = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}

	for (i = 1; i < info->argc && info->argv[i]; i++)
	{
		p = _strchr(info->argv[i], '=');
		if (p)
			set_alias(info, info->argv[i]);
		else
		{
			node = node_starts_with(info->alias, info->argv[i], '=');
			if (node)
				print_alias(node);
		}
	}

	return (0);
}

