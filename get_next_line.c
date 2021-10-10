#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#define BUFFSIZE 10

static void ft_init_gnl(t_line *l, int *errcode)
{
	l->sz = 0;
	l->parts = NULL;
	l->tail = &l->parts; 
	l->buf = ft_malloc_errcode(sizeof(char), &errcode); // see (1)
	errcode = 0;
}

//TODO remove 
#include <stdio.h>

static void ft_save_line_buf(t_line *l, int *errcode)
{
	uint i;
	t_list *new_cell;

	i = l->sz % BUFFSIZE;
	if (i == 0 && l->sz != 0)
		i = BUFFSIZE;
	(l->buf)[i] = '\0';
	printf("linebuf full: %d %s \n", i, l->buf);
	new_cell = ft_lstnew(l->buf);
	if (!new_cell)
	{
		free(l->buf);
		*errcode = -1;
	}
	// ptr/precedence pbs?
	*l->tail = new_cell;
	l->tail = &new_cell->next;
	l->buf = malloc(BUFFSIZE + 1);
}

static int ft_next_read(int fd, char *rd_buff, int *errcode)
{
	int nread;

	nread = read(fd, rd_buff, BUFFSIZE);
	if (nread == -1)
	{
		*errcode = -1;
		return (-1);
	}
	return (nread);
}

static char *ft_meld_parts(t_line *l, int errcode)
{
	char *str_line;
	char *line_pos;
	t_list *lst;

	str_line = malloc(sizeof(char) * (l->sz + 1));
	if (l->sz == 0 || errcode == 1 || !str_line)
	{
		free(str_line);
		ft_lstclear(&l->parts, free);
		return (NULL);
	}
	lst = l->parts;
	line_pos = str_line;
	while (lst)
	{
		line_pos = ft_us_streamcpy(line_pos, lst->content);
		lst = lst->next;
	}
	ft_lstclear(&l->parts, free);
	return (str_line);
}

/* there will be a problem if we change file
 * or at the end of a file read
 * TODO reinit the static vars when needed
 */
char *get_next_line(int fd)
{
	static char buff[BUFFSIZE];
	static uint ibuf = 0;
	static int nread = BUFFSIZE;
	t_line l;
	int errcode;

	ft_init_gnl(&l, &errcode);
	while (errcode != -1 && buff[ibuf] != '\n' && ibuf != (uint) nread)
	{
		if (l.sz % BUFFSIZE == 0)
			ft_save_line_buf(&l, &errcode);
		if (ibuf == 0)
			nread = ft_next_read(fd, buff, &errcode);
		if (errcode != -1)
			l.buf[l.sz++ % BUFFSIZE] = buff[ibuf++];
		ibuf %= BUFFSIZE;
	}
	if (ibuf != (uint) nread && errcode != -1)
		l.buf[l.sz++ % BUFFSIZE] = buff[ibuf++];
	ibuf %= BUFFSIZE;
   ft_save_line_buf(&l, &errcode);
	return (ft_meld_parts(&l, errcode));
}

#include <fcntl.h>
#include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 2)
		exit(-1);
	int fd = open(av[1], O_RDONLY);
	char *line;
	
	line = get_next_line(fd);
	int i = 0;
	while (line != NULL)
	//for (int i = 0; i < 5; ++i)
	{
		printf("line %d : %s\n", i++, line);
		line = get_next_line(fd);
		//printf("line %d : %s\n", i++, line);
	}
	return (0);
}
