/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:31 by djames            #+#    #+#             */
/*   Updated: 2023/10/20 11:51:46 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
		if (minirt(&data) != OK)
			return (ERROR);
	}
	else
		ft_putstr_fd("Invalid number of arguments given\n", 2);
	return (OK);
}
