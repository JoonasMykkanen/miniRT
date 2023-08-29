/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/29 14:52:56 by joonasmykka      ###   ########.fr       */
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


int perPixel(int x, int y, int z, float r, t_data *data) {
    float t = (float)y / (float)HEIGHT;  // normalize y to range [0.0, 1.0]
    int startR = 255, startG = 154, startB = 162;
    int endR = 199, endG = 206, endB = 234;
    // Interpolate between the start and end colors
    int red = interpolate(startR, endR, t);
    int green = interpolate(startG, endG, t);
    int blue = interpolate(startB, endB, t);

	float ax = data->scene.camera.position.x;  // Camera position x-coordinate
    float ay = data->scene.camera.position.y;  // Camera position y-coordinate
    float az = data->scene.camera.position.z;  // Camera position z-coordinate

    // Assuming ray direction is (x, y, z)
	float aspect_ratio = (float)WIDTH / (float)HEIGHT;
    float bx = (x * 2.0f / WIDTH - 1.0f) * aspect_ratio;
	float by = y * 2.0f / HEIGHT - 1.0f;
    float bz = z;
    
    // Compute A, B, and C coefficients for the quadratic equation
	// A = origin
    float A = bx * bx + by * by + bz * bz;
	// B = direction of ray
    float B = 2 * (ax * bx + ay * by + az * bz);
	// C = 
    float C = ax * ax + ay * ay + az * az - r * r;
    
    // Calculate discriminant
    float discriminant = B * B - 4 * A * C;
    
    if (discriminant >= 0.0f) {
        return 0xffff00ff;  // Color when ray hits the sphere
	}
    // } else {
	// 	return (0x000000ff);
	// }

    // Otherwise, interpolate color
    return (red << 24) | (green << 16) | (blue << 8) | 0xff;
}

void	draw_sphere(t_data *data)
{
	// draw gradient
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
