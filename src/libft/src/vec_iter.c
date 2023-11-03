/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:10:23 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_iter(t_vec *src, void (*f) (void *))
{
	size_t	idx;

	if (!src || !src->memory || !(*f))
		return (-1);
	idx = -1;
	while (++idx < src->len)
	{
		f(&src->memory[src->elem_size * idx]);
	}
	return (1);
}
