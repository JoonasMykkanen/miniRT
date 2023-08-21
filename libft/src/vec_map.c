/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/26 16:04:54 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_map(t_vec *dst, t_vec *src, void (*f) (void *))
{
	if (!dst || !src || !src->memory)
		return (-1);
	else if (!dst->memory)
	{
		if (vec_new(dst, src->len, src->elem_size) < 0)
			return (-1);
	}
	if (vec_copy(dst, src) < 0)
		return (-1);
	if (vec_iter(dst, f) < 0)
		return (-1);
	return (1);
}
