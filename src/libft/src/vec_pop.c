/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/07/02 10:09:32 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_pop(void *dst, t_vec *src)
{
	if (!src)
		return (-1);
	else if (!src->memory || src->len == 0)
		return (0);
	if (dst)
		ft_memcpy(dst, vec_get(src, src->len - 1), src->elem_size);
	src->len--;
	return (1);
}
