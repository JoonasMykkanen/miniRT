/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_append.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/26 16:04:54 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_append(t_vec *dst, t_vec *src)
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
	ft_memcpy(
		&dst->memory[dst->elem_size * dst->len],
		&src->memory[0],
		(src->len * src->elem_size));
	dst->len += src->len;
	return (1);
}
