#include "shell.h"

/**
 * is_cmd - determine if file is executable cmd
 * @info: info struct
 * @path: path to file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat sta;

	(void)info;
	if (!path || stat(path, &sta))
		return (0);

	if (sta.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicate character
 * @pathstr: PATH string
 * @start: starting index
 * @stop: stopping index
 *
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buff[1024];
	int i = 0, k = 0;

	for (k = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buff[k++] = pathstr[i];
	buff[k] = 0;
	return (buff);
}

/**
 * find_path - find this command in PATH string
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: command to find
 *
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int n = 0, current_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[n] || pathstr[n] == ':')
		{
			path = dup_chars(pathstr, current_pos, n);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(info, path))
				return (path);
			if (!pathstr[n])
				break;
			current_pos = n;
		}
		n++;
	}
	return (NULL);
}
