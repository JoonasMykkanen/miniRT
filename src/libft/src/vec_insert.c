/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/26 16:04:54 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_insert(t_vec *dst, void *src, size_t index)
{
	if (!dst || !src || index > dst->len)
		return (-1);
	else if (index == dst->len)
		return (vec_push(dst, src));
	if (dst->elem_size * dst->len >= dst->alloc_size)
	{
		if (vec_resize(dst, (dst->alloc_size * 2) / dst->elem_size) < 0)
			return (-1);
	}
	ft_memmove(
		vec_get(dst, index + 1),
		vec_get(dst, index),
		(dst->len - index) * dst->elem_size);
	ft_memcpy(
		vec_get(dst, index),
		src, dst->elem_size);
	dst->len++;
	return (1);
}
