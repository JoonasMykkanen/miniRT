/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:29:47 by djames            #+#    #+#             */
/*   Updated: 2023/10/19 15:29:50 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_camera(t_data *data, int mode, float delta)
{
	if (mode == HORIZONTAL)
	{
		data->scene.camera.angle += delta;
		data->scene.camera.position.x = data->scene.camera.R
			* cos(data->scene.camera.angle);
		data->scene.camera.position.z = data->scene.camera.R
			* sin(data->scene.camera.angle);
	}
	else if (mode == VERTICAL)
	{
		data->scene.camera.position.y += delta;
	}
	else if (mode == DEPTH)
	{
		data->scene.camera.position.z += delta;
	}
}

void	ft_hook(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		update_camera(data, HORIZONTAL, -0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		update_camera(data, HORIZONTAL, 0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		update_camera(data, DEPTH, 0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		update_camera(data, DEPTH, -0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		update_camera(data, VERTICAL, 0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		update_camera(data, VERTICAL, -0.1f);
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
