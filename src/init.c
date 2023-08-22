/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:50:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/22 12:52:33 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init(t_data *data)
{
	if (!(data->mlx = mlx_init(HEIGHT, WIDTH, "miniRT", true)))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), ERROR);
		return (ERROR);
	}
	if (!(data->image = mlx_new_image(data->mlx, HEIGHT, WIDTH)))
	{
		mlx_close_window(data->mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), ERROR);
		return (ERROR);
	}
	return (OK);	
}
