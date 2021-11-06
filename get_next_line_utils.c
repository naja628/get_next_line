/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:30:12 by najacque          #+#    #+#             */
/*   Updated: 2021/10/20 14:30:33 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

typedef unsigned char	t_uchar;

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
	size_t	i;

	i = 0;
	while (i < len)
	{
		*((t_uchar *)dst + i) = *((t_uchar *)src + i);
		++i;
	}
	return (dst);
}
