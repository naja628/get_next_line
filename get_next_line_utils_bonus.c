#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

typedef unsigned char	t_uchar;

int	ft_read_errcode(int fd, char *buf, size_t n, int *errcode)
{
	int	nread;

	nread = read(fd, buf, n);
	if (nread == -1)
		*errcode = -1;
	return (nread);
}

void	ft_lstrm_head(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	del((*lst)->content);
	tmp = (*lst)->next;
	free (*lst);
	*lst = tmp;
}

void	ft_lstput_front_errcode(t_list **lst, void *content, int *errcode)
{
	t_list	*new_cell;

	new_cell = malloc(sizeof(t_list));
	if (!new_cell)
	{
		*errcode = -1;
		return ;
	}
	new_cell->content = content;
	new_cell->next = *lst;
	*lst = new_cell;
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((t_uchar *)dst + i) = *((t_uchar *)src + i);
		++i;
	}
	return (dst);
}

void	*ft_malloc_errcode(size_t n, int *errcode)
{
	void	*alloced;

	alloced = malloc(n);
	if (!alloced)
		*errcode = -1;
	return (alloced);
}
