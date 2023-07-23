#include "shell.h"

/**
 * count_words - counts the number of words in a string
 * @str: the input string
 * @delim: the delimiter string
 *
 * Return: the number of words
 */
static int count_words(char *str, char *delim)
{
	int i, numwords = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		if (!is_delim(str[i], delim) && (is_delim(str[i + 1], delim) || !str[i + 1]))
			numwords++;
	}

	return (numwords);
}

/**
 * allocate_memory - allocates memory for the string array
 * @numwords: the number of words
 *
 * Return: a pointer to the allocated memory
 */
static char **allocate_memory(int numwords)
{
	char **s = malloc((1 + numwords) * sizeof(char *));

	if (!s)
		return (NULL);

	return (s);
}

/**
 * split_string - splits the string into words and stores them in the array
 * @str: the input string
 * @delim: the delimiter string
 * @s: the string array
 *
 * Return: 1 on success, 0 on failure
 */
static int split_string(char *str, char *delim, char **s)
{
	int i, j, k, m, numwords = 0;

	for (i = 0, j = 0; s[j] != NULL; j++)
	{
		while (is_delim(str[i], delim))
			i++;
		k = 0;
		while (!is_delim(str[i + k], delim) && str[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (0);
		}
		for (m = 0; m < k; m++)
			s[j][m] = str[i++];
		s[j][m] = 0;
	}

	return (1);
}

/**
 * strtow - splits a string into words. Repeat delimiters are ignored
 * @str: the input string
 * @delim: the delimiter string
 *
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow(char *str, char *delim)
{
	int numwords;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);

	if (!delim)
		delim = " ";

	numwords = count_words(str, delim);
	if (numwords == 0)
		return (NULL);

	s = allocate_memory(numwords);
	if (!s)
		return (NULL);

	if (!split_string(str, delim, s))
		return (NULL);

	s[numwords] = NULL;
	return (s);
}
