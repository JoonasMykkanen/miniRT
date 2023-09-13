/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/13 18:38:27 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TESTING STARTS
#include <time.h>
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

t_vector subtract(t_vector a, t_vector b)
{
    t_vector result;
	
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
	
    return result;
}

double lengthSquared(t_vector v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

t_vector cross(t_vector forward, t_vector position) {
    t_vector result;
    result.x = forward.y * position.z - forward.z * position.y;
    result.y = forward.z * position.x - forward.x * position.z;
    result.z = forward.x * position.y - forward.y * position.x;
    return (result);
}

t_vector vec_multis(const t_vector v, float r) {
    t_vector result;
    result.x = v.x * r;
    result.y = v.y * r;
    result.z = v.z * r;
    return result;
}
t_vector vec_divide(const t_vector v, float r) {
    t_vector result;
    result.x = v.x / r;
    result.y = v.y / r;
    result.z = v.z / r;
    return result;
}

t_vector vec_add(const t_vector v1, const t_vector v2) {
    t_vector result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;

}

void create_sphere(t_sphere *sphe)
{
    for(int i =0; i < 3; i++)
    {
        sphe[i].center.x =  1 + 0.30 * i;
        sphe[i].center.y =  0;
        sphe[i].center.z =  -i;
        sphe[i].radius = 0.25;   
    }
}

double length(t_vector v) {
    return sqrt(lengthSquared(v));
}

t_ray ray_create(const t_vector origin, const t_vector direction) {
    t_ray r = {origin, direction};
	
    return r;
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

t_vector ray_at(const t_ray r, double t) {
	t_vector help;
	help = vec_multis(r.dir, (float)t);
    return vec_add(r.orig, help);
}

t_vector add_color(const t_vector c1, const t_vector c2) {
    return (t_vector){c1.x + c2.x, c1.y + c2.y, c1.z + c2.z};
}

int	draw_plane(t_data *data, int x, int y)
{
	t_vector ray_origin = {
		data->scene.camera.position.x,
		data->scene.camera.position.y,
		data->scene.camera.position.z
	};
	
	t_vector ray_dir = {
		((double)x / (double)WIDTH - 0.5) * data->aspect_ratio * tan(data->scene.camera.fov / 2.0),
		(0.5 - (double)y / (double)HEIGHT) * tan(data->scene.camera.fov / 2.0),
		-1
	};
	ray_dir = normalize(ray_dir);

	double numerator = dotProduct(subtract(data->scene.planes[0].point, ray_origin), data->scene.planes[0].normal);
    double denominator = dotProduct(ray_dir, data->scene.planes[0].normal);
	if(denominator == 0.0) {
        return (0x000000ff);
    }
    double t =  numerator / denominator;
	if (t > 0) {
		return (0xffffffff);		
	}
	return (0x000000ff);
}

double hit_sphere(const t_vector center, double radius, const t_ray r) {
    t_vector oc = subtract(r.orig, center);
    double a = dotProduct(r.dir, r.dir);
    double b = 2.0 * dotProduct(oc, r.dir);
    double c = dotProduct(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
	if(discriminant < 0)
		return -1;
	else
		return (-b - sqrt(discriminant) ) / (2.0 * a);
}

t_vector ray_color(const t_ray r) {
    t_vector unit_direction = normalize(r.dir);
    double a = 0.5 * (unit_direction.y + 1.0);
    t_vector white;
    t_vector blue;
    t_vector help;
    t_vector n;
    help.x =0;
    help.y =0;
    help.z =0;
    double t = hit_sphere(help, 0.5, r);
    if (t > 0) {
        n = ray_at(r, t);
        n = subtract(n, help);
        n = normalize(n);
        n.x = 0.5 * (n.x + 1);
        n.y = 0.5 * (n.y + 1);
        n.z = 0.5 * (n.z + 1);
        return n;
    }
	white.x =1;
	white.y =1;
	white.z =1;
	blue.x = 0.5;
	blue.y = 0.7;
	blue.z = 1.0;
	white =  vec_multis(white, (float)(1.0 - a));
	blue =  vec_multis(blue, (float)(a));
    return add_color(white, blue);
}

// TODO --> better names for some variables in camera
// TODO --> replace all "magic numbers" to DEFINES with names
// TODO --> check if this can be done only once or when camera is moved
void	init_camera(t_data *data)
{
	data->scene.camera.vup.x = 0;
    data->scene.camera.vup.y = 1;
    data->scene.camera.vup.z = 0;
	data->scene.camera.hvac = tan(data->scene.camera.fov / 2);
    data->scene.camera.focal = subtract(data->scene.camera.position, data->scene.camera.orientation);
    data->scene.camera.f_len = length(data->scene.camera.focal);
	data->scene.camera.viewport_height = 2.0 * data->scene.camera.hvac * data->scene.camera.f_len;
	data->scene.camera.viewport_width =data->scene.camera.viewport_height * ((double)(WIDTH)/(double)HEIGHT);
    data->scene.camera.w1 = normalize(data->scene.camera.focal);
    data->scene.camera.u1 = cross(data->scene.camera.vup,data->scene.camera.w1);
    data->scene.camera.u1 = normalize(data->scene.camera.u1);
    data->scene.camera.v1 = cross(data->scene.camera.w1, data->scene.camera.u1);
    data->scene.camera.u = vec_multis(data->scene.camera.u1, data->scene.camera.viewport_width);
    data->scene.camera.v = vec_multis(data->scene.camera.v1, -data->scene.camera.viewport_height);
	data->scene.camera.pixu =vec_divide(data->scene.camera.u, (float)WIDTH);
	data->scene.camera.pixv = vec_divide(data->scene.camera.v, (float)HEIGHT);
    data->scene.camera.help = vec_multis(data->scene.camera.w1, data->scene.camera.f_len);
    data->scene.camera.help1 = subtract(data->scene.camera.position, data->scene.camera.help);// maybe in this part we need to check
	data->scene.camera.help = vec_divide(data->scene.camera.u, 2.0);
	data->scene.camera.up_left = subtract(data->scene.camera.help1, data->scene.camera.help);
	data->scene.camera.help = (vec_divide(data->scene.camera.v, 2.0));
	data->scene.camera.up_left = subtract(data->scene.camera.up_left, data->scene.camera.help);
	data->scene.camera.help = vec_add(data->scene.camera.pixu, data->scene.camera.pixv);
	data->scene.camera.help1 = vec_multis(data->scene.camera.help, 0.5); // I need to remember what is 0.5 
	data->scene.camera.pixel = vec_add(data->scene.camera.up_left, data->scene.camera.help1);
}

void	render(void *param)
{
	// TIMING
	static int idx = 0;
	clock_t start, end;
    double cpu_time_used;
	start = clock();
	
	t_data *data = (t_data *)param;

	init_camera(data);
    
    t_vector scaled_direction;
	t_vector ray_d;
    t_vector hit_pos;
    t_vector norm;
	
	uint32_t color;

    t_sphere sphe[3];
    create_sphere(sphe);
    t_sphere aux;
    double t66 = 5000000000000.0;
    double hit;
    int a2;
	
	for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
			data->scene.camera.help = vec_multis(data->scene.camera.pixu, (float)i);
			data->scene.camera.help1 = vec_multis(data->scene.camera.pixv, (float)j);
			data->scene.camera.center = vec_add(data->scene.camera.help, data->scene.camera.help1);
			data->scene.camera.center = vec_add(data->scene.camera.center, data->scene.camera.pixel);
			ray_d = subtract(data->scene.camera.center, data->scene.camera.position);
			data->scene.ray = ray_create(data->scene.camera.position, ray_d);
			t_vector pixel_color = ray_color(data->scene.ray);
			t66 = 5000000000000.0;
			
			for (int idx = 0; idx < data->scene.num_spheres; idx++)
            {
                hit = hit_sphere(data->scene.spheres[idx].center, data->scene.spheres[idx].radius, data->scene.ray);
                if((hit < t66) && (hit > 0))
                {
                    aux = data->scene.spheres[idx];
                    t66 = hit;
                    a2 =idx;
                }
            }
			
            if (t66 != 5000000000000.0){
                scaled_direction = vec_multis(ray_d, t66);
                hit_pos = subtract(data->scene.ray.orig, sphe[a2].center);
                hit_pos = vec_add(hit_pos, scaled_direction);
                norm =normalize(hit_pos);
               
                double d =fmax((dotProduct(norm, (data->scene.light.position))), 0.00f);

				double ambientR = data->scene.ambient.color.red * data->scene.ambient.intensity;
				double ambientG = data->scene.ambient.color.green * data->scene.ambient.intensity;
				double ambientB = data->scene.ambient.color.blue * data->scene.ambient.intensity;

				ambientR *= data->scene.spheres[a2].color.red / 255.0;
				ambientG *= data->scene.spheres[a2].color.green / 255.0;
				ambientB *= data->scene.spheres[a2].color.blue / 255.0;

				double spotR = (d * data->scene.light.brightness * data->scene.light.color.red) * data->scene.spheres[a2].color.red / 255.0;
				double spotG = (d * data->scene.light.brightness * data->scene.light.color.green) *  data->scene.spheres[a2].color.green / 255.0;
				double spotB = (d * data->scene.light.brightness * data->scene.light.color.blue) * data->scene.spheres[a2].color.blue / 255.0;

				int red = (int)(ambientR + spotR);
				int green = (int)(ambientG + spotG);
				int blue = (int)(ambientB + spotB);

				if (red > 255) red = 255;
				if (green > 255) green = 255;
				if (blue > 255) blue = 255;
                
                color  = ft_color(red, green, blue, 0xff);
			} else {
				color = ft_color(
					0x00,
					0x00,
					0x00,
					0xff
				);
			}
		    mlx_put_pixel(data->img, i, j, color);
		}
	}
	
	// only to print timing in order to track performance
	idx++;
	end = clock();  // Mark the end time
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	if (idx == 10) {
    	printf("render() took %f seconds to execute \n", cpu_time_used);
		idx = 0;
	}
}

void ft_hook(void* param)
{
	t_data	*data = (t_data *)param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
        data->scene.camera.position.y -= 0.3;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		 data->scene.camera.position.y += 0.3;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		 data->scene.camera.position.x += 0.3;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		 data->scene.camera.position.x -= 0.3;
    if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		 data->scene.camera.position.z += 0.3;
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		 data->scene.camera.position.z -= 0.3;
}

int	test(t_data *data)
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
		test(&data);
	}
	else
		ft_putstr_fd("Error with inputfile\n", 2);
	return (OK);
}