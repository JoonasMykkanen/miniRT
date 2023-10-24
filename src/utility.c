/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:47 by djames            #+#    #+#             */
/*   Updated: 2023/10/24 15:57:45 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <math.h>

void	reset_pix(t_data *data)
{
	ft_memset(&data->obj, 0, sizeof(t_obj));
	data->pix.reflection_found = false;
	data->pix.closest_t = FLT_MAX;
	data->pix.color = 0x000000ff;
	data->pix.obj_type = NONE;
}

int	ft_color(int r, int g, int b, int a)
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

int	check_number(char *str)
{
	while (*str)
	{
		if (ft_isdigit(*str) != 1)
		{
			if (*str != '.' && *str != '-')
				return (ERROR);
			else if (*str == '-' && *(str + 1) == '\0')
				return (ERROR);
		}
		str++;
	}
	return (OK);
}
