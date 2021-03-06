#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H
# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int		ft_read_errcode(int fd, char *buf, size_t n, int *errcode);
void	ft_lstrm_head(t_list **lst, void (*del)(void *));
void	ft_lstput_front_errcode(t_list **lst, void *content, int *errcode);
void	*ft_memcpy(void *dst, const void *src, size_t len);
void	*ft_malloc_errcode(size_t n, int *errcode);
char	*get_next_line(int fd);

#endif
