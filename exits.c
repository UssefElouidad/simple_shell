#include "shell.h"

/**
 * _strncpy - work exactly like strncpy.
 * @dest: string of setination.
 * @src: string of source.
 * @n: size of second string.
 * Return: Always 0.
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i;

	for (i = 0; i < n && src[i] != '\0'; i++)
	*(dest + i) = *(src + i);
	for (; i < n; i++)
		*(dest + i) = '\0';
	return (dest);
}

/**
 * _strncat - fonction that appends src string to the dest string.
 * @dest: string destination.
 * @src: source string.
 * @n: number of bytes used.
 * Return: Always 0
 */
char *_strncat(char *dest, char *src, int n)
{
	int ld = 0, ls = 0;

	while (*(dest + ld) != '\0')
		ld++;
	while (*(src + ls) != '\0' && ld < 97 && ls < n)
	{
		*(dest + ld) = *(src + ls);
		ld++;
		ls++;
	}
	*(dest + ld) = '\0';
	return (dest);
}

/**
 * _strchr - a function that locates a character in a string.
 * @c: character ito locate.
 * @s: ths string to look in.
 * Return: int the string.
 */
char *_strchr(char *s, char c)
{
	int i = 0;

	for (; s[i] >= '\0'; i++)
	{
		if (s[i] == c)
			return (&s[i]);
	}
	return (0);
}

