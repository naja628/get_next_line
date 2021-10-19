#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>

int		ft_read_errcode(int fd, char *buf, size_t n, int *errcode);
void	*ft_memcpy(void *dst, const void *src, size_t len);
char	*get_next_line(int fd);

#endif
