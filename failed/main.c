/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/30 14:25:55 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TESTING STARTS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

t_vector normals[] = {
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    // ... more normals
};

// t_vector reflect(t_vector lightDir, t_vector normal) {
//     double dotProduct = lightDir.x * normal.x + lightDir.y * normal.y + lightDir.z * normal.z;

//     t_vector reflection = {
//         2 * dotProduct * normal.x - lightDir.x,
//         2 * dotProduct * normal.y - lightDir.y,
//         2 * dotProduct * normal.z - lightDir.z
//     };

//     return normalize(reflection);
// }

t_vector normalize(t_vector vector) {
    double length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    t_vector normalizedVector = {
        vector.x / length,
        vector.y / length,
        vector.z / length
    };
    return normalizedVector;
}

int interpolate(int start, int end, float t) {
    return (int)(start * (1 - t) + end * t);
}

double dotProduct(t_vector a, t_vector b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int perPixel(int x, int y, int z, float r, t_data *data) {
    // int startR = 255, startG = 154, startB = 162;
    // int endR = 199, endG = 206, endB = 234;
    // // Interpolate between the start and end colors
    // int red = interpolate(startR, endR, t);
    // int green = interpolate(startG, endG, t);
    // int blue = interpolate(startB, endB, t);

	int	red;

	// TODO WHAT ARE THESE 
	t_vector	light;
	light.x = 1;
    light.y = 1;
    light.z = -1;
    light = normalize(light);
	t_vector	norm;
	t_vector	hit_pos;
	t_vector 	scaled_dir;	// ???
	double		t0; 		// ???
	
	double		des;
	double		a;
	double		b;
	double		c;
	
	// RAY ORIGIN
	t_vector	ray_o;
	// ray_o.x = data->scene.camera.position.x;  // Camera position x-coordinate
    // ray_o.y = data->scene.camera.position.y;  // Camera position y-coordinate
    // ray_o.z = data->scene.camera.position.z;  // Camera position z-coordinate
	// TODO CHANGE TO ABOVE
	ray_o.x = 0.0;
    ray_o.y = 0.0;
    ray_o.z = 5;

    // RAY DIRECTION
	float 		aspect_ratio = (float)WIDTH / (float)HEIGHT;
	t_vector	ray_d;
	// ray_d.x = (x * 2.0f / WIDTH - 1.0f) * aspect_ratio;
	// ray_d.y = y * 2.0f / HEIGHT - 1.0f;
	ray_d.x = (double)x / WIDTH;
	ray_d.y = 1 - (double)y / HEIGHT;
	ray_d.z = -1.0f; // TODO change to actual
    
	// TODO replace with actual camera coords
	t_vector camera;
	// camera.x = ray_o.x - ray_d.x;
	// camera.y = ray_o.y - ray_d.y;
	// camera.z = ray_o.z - ray_d.z;
	camera.x = 0;
	camera.y = 0;
	camera.z = -100;

	a = dotProduct(ray_d, ray_o);
	b = 2.0f * (dotProduct(ray_d, camera));
	c = dotProduct(ray_d, camera) - (r * r);
    des = (b * b) - (4.0f * (a * c));
    
    if (des >= 0.0f) {
		t0 = (-b + sqrt(des)) / (2.0f * a);
		scaled_dir.x = ray_d.x * t0;
		scaled_dir.y =ray_d.y * t0;
		scaled_dir.z = ray_d.z * t0;
		hit_pos.x = ray_o.x + scaled_dir.x;
		hit_pos.y = ray_o.y + scaled_dir.y;
		hit_pos.z = ray_o.z + scaled_dir.z;
		norm = normalize(hit_pos);

		double d =fmax((dotProduct(norm, (light))), 0.00f);

		red = (int)(0.7* (255 * d)) + (int)((0.2 * 255));// make something 0  to 1 multiple  by 2551 I added the ambient // later we consider what is the color of the  this will grow with multiple by color of our object
		if(red > 255)
			red =255;
		int color = ft_pixel(red, 0x00, 0x00, 0xFF);
		return (0xFF0000FF);
	}
	return (0x000000ff);
    // return (red << 24) | (green << 16) | (blue << 8) | 0xff;
}

void	draw_sphere(t_data *data)
{
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			mlx_put_pixel(data->img, x, y, perPixel(x, y, 1, data->scene.spheres->diameter / 2, data));
		}
	}
}

int	test(t_data *data)
{
	draw_sphere(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(ERROR);
	}

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
		ft_putstr_fd("Error, no input file\n", 2);
	return (OK);
}
