/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:31 by djames            #+#    #+#             */
/*   Updated: 2023/11/03 15:13:31 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

int	check_inside_cylinder(t_data *data, int i)
{
	double		distance_squared;
	double		y_difference;
	double		half_height;
	t_vector	cam;
	int			idx;

	idx = -1;
	cam = data->scene[i].camera.position;
	while (++idx < data->scene[i].num_cylinders)
	{
		half_height = data->scene[i].cylinders[idx].height * 0.5;
		distance_squared = (cam.x - data->scene[i].cylinders[idx].center.x)
			* (cam.x - data->scene[i].cylinders[idx].center.x)
			+ (cam.z - data->scene[i].cylinders[idx].center.z)
			* (cam.z - data->scene[i].cylinders[idx].center.z);
		if (distance_squared < (data->scene[i].cylinders[idx].diameter
				* data->scene[i].cylinders[idx].diameter))
		{
			y_difference = cam.y - data->scene[i].cylinders[idx].center.y;
			if (y_difference >= -half_height && y_difference <= half_height)
				return (ERROR);
		}
	}
	return (OK);
}

int	check_inside(t_data *data, int i)
{
	t_vector	cam;
	t_vector	res;
	int			idx;
	double		d;

	idx = -1;
	cam = data->scene[i].camera.position;
	while (++idx < data->scene[i].num_spheres)
	{
		res.x = (cam.x - data->scene[i].spheres[idx].center.x)
			* (cam.x - data->scene[i].spheres[idx].center.x);
		res.y = (cam.y - data->scene[i].spheres[idx].center.y)
			* (cam.y - data->scene[i].spheres[idx].center.y);
		res.z = (cam.z - data->scene[i].spheres[idx].center.z)
			* (cam.z - data->scene[i].spheres[idx].center.z);
		d = res.x + res.y + res.z;
		if (d < (data->scene[i].spheres[idx].radius
				* data->scene[i].spheres[idx].radius))
			return (ERROR);
	}
	if (check_inside_cylinder(data, 0) != OK)
		return (ERROR);
	return (OK);
}

int	minirt(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		ft_putstr_fd("Error: MLX Image\n", 2);
		return (ERROR);
	}
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop_hook(data->mlx, render, data);
	mlx_close_hook(data->mlx, handle_exit, data);
	mlx_loop(data->mlx);
	mlx_delete_image(data->mlx, data->img);
	mlx_terminate(data->mlx);
	return (OK);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		if (init(&data, argv[1]) != OK)
			return (ERROR);
		if (validate_scene(&data) != OK)
			return (ERROR);
		if (create_jobs(&data) != OK)
			return (ERROR);
		if (wakeup_workers(&data) != OK)
			return (ERROR);
		if (minirt(&data) != OK)
			return (ERROR);
	}
	else
		ft_putstr_fd("Invalid number of arguments given\n", 2);
	return (OK);
}
