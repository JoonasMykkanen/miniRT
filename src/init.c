/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:50:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/24 14:30:21 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	init(t_data *data, char *file)
{
	ft_memset(&data->scene, 0, sizeof(data->scene));
	if (read_input(data, file) != OK)
	{
		ft_putstr_fd("Error with input file\n", 2);
		return (ERROR);
	}
	if (!(data->mlx = mlx_init(HEIGHT, WIDTH, "miniRT", true)))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), ERROR);
		return (ERROR);
	}
	if (!(data->image = mlx_new_image(data->mlx, 120, 120)))
	{
		mlx_close_window(data->mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), ERROR);
		return (ERROR);
	}
	return (OK);	
}
