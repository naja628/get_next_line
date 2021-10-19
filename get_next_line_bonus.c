#include <unistd.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

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

/* this function find the thread corresponding to fd
 * or creates it if it does not exist yet (modifying the lst arg)
 * it modifies *rd to be the correct rd_thread
 * it returns the adress of the list node containing rd
 * so it can be deleted if needed.
 *
 * the choice to return the list and modify rd in place and not 
 * vice versa is pretty arbitrary 
 * except for the fact that triple pointers are frightening */
static t_list	**ft_prep_rd(t_list **lst, t_rd_thread **rd, int fd, int *errc)
{
	t_list	**it;

	it = lst;
	while (*it != NULL && ((t_rd_thread *)(*it)->content)->fd != fd)
		it = &((*it)->next);
	if (*it == NULL && *errc != -1)
	{
		*rd = ft_malloc_errcode(sizeof(t_rd_thread), errc);
		(*rd)->fd = fd;
		(*rd)->i = 0;
		(*rd)->nrd = BUFFER_SIZE;
		ft_lstput_front_errcode(lst, *rd, errc);
		if (*errc != -1)
			return (lst);
		free (*rd);
	}
	if (*errc == -1)
		return (NULL);
	*rd = (*it)->content;
	return (it);
}

/* rd needs to be a pointer because penult line of prep_rd */
char	*get_next_line(int fd)
{
	static t_list	*threads = NULL;
	t_rd_thread		*rd;
	t_list			**maybe_delme;
	t_line			l;
	int				ec;

	ft_init_line(&l, &ec);
	maybe_delme = ft_prep_rd(&threads, &rd, fd, &ec);
	while (ec != -1 && !(rd->nrd != BUFFER_SIZE && rd->i == (size_t) rd->nrd))
	{
		rd->i %= BUFFER_SIZE;
		if (rd->i == 0)
			rd->nrd = ft_read_errcode(fd, rd->buf, BUFFER_SIZE, &ec);
		if (l.i >= l.sz)
			ft_dblsz_line(&l, &ec);
		if (ec != -1 && rd->nrd != 0)
			l.buf[l.i++] = (rd->buf)[rd->i++];
		if (rd->i != 0 && rd->buf[rd->i - 1] == '\n')
			break ;
	}
	if (ec == -1 || l.i == 0 || (rd->fd == 0 && rd->i == (size_t) rd->nrd))
		ft_lstrm_head(maybe_delme, free);
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
	close(fd);
	return (0);
}
#endif
#ifdef TEST1
# include <fcntl.h>
# include <stdio.h>

int main(int ac, char **av)
{
	if (ac != 2) 
		return (-1);
	char *line, *line2;
	int fd = open(av[1], O_RDONLY);
	line = get_next_line(0);
	line2 = get_next_line(fd);
	int i = 0;
	while (line && line2)
	{
		printf("kdb line %d: %s", i++, line);
		free(line);
		line = get_next_line(0);
		printf("file line %d: %s", i++, line2);
		free(line2);
		line2 = get_next_line(fd);
	}
	close (fd);
	return (0);
}
#endif
