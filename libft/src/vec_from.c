/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_from.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/06/24 14:58:21 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_from(t_vec *dst, void *src, size_t len, size_t elem_size)
{
	if (!dst | !src)
		return (-1);
	if (vec_new(dst, len, elem_size) == 1)
		ft_memcpy(dst->memory, src, dst->alloc_size);
	else
		return (-1);
	return (1);
}
