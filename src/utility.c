/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:42:27 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 11:21:27 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/inc/libft.h"
#include <math.h>

int	normalize_alpha(float value)
{
	return (round(value * 255));
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
