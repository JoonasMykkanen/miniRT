/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/06 17:50:42 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TESTING STARTS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int interpolate(int start, int end, float t) {
    return (int)(start * (1 - t) + end * t);
}

double dotProduct(t_vector a, t_vector b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_vector normalize(t_vector vector) {
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


int perPixel(int x, int y, int z, float r, t_data *data) {
    float t = (float)y / (float)HEIGHT;  // normalize y to range [0.0, 1.0]
    int startR = 255, startG = 154, startB = 162;
    int endR = 199, endG = 206, endB = 234;
    // Interpolate between the start and end colors
    int red = interpolate(startR, endR, t);
    int green = interpolate(startG, endG, t);
    int blue = interpolate(startB, endB, t);


	t_vector	scaled_direction;
	t_vector	norm;
	t_vector	light;
	light.x = data->scene.light.position.x;
    light.y = data->scene.light.position.y;
    light.z = data->scene.light.position.z;
    light = normalize(light);
	t_vector	hit_pos;
	double		t0;
	double		t1;


	float ax = data->scene.camera.position.x;  // Camera position x-coordinate
    float ay = data->scene.camera.position.y;  // Camera position y-coordinate
    float az = data->scene.camera.position.z;  // Camera position z-coordinate

	float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    float bx = (x * 2.0f / WIDTH - 1.0f) * aspect_ratio;
	float by = y * 2.0f / HEIGHT - 1.0f;
    float bz = z;
    
    // Compute A, B, and C coefficients for the quadratic equation
	// A = origin
    float a = bx * bx + by * by + bz * bz;
	// B = direction of ray
    float b = 2 * (ax * bx + ay * by + az * bz);
	// C = 
    float c = ax * ax + ay * ay + az * az - r * r;
    
    // Calculate descriminant
    float des = (b * b) - (4 * (a * c));
    
    if (des >= 0.0f) {
		int red;
		t0 = (-b + sqrt(des)) / (2.0f * a);
		t1 = (-b - sqrt(des)) / (2.0f * a);
		scaled_direction.x = bx * t0;
		scaled_direction.y = by * t0;
		scaled_direction.z = bz * t0;
		hit_pos.x = ax + scaled_direction.x;
		hit_pos.y = ay + scaled_direction.y;
		hit_pos.z = az + scaled_direction.z;
		norm = normalize(hit_pos);
		
		double d =fmax((dotProduct(norm, (light))), 0.00f);
		
		red = (int)(((data->scene.light.color.red * data->scene.light.brightness) * d)) + (int)((data->scene.ambient.intensity * data->scene.ambient.color.red)) * data->scene.spheres[0].color.red / 255;
		if(red > 255)
			red = 255;
		green = (int)(((data->scene.light.color.green * data->scene.light.brightness) * d)) + (int)((data->scene.ambient.intensity * data->scene.ambient.color.green))* data->scene.spheres[0].color.green / 255;
		if(green > 255)
			green = 255;
		blue = (int)(((data->scene.light.color.blue * data->scene.light.brightness) * d)) + (int)((data->scene.ambient.intensity * data->scene.ambient.color.blue))* data->scene.spheres[0].color.blue / 255;
		if(blue > 255)
			blue = 255;
		int color = ft_color(red, green, blue, 0xff);
		return color;
	}
    return (red << 24) | (green << 16) | (blue << 8) | 0xff;
	// return 0x000000ff;
}

void	draw_sphere(void *param)
{
	t_data *data = (t_data *)param;
	
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			mlx_put_pixel(data->img, x, y, perPixel(x, y, 1, data->scene.spheres[0].diameter / 2, data));
		}
	}
}

void ft_hook(void* param)
{
	t_data	*data = (t_data *)param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		data->scene.light.position.y += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		data->scene.light.position.y -= 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->scene.light.position.x += 1;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->scene.light.position.x -= 1;
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

	mlx_loop_hook(data->mlx, draw_sphere, data);
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