/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_remove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:10:30 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_remove(t_vec *src, size_t index)
{
	if (!src || index > src->len)
		return (-1);
	if (index == src->len)
	{
		src->len--;
		return (1);
	}
	ft_memmove(
		vec_get(src, index),
		&src->memory[src->elem_size * (index + 1)],
		(src->len - index) * src->elem_size);
	src->len--;
	return (1);
}
