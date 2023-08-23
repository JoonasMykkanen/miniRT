/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:50:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/22 21:58:18 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

static void	init_structs(t_data *data)
{
    ft_memset(&data->scene.light, 0, sizeof(data->scene.light));
    ft_memset(data->scene.planes, 0, sizeof(data->scene.planes));
    ft_memset(&data->scene.camera, 0, sizeof(data->scene.camera));
    ft_memset(data->scene.spheres, 0, sizeof(data->scene.spheres));
	ft_memset(&data->scene.ambient, 0, sizeof(data->scene.ambient));
    ft_memset(data->scene.cylinders, 0, sizeof(data->scene.cylinders));
}

int	init(t_data *data, char *file)
{
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
