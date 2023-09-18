/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/18 11:42:31 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
int	minirt(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(ERROR);
	}
	mlx_loop_hook(data->mlx, render, data);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
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
		ft_putstr_fd("Error with inputfile\n", 2);
	return (OK);
}