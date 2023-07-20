#include "shell.h"
/**
 * _myexit - exits the shell
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = _erratoi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			fprintf(stderr, "Illegal number: %s\n", info->argv[1]);
			return (1);
		}
		info->err_num = exitcheck;
		return (-2);
	}

	info->err_num = -1;

	return (-2);
}

/**
 * _myhelp - function that changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array);
	return (0);
}
/**
 * _mycd - function that changes the current directory of the process
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */

int _mycd(info_t *info)
{
	char *dir, buffer[1024],
	char *oldpwd = getenv("OLDPWD"), *s = getcwd(buffer, 1024);
	int chdir_ret;

	if (!s)
		return (_puts("TODO: >>getcwd failure emsg here<<\n"), 1);

	if (!info->argv[1])
	{
		dir = getenv("HOME");
		if (!dir)
			chdir_ret = chdir((dir = getenv("PWD")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!oldpwd)
			return (_puts(s), _putchar('\n'), 1);
		chdir_ret = chdir(oldpwd ? oldpwd : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
		fprintf(stderr, "can't cd to %s\n", info->argv[1]);
	else
		setenv("OLDPWD", s, 1), setenv("PWD", getcwd(buffer, 1024), 1);

	return (0);
}

