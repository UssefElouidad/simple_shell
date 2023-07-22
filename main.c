#include "shell.h"

/**
 * main - entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0 on success, 1 on error
 */
int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };/* Initialize info_t structure*/
	int fd = 2; /* Default file descriptor for error messages*/

	/* Inline assembly to manipulate the file descriptor*/
	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2) /* If an input file is provided as a command-line argument*/
	{
		fd = open(av[1], O_RDONLY); /* Open the file in read-only mode*/
		if (fd == -1) /* Error opening the file*/
		{
			if (errno == EACCES) /*Permission denied*/
				exit(126);
			if (errno == ENOENT) /* File not found*/
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd; /* Update the file descriptor in info_t structure*/
	}

	populate_env_list(info); /* Populate the environment list*/
	read_history(info); /* Read command history from a file*/
	hsh(info, av); /* Start the shell*/
	return (EXIT_SUCCESS);
}
