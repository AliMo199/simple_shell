#include "shell.h"

/**
 *_myexit - quits the shell
 *@data: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: quits with a given exit status
 *        (0) if data.argv[0] != "exit"
 */
int _myexit(info_t *data)
{
	int exitval;

	if (data->argv[1]) /*If there is an exit arguement */
	{
		exitval = _erratoi(data->argv[1]);
		if (exitval == -1)
		{
			data->status = 2;
			print_error(data, "Invalid number: ");
			_eputs(data->argv[1]);
			_eputchar('\n');
			return (1);
		}

		data->err_num = _erratoi(data->argv[1]);
		return (-2);
	}

	data->err_num = -1;
	return (-2);
}

/**
 *_mycd - modifies the current directory of the process
 *@data: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: Always 0
 */
int _mycd(info_t *data)
{
	char *p, *dir, buffer[1024];
	int chdir_res;

	p = getcwd(buffer, 1024);
	if (!p)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!data->argv[1])
	{
		dir = _getenv(data, "HOME=");
		if (!dir)
			chdir_res = /*TODO: what should this be? */
			chdir((dir = _getenv(data, "PWD=")) ? dir : "/");
		else
			chdir_res = chdir(dir);
	}
	else if (_strcmp(data->argv[1], "-") == 0)
	{
		if (!_getenv(data, "OLDPWD="))
		{
			_puts(p);
			_putchar('\n');
			return (1);
		}

		_puts(_getenv(data, "OLDPWD=")), _putchar('\n');
		chdir_res = /*TODO: what should this be? */
			chdir((dir = _getenv(data, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_res = chdir(data->argv[1]);
	if (chdir_res == -1)
	{
		print_error(data, "can't cd to ");
		_eputs(data->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(data, "OLDPWD", _getenv(data, "PWD="));
		_setenv(data, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 *_myhelp - displays the help information of the shell
 *@data: Structure containing potential arguments. Used to maintain
 *constant function prototype.
 *Return: Always 0
 */
int _myhelp(info_t *data)
{
	char **arg_list;

	arg_list = data->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_list); /*temp att_unused workaround */
	return (0);
}
