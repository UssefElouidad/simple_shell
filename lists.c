#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the newly added node
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_head = malloc(sizeof(list_t));

	if (!new_head)
		return (NULL);

	/* Initialize the new node */
	new_head->num = num;

	if (str)
	{
		new_head->str = _strdup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	else
		new_head->str = NULL;

	/* Update the linked list */
	new_head->next = *head;
	*head = new_head;

	return (new_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @num: node index used by history
 *
 * Return: pointer to the newly added node
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_node = malloc(sizeof(list_t));

	if (!new_node)
		return (NULL);

	/* Initialize the new node */
	new_node->num = num;

	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->str = NULL;

	new_node->next = NULL;

	/* Update the linked list */
	if (!*head)
	{
		*head = new_node;
		return (new_node);
	}

	list_t *node = *head;

	while (node->next)
		node = node->next;

	node->next = new_node;

	return (new_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @h: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *h)
{
	size_t i = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");

		h = h->next;
		i++;
	}

	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	if (!head || !*head)
		return (0);

	/* Delete the first node */
	if (index == 0)
	{
		list_t *node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}

	list_t *node = *head;
	list_t *prev_node = NULL;
	unsigned int i = 0;

	/* Traverse the list to find the node at the given index */
	while (node && i < index)
	{
		prev_node = node;
		node = node->next;
		i++;
	}

	if (!node)
		return (0);

	/* Update the linked list */
	prev_node->next = node->next;
	free(node->str);
	free(node);

	return (1);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	if (!head_ptr || !*head_ptr)
		return;

	list_t *node = *head_ptr;

	while (node)
	{
		list_t *next_node = node->next;

		free(node->str);
		free(node);
		node = next_node;
	}

	*head_ptr = NULL;
}