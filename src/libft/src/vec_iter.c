/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_iter.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 16:04:53 by jmykkane          #+#    #+#             */
/*   Updated: 2022/10/26 16:04:54 by jmykkane         ###   ########.fr       */
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
