#include "shell.h"

/**
 * get_history_file - get history file
 * @info: parameter struct
 *
 * Return: allocated string containg the history file
 */

char *get_history_file(info_t *info)
{
	char *buf, *direc;

	direc = _getenv(info, "HOME=");
	if (!direc)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, direc);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - create file, or append to existing file
 * @info: the parameter struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *filename1 = get_history_file(info);
	list_t *node1 = NULL;

	if (!filename1)
		return (-1);

	fd = open(filename1, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename1);
	if (fd == -1)
		return (-1);
	for (node1 = info->history; node1; node1 = node1->next)
	{
		_putsfd(node1->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - read history from file
 * @info: the parameter struct
 *
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int i, last = 0, linecount1 = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			build_history_list(info, buf + last, linecount1++);
			last = i + 1;
		}
	if (last != i)
		build_history_list(info, buf + last, linecount1++);
	free(buf);
	info->histcount = linecount1;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - add entry to history linked list
 * @info: Structure containing potential args. Used to maintain
 * @buf: buff
 * @linecount: history linecount, histcount
 *
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node1 = NULL;

	if (info->history)
		node1 = info->history;
	add_node_end(&node1, buf, linecount);

	if (!info->history)
		info->history = node1;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Structure containing potential arguments. Used to maintain
 *
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node1 = info->history;
	int n = 0;

	while (node1)
	{
		node1->num = n++;
		node1 = node1->next;
	}
	return (info->histcount = n);
}
