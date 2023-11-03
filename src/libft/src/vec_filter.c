/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_filter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2023/11/03 12:10:15 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

int	vec_filter(t_vec *dst, t_vec *src, bool (*f) (void *))
{
	void	*res;
	size_t	idx;

	if (!dst || !src || !src->memory)
		return (-1);
	else if (!dst->memory)
	{
		if (vec_new(dst, 1, src->elem_size) < 0)
			return (-1);
	}
	res = malloc(src->elem_size);
	if (!res)
		return (-1);
	idx = -1;
	while (++idx < src->len)
	{
		ft_memcpy(res, &src->memory[src->elem_size * idx], src->elem_size);
		if (f(res) == true)
		{
			if (vec_push(dst, res) < 0)
				return (-1);
		}
	}
	free(res);
	return (1);
}
