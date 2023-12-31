/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_prepend.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:10:27 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_prepend(t_vec *dst, t_vec *src)
{
	if (!dst || !src || !src->memory)
		return (-1);
	else if (!dst->memory)
	{
		if (vec_new(dst, 1, dst->elem_size) < 0)
			return (-1);
	}
	if (dst->elem_size * dst->len >= dst->alloc_size)
	{
		if (vec_resize(dst, (dst->len + src->len)) < 0)
			return (-1);
	}
	ft_memmove(
		&dst->memory[src->elem_size * src->len],
		&dst->memory[0],
		src->elem_size * src->len);
	ft_memcpy(
		&dst->memory[0],
		&src->memory[0],
		src->elem_size * src->len);
	dst->len += src->len;
	return (1);
}
