#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>

typedef unsigned int	t_uint;
typedef unsigned char	t_uchar;

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_read_errcode(int fd, char *buf, size_t n, int *errcode);
void	*ft_memcpy(void *dst, const void *src, size_t len);
char	*get_next_line(int fd);

#endif
