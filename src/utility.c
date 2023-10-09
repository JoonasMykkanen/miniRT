/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:42:27 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/09 11:39:24 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	reset_pix(t_pixel *pix)
{
	pix->closest_t = DBL_MAX;
	pix->color = 0x000000ff;
	pix->obj_type = NONE;
}

int ft_color(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	free_arr(char **arr)
{
	int	index;

	index = 0;
	while (arr[index] != NULL)
	{
		ft_free(arr[index]);
		index++;
	}
	ft_free(arr);
}

int	arr_len(char **arr)
{
	int	len;

	len = 0;
	while (arr[len] != NULL)
		len++;
	return (len);
}
