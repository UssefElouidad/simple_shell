#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0';
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * get_input - a function that gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *chain_buf; /* The ';' command chain buffer */
	static size_t chain_pos, chain_len;
	ssize_t bytes_read = 0;
	char **arg_buf = &(info->arg), *cmd_start;

	_putchar(BUF_FLUSH);
	bytes_read = input_buf(info, &chain_buf, &chain_len);

	if (bytes_read == -1) /* EOF */
		return (-1);

	if (chain_len) /* We have commands left in the chain buffer */
	{
		size_t cmd_end = chain_pos; /* Initialize new iterator to current*/

		cmd_start = chain_buf + chain_pos; /* Get pointer for return */

		check_chain(info, chain_buf, &cmd_end, chain_pos, chain_len);

		while (cmd_end < chain_len) /* Iterate to semicolon or end of chain buffer */
		{
			if (is_chain(info, chain_buf, &cmd_end))
				break;
			cmd_end++;
		}

		chain_pos = cmd_end + 1; /* Increment past nulled ';'' */

		if (chain_pos >= chain_len) /* Reached the end of buffer? */
		{
			chain_pos = chain_len = 0; /* Reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*arg_buf = cmd_start; /* Pass back pointer to the current command position */
		return (_strlen(cmd_start)); /* Return length of the current command */
	}

	*arg_buf = chain_buf; /* Otherwise, it's not chain, so pass back buffer*/
	return (bytes_read); /* Return length of the buffer from _getline() */
}

/**
 * read_buf - function that reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: Number of bytes read or -1 on error
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);

	r = read(info->readfd, buf, READ_BUF_SIZE);

	if (r >= 0)
		*i = r;

	return (r);
}

/**
 * _getline - function gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: Number of characters read or -1 on error/EOF
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? (free(p), -1) : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
