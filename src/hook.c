/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:29:47 by djames            #+#    #+#             */
/*   Updated: 2023/10/20 11:28:08 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
	{
		printf("called\n");
		mlx_delete_image(data->mlx, data->img);
		mlx_terminate(data->mlx);
		exit(0);
	}
}

void	render(void *param)
{
	t_data	*data;
	int		x;
	int		y;

	x = -1;
	y = -1;
	data = (t_data *)param;
	init_camera(data, 0, 0);
	while (++y < HEIGHT)
	{
		while (++x < WIDTH)
			mlx_put_pixel(data->img, x, y, render_pixel(data, x, y));
		x = -1;
	}
}
