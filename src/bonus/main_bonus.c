/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:31 by djames            #+#    #+#             */
/*   Updated: 2023/10/26 12:44:41 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

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
