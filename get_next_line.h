/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: najacque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:30:06 by najacque          #+#    #+#             */
/*   Updated: 2021/10/20 14:30:36 by najacque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stddef.h>

int		ft_read_errcode(int fd, char *buf, size_t n, int *errcode);
void	*ft_memcpy(void *dst, const void *src, size_t len);
char	*get_next_line(int fd);

#endif
