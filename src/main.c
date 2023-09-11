/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/11 13:15:59 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TESTING STARTS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int interpolate(int start, int end, float t)
{
    return (int)(start * (1 - t) + end * t);
}

double dotProduct(t_vector a, t_vector b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_vector normalize(t_vector vector)
{
    double length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    t_vector normalizedVector = {
        vector.x / length,
        vector.y / length,
        vector.z / length
    };
    return normalizedVector;
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	iterate_spheres(t_data *data, int x, int y, double *closest)
{
	for (int i = 0; i <= data->scene.num_spheres; i++) {
		t_vector	ray_origin = {
			data->scene.camera.position.x - data->scene.spheres[i].center.x,
			data->scene.camera.position.y - data->scene.spheres[i].center.y,
			data->scene.camera.position.z - data->scene.spheres[i].center.z,
		};
		t_vector ray_dir = {
			((double)x / (double)WIDTH - 0.5) * data->aspect_ratio * tan(data->scene.camera.fov / 2.0),
			(0.5 - (double)y / (double)HEIGHT) * tan(data->scene.camera.fov / 2.0),
			-1,
		};
		ray_dir = normalize(ray_dir);
		
		double	r = data->scene.spheres[i].radius;
		
		float a = dotProduct(ray_dir, ray_dir);
		float b = 2.0 * (dotProduct(ray_dir, ray_origin));
		float c = (dotProduct(ray_origin, ray_origin)) - (r * r);
		float des = (b * b) - (4 * (a * c));
		if (des >= 0.0f)
		{
			double t = (-b - sqrt(des)) / (2.0f * a);
			// if (t < *closest)
			// {
			// *closest = t;
			t_vector scaled_direction = {
				ray_dir.x * t,
				ray_dir.y * t,
				ray_dir.z * t,
			};
			t_vector hit_pos = {
				ray_origin.x + scaled_direction.x,
				ray_origin.y + scaled_direction.y,
				ray_origin.z + scaled_direction.z,
			};
			t_vector light = {
				hit_pos.x + data->scene.light.position.x,
				hit_pos.y + data->scene.light.position.y,
				hit_pos.z + data->scene.light.position.z,
			};
			t_vector norm = {
				hit_pos.x - data->scene.spheres[i].center.x,
				hit_pos.y - data->scene.spheres[i].center.y,
				hit_pos.z - data->scene.spheres[i].center.z,
			};
			norm = normalize(norm);
			light = normalize(light);

			double d =fmax((dotProduct(norm, (light))), 0.00f);

			// Ambient Contributions
			double ambientR = data->scene.ambient.color.red * data->scene.ambient.intensity;
			double ambientG = data->scene.ambient.color.green * data->scene.ambient.intensity;
			double ambientB = data->scene.ambient.color.blue * data->scene.ambient.intensity;

			// Multiply ambient light with the object color
			ambientR *= data->scene.spheres[i].color.red / 255.0;
			ambientG *= data->scene.spheres[i].color.green / 255.0;
			ambientB *= data->scene.spheres[i].color.blue / 255.0;

			// Spot Light Contributions
			double spotR = (d * data->scene.light.brightness * data->scene.light.color.red) * data->scene.spheres[i].color.red / 255.0;
			double spotG = (d * data->scene.light.brightness * data->scene.light.color.green) *  data->scene.spheres[i].color.green / 255.0;
			double spotB = (d * data->scene.light.brightness * data->scene.light.color.blue) * data->scene.spheres[i].color.blue / 255.0;

			// Add both contributions
			int red = (int)(ambientR + spotR);
			int green = (int)(ambientG + spotG);
			int blue = (int)(ambientB + spotB);

			// Ensure values don't exceed 255
			if (red > 255) red = 255;
			if (green > 255) green = 255;
			if (blue > 255) blue = 255;
				
			int color = ft_color(red, green, blue, 0xff);
			mlx_put_pixel(data->img, x, y, color);
			// }
		}
		else
			mlx_put_pixel(data->img, x, y, 0x000000ff);
	}
}

void perPixel(int x, int y, t_data *data)
{
	double closest = MAXFLOAT;
	int color;

	
    iterate_spheres(data, x, y, &closest);

}

void	render(void *param)
{
	t_data *data = (t_data *)param;
	
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			perPixel(x, y, data);
		}
	}
}


void ft_hook(void* param) /// this move the camera now 
{
	t_data	*data = (t_data *)param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		//image->instances[0].y -= 5;
        data->scene.camera.position.y -= 0.1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		 data->scene.camera.position.y += 0.1;
        //image->instances[0].y += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		 data->scene.camera.position.x += 0.1;
        //image->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		 data->scene.camera.position.x -= 0.1;
        //image->instances[0].x += 5;
    if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		 data->scene.camera.position.z += 0.1;
        //image->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		 data->scene.camera.position.z -= 0.1;
}

int	test(t_data *data)
{
	render(data);
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
// TESTING ENDS

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc == 2)
	{
		if (init(&data, argv[1]) != OK)
			return (ERROR);
		test(&data);
	}
	else
		ft_putstr_fd("Error with inputfile\n", 2);
	return (OK);
}