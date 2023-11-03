/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_pop.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:10:26 by djames           ###   ########.fr       */
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
