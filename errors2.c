#include "shell.h"

/**
 * _erratoi - a function that converts a string to an integer
 * @s: the string to be converted
 *
 * Return: The converted number if valid, otherwise -1 on error
 */
int _erratoi(char *s)
{
	int i = 0;
	unsigned long int result = 0;
	int sign = 1;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}

	for (i = 0; s[i] != '\0'; i++)
	{

		if (s[i] >= '0' && s[i] <= '9')
		{
			result *= 10;
			result += (s[i] - '0');


			if (result > INT_MAX)
				return (-1);
		}
		else
		{

			return (-1);
		}
	}


	return (sign * (int)result);
}
/**
 * print_error - function that prints an error message
 * @info: the parameter & return info struct.
 * @estr: string containing specified error type.
 * Return: 0 if no numbers in string, converted number otherwis
 * -1 on error
 */
void print_error(info_t *info, char *estr)
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
 * print_d - function that prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the file descriptor to write to
 *
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = (fd == STDERR_FILENO) ? _eputchar : _putchar;
	int count = 0;

	if (input < 0)
	{
		__putchar('-');
		count++;
		input = -input;
	}

	if (input == 0)
		return (__putchar('0') + 1);

	int temp = input;
	int num_digits = 0;

	while (temp != 0)
	{
		temp /= 10;
		num_digits++;
	}

	while (num_digits--)
	{
		int divisor = 1;

		for (int i = 1; i <= num_digits; i++)
			divisor *= 10;

		int digit = input / divisor;

		__putchar('0' + digit);
		count++;

		input %= divisor;
	}

	return (count);
}

/**
 * convert_number - a function that convert numbers
 * @num: number to convert
 * @base: the base.
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = (num < 0 && !(flags & CONVERT_UNSIGNED)) ? -num : num;

	array = (flags & CONVERT_LOWERCASE) ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (num < 0 && !(flags & CONVERT_UNSIGNED))
		sign = '-';

	if (sign)
		*--ptr = sign;
	return (ptr);
}
/**
 * remove_comments - function that replaces first instance of '#' with '\0'
 * @buf: address of the string to modify.
 *
 * Return: Always 0
 */
void remove_comments(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
	{
		if (buf[i] == '#' && (i == 0 || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
	}
}
