#include <unistd.h>
#include <stdlib.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif
#if BUFFER_SIZE < 1
# undef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

typedef struct s_rd_thread
{
	int		fd;
	size_t	i;
	int		nrd;
	char	buf[BUFFER_SIZE];
}	t_rd_thread;

typedef struct s_line
{
	char	*buf;
	size_t	i;
	size_t	sz;
}	t_line;

static void	ft_init_line(t_line *l, int *errcode)
{
	l->buf = malloc(sizeof(char) * BUFFER_SIZE);
	if (!l->buf)
	{
		*errcode = -1;
		return ;
	}
	*errcode = 0;
	l->i = 0;
	l->sz = BUFFER_SIZE;
}

static void	ft_dblsz_line(t_line *l, int *errcode)
{
	char	*bigger_buf;

	bigger_buf = malloc(2 * l->sz * sizeof(char));
	if (!bigger_buf)
	{
		*errcode = -1;
		return ;
	}
	ft_memcpy(bigger_buf, l->buf, l->sz);
	l->sz *= 2;
	free(l->buf);
	l->buf = bigger_buf;
}

static char	*ft_wrap_line(t_line *l, int errcode)
{
	char	*out;
	size_t	i;

	out = malloc(sizeof(char) * (l->i + 1));
	if (errcode == -1 || l->i == 0 || !out)
	{
		free(out);
		free(l->buf);
		return (NULL);
	}
	i = 0;
	while (i < l->i)
	{
		out[i] = l->buf[i];
		++i;
	}
	free(l->buf);
	out[i] = '\0';
	return (out);
}

/* it might seem odd to initialize nrd to BUFFER_SIZE
 * but this is the easiest way to make the code work
 * smoothly as this is the typical value of this field
 * during runtime (ie after every non final succesful read)
 */
static void	ft_reset_buf(t_rd_thread *rd, int fd)
{
	rd->i = 0;
	rd->fd = fd;
	rd->nrd = BUFFER_SIZE;
}

char	*get_next_line(int fd)
{
	static t_rd_thread	rd = {-1, 0, BUFFER_SIZE, {0}};
	t_line				l;
	int					ec;

	ft_init_line(&l, &ec);
	if (fd != rd.fd)
		ft_reset_buf(&rd, fd);
	while (ec != -1 && !(rd.nrd != BUFFER_SIZE && rd.i == (size_t) rd.nrd))
	{
		rd.i %= BUFFER_SIZE;
		if (rd.i == 0)
			rd.nrd = ft_read_errcode(fd, rd.buf, BUFFER_SIZE, &ec);
		if (l.i >= l.sz)
			ft_dblsz_line(&l, &ec);
		if (ec != -1 && rd.nrd != 0)
			l.buf[l.i++] = (rd.buf)[rd.i++];
		if (rd.i != 0 && rd.buf[rd.i - 1] == '\n')
			break ;
	}
	if (rd.i == (size_t) rd.nrd)
		rd.i = 0;
	return (ft_wrap_line(&l, ec));
}

#ifdef TEST0
# include <fcntl.h>
# include <stdio.h>

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
		printf("line %d: %s", i++, line);
		free(line);
		line = get_next_line(fd);
	}
	close (fd);
	return (0);
}
#endif
#ifdef TEST1
# include <fcntl.h>
# include <stdio.h>

int main()
{
	char *line;
	
	line = get_next_line(-1);
	printf("reading from -1 : %p\n", line);
	line = get_next_line(42);
	printf("reading from 42 : %p\n", line);
	line = get_next_line(0);
	int i = 0;
	while (line != NULL)
	{
		printf("line %d: %s", i++, line);
		free(line);
		line = get_next_line(0);
	}
	return (0);
}
#endif
#ifdef TEST2
# include <fcntl.h>
# include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 3)
		exit (-1);
	int fd1 = open(av[1], O_RDONLY);
	int fd2 = open(av[2], O_RDONLY);
	char *line = get_next_line(fd1);
	int i = 0;
	while (i < 3)
	{
		if (line)
			printf("line %d: %s", i++, line);
		free(line);
		line = get_next_line(fd1);
	}
	free(line);
	line = get_next_line(fd2);
	i = 0;
	while (line != NULL)
	{
		printf("line %d: %s", i++, line);
		free(line);
		line = get_next_line(fd2);
	}
	close(fd1);
	close(fd2);
	return 0;
}

#endif
