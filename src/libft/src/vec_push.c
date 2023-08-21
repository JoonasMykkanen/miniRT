/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_push.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/06/24 14:58:35 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_push(t_vec *dst, void *src)
{
	if (!dst || !src)
		return (-1);
	else if (!dst->memory)
	{
		if (vec_new(dst, 1, dst->elem_size) < 0)
			return (-1);
	}
	if (dst->elem_size * dst->len >= dst->alloc_size)
	{
		if (vec_resize(dst, dst->len * 2) < 0)
			return (-1);
	}
	ft_memcpy(&dst->memory[dst->elem_size * dst->len], src, dst->elem_size);
	dst->len++;
	return (1);
}
