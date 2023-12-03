#include "shell.h"

/**
 * _myexit - exit shell
 * @info: Structure containing potential args. Used to maintain
 *          constant function prototype.
 *  Return: exit with a given exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitev;

	if (info->argv[1])  /* If there is an exit arguement */
	{
		exitev = _erratoi(info->argv[1]);
		if (exitev == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - change current directory of process
 * @info: Structure containing potential args. Used to maintain
 *          constant func prototype.
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *s, *dir, buff[1024];
	int chardir_ret;

	s = getcwd(buff, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = _getenv(info, "HOME=");
		if (!dir)
			chardir_ret = /* TODO: what should this be? */
				chdir((dir = _getenv(info, "PWD=")) ? dir : "/");
		else
			chardir_ret = chdir(dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chardir_ret = /* TODO: what should this be? */
			chdir((dir = _getenv(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chardir_ret = chdir(info->argv[1]);
	if (chardir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buff, 1024));
	}
	return (0);
}

/**
 * _myhelp - change current directory of process
 * @info: Structure containing potential args. Used to maintain
 *          constant func prototype.
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_arr;

	arg_arr = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr); /* temp att_unused workaround */
	return (0);
}
