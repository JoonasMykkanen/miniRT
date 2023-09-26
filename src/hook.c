/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 08:06:45 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/26 12:12:01 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	update_camera(t_data *data, int mode, float delta)
{
	if (mode == HORIZONTAL) {
		data->scene.camera.angle += delta;
		data->scene.camera.position.x = data->scene.camera.R * cos(data->scene.camera.angle);
		data->scene.camera.position.z = data->scene.camera.R * sin(data->scene.camera.angle);
	}
	else if (mode == VERTICAL) {
		data->scene.camera.position.y += delta;
	}
	else if (mode == DEPTH) {
		data->scene.camera.position.z += delta;
	}
}

void	ft_hook(void *param)
{
	t_data	*data = (t_data *)param;
	
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
	static int render_frame = 0;
	clock_t start, end;
    double cpu_time_used;
	start = clock();

	t_data	*data = (t_data *)param;
	
	init_camera(data);
	for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
			mlx_put_pixel(data->img, x, y, render_pixel(data, x, y));
		}
	}
	
	render_frame++;
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	if (render_frame == 20) {
    	printf("render() took %f seconds to execute\n", cpu_time_used);
		render_frame = 0;
	}
}
