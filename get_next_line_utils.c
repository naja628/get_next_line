#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

int	ft_read_errcode(int fd, char *buf, size_t n, int *errcode)
{
	int	nread;

	nread = read(fd, buf, n);
	if (nread == -1)
		*errcode = -1;
	return (nread);
}

void	*ft_memcpy(void *dst, const void *src, size_t len)
{
	t_uint	i;

	i = 0;
	while (i < len)
	{
		*((t_uchar *)dst + i) = *((t_uchar *)src + i);
		++i;
	}
	return (dst);
}
