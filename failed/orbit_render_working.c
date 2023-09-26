/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   orbit_render_working.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/26 12:11:28 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include <stdio.h>
#include <stdlib.h>

int ***orbit;

static void	pre_render(t_data *data)
{
	// Crunch down numbers lol :D
	printf("Starting to render\n");
	init_camera(data);
	orbit = malloc(600 * sizeof(int **));
    if (!orbit) {
        perror("Failed to allocate memory for orbit");
        exit(1);
    }

    for (int i = 0; i < 600; i++) {
        orbit[i] = malloc(1300 * sizeof(int *));
        if (!orbit[i]) {
            perror("Failed to allocate memory for orbit[i]");
            exit(1);
        }
        for (int j = 0; j < 1300; j++) {
            orbit[i][j] = malloc(800 * sizeof(int));
            if (!orbit[i][j]) {
                perror("Failed to allocate memory for orbit[i][j]");
                exit(1);
            }
        }
    }
	for (int index = 0; index < 600; index++) {
		int proportion = (index * 50) / 600;
		printf("\r[");
		for (int j = 0; j < proportion; j++) { printf("#"); }
		for (int j = proportion; j < 50; j++) { printf("-"); }
		printf("] %d/%d", proportion * 2, 100);
    	fflush(stdout);


		update_camera(data, HORIZONTAL, 0.01f);
		for (int j = 0; j < HEIGHT; ++j) {
			for (int i = 0; i < WIDTH; ++i) {
				double		closest_t;
				int			color;
	
				closest_t = 10;
				color = 0x000000ff;
				update_ray(data, i, j, &data->scene.ray.dir);
				draw_sphere(data, &closest_t, &color);
				draw_plane(data, &closest_t, &color);
				orbit[index][i][j] = color;
			}
		}
	}
}

static void	draw_from_render(void *param)
{
	t_data *data = (t_data *)param;
	static int	idx = 0;

	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			mlx_put_pixel(data->img, x, y, orbit[idx][x][y]);
		}
	}
	if (++idx >= 600)
		idx = 0;
}

int	minirt(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(ERROR);
	}

	pre_render(data);

	mlx_loop_hook(data->mlx, draw_from_render, data);
	// mlx_loop_hook(data->mlx, ft_hook, data);
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