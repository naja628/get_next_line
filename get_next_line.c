#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#define BUFFSIZE 10

static void ft_init_line(t_line *l)
{
	l->sz = 0;
	l->parts = NULL;
	l->tail = &l->parts; 
}

static void ft_save_line_buf(t_line *l, int *errcode)
{
	uint i;
	t_list *new_cell;

	i = l->sz % BUFFSIZE;
	if (i == 0)
		i = BUFFSIZE;
	l->buf[i] = '\0';
	new_cell = ft_lstnew(l->buf);
	if (!new_cell)
	{
		free(l->buf);
		*errcode = -1;
	}
	// ptr/precedence pbs?
	*l->tail = new_cell;
	l->tail = &new_cell->next;
}

static int ft_next_read(int fd, char *rd_buff, char **w_buff, int *errcode)
{
	int nread;

	nread = read(fd, rd_buff, BUFFSIZE);
	if (nread == -1)
	{
		*errcode = -1;
		return (-1);
	}
	*w_buff = malloc(BUFFSIZE + 1);
	if (!(*w_buff))
		*errcode = -1;
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

//TODO remove 
#include <stdio.h>

char *get_next_line(int fd)
{
	static char buff[BUFFSIZE];
	static uint ibuf = 0;
	t_line l;
	int nread;
	int errcode;

	errcode = 0;
	nread = -1;
	ft_init_line(&l);
	l.buf = ft_malloc_errcode(sizeof(char), &errcode); // see (1)
	while (errcode != -1 && buff[ibuf] != '\n' && ibuf != (uint) nread)
	{
		if (ibuf == 0)
		{
			ft_save_line_buf(&l, &errcode);
			nread = ft_next_read(fd, buff, &l.buf, &errcode);
		}
		if (errcode != -1)
			l.buf[l.sz++ % BUFFSIZE] = buff[ibuf++];
		printf("%u %c\n", l.sz, l.buf[l.sz]);
		ibuf %= BUFFSIZE;
	}
	if (ibuf != (uint) nread)
		l.buf[l.sz++ % BUFFSIZE] = buff[ibuf++];
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
	{
		printf("line %d : %s\n", i++, line);
		line = get_next_line(fd);
		//printf("line %d : %s\n", i++, line);
	}
	return (0);
}
