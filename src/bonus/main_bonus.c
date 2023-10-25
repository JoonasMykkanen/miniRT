/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:31 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 15:01:09 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

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
	if (s->ambient.intensity == 0 && s->light.brightness == 0)
	{
		status = ERROR;
		ft_putstr_fd("Error: No light found in scene\n", 2);
	}
	return (status);
}

int	minirt(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
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
