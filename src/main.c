/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:31 by djames            #+#    #+#             */
/*   Updated: 2023/11/03 15:07:51 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_inside_cylinder(t_data *data)
{
	double		distance_squared;
	double		y_difference;
	double		half_height;
	t_vector	cam;
	int			idx;

	idx = -1;
	cam = data->scene.camera.position;
	while (++idx < data->scene.num_cylinders)
	{
		half_height = data->scene.cylinders[idx].height * 0.5;
		distance_squared = (cam.x - data->scene.cylinders[idx].center.x)
			* (cam.x - data->scene.cylinders[idx].center.x)
			+ (cam.z - data->scene.cylinders[idx].center.z)
			* (cam.z - data->scene.cylinders[idx].center.z);
		if (distance_squared < (data->scene.cylinders[idx].diameter
				* data->scene.cylinders[idx].diameter))
		{
			y_difference = cam.y - data->scene.cylinders[idx].center.y;
			if (y_difference >= -half_height && y_difference <= half_height)
				return (ERROR);
		}
	}
	return (OK);
}

static int	check_inside(t_data *data)
{
	t_vector	cam;
	t_vector	res;
	int			idx;
	double		d;

	idx = -1;
	cam = data->scene.camera.position;
	while (++idx < data->scene.num_spheres)
	{
		res.x = (cam.x - data->scene.spheres[idx].center.x)
			* (cam.x - data->scene.spheres[idx].center.x);
		res.y = (cam.y - data->scene.spheres[idx].center.y)
			* (cam.y - data->scene.spheres[idx].center.y);
		res.z = (cam.z - data->scene.spheres[idx].center.z)
			* (cam.z - data->scene.spheres[idx].center.z);
		d = res.x + res.y + res.z;
		if (d < (data->scene.spheres[idx].radius
				* data->scene.spheres[idx].radius))
			return (ERROR);
	}
	if (check_inside_cylinder(data) != OK)
		return (ERROR);
	return (OK);
}

static int	validate_scene(t_data *data)
{
	t_scene	*s;
	int		status;

	status = OK;
	s = &data->scene;
	if (!data->scene.status_ambient)
		status = ERROR;
	if (!data->scene.status_camera)
		status = ERROR;
	if (!data->scene.status_light)
		status = ERROR;
	if (status == ERROR)
		ft_putstr_fd("Error: Map error\n", 2);
	if (s->ambient.intensity == 0 && status != ERROR)
	{
		status = ERROR;
		ft_putstr_fd("Error: No ambient light found in scene\n", 2);
	}
	if (check_inside(data) != OK)
	{
		status = ERROR;
		ft_putstr_fd("Error: Camera inside object\n", 2);
	}
	return (status);
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
	render(data);
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
		if (minirt(&data) != OK)
			return (ERROR);
	}
	else
		ft_putstr_fd("Invalid number of arguments given\n", 2);
	return (OK);
}
