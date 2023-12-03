#include "shell.h"

/**
 * input_buf - buffs chained cmds
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len variable
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t r1 = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r1 = getline(buf, &len_p, stdin);
#else
		r1 = _getline(info, buf, &len_p);
#endif
		if (r1 > 0)
		{
			if ((*buf)[r1 - 1] == '\n')
			{
				(*buf)[r1 - 1] = '\0'; /* remove trailing newline */
				r1--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r1;
				info->cmd_buf = buf;
			}
		}
	}
	return (r1);
}

/**
 * get_input - get line minus newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t i, j, len;
	ssize_t r1 = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r1 = input_buf(info, &buff, &len);
	if (r1 == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buff + i; /* get pointer for return */

		check_chain(info, buff, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1; 
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; 
		return (_strlen(p));
	}

	*buf_p = buff; 
	return (r1);
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r1
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t r1 = 0;

	if (*i)
		return (0);
	r1 = read(info->readfd, buf, READ_BUF_SIZE);
	if (r1 >= 0)
		*i = r1;
	return (r1);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r1 = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r1 = read_buf(info, buf, &len);
	if (r1 == -1 || (r1 == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

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
