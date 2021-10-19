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
	t_uint	i;
	int		nrd;
	char	buf[BUFFER_SIZE];
}	t_rd_thread;

typedef struct s_line
{
	char	*buf;
	t_uint	i;
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
	t_uint	i;

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
	while (ec != -1 && !(rd.nrd != BUFFER_SIZE && rd.i == (t_uint) rd.nrd))
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
	return (ft_wrap_line(&l, ec));
}
