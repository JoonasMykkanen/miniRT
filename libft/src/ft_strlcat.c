/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 11:26:34 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/27 11:26:35 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	find_start(size_t *start, size_t *len, size_t *dstsize, char *dst)
{
	while (dst[*start] != '\0' && *dstsize > 0)
	{
		*start += 1;
		*len += 1;
		*dstsize -= 1;
	}
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	original_dst_size;
	size_t	start;
	size_t	src_index;
	size_t	len;
	size_t	src_len;

	len = 0;
	start = 0;
	src_index = 0;
	src_len = ft_strlen(src);
	if (dst == NULL && dstsize == 0)
		return (src_len + len);
	original_dst_size = ft_strlen(dst);
	find_start(&start, &len, &dstsize, dst);
	while (src[src_index] != '\0' && dstsize > 1)
	{
		dst[start] = src[src_index];
		start++;
		src_index++;
		dstsize--;
	}
	if (dstsize != 0 && original_dst_size >= len)
		dst[start] = '\0';
	return (src_len + len);
}
