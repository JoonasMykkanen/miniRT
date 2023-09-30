/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:17:48 by jmykkane          #+#    #+#             */
/*   Updated: 2023/09/30 08:14:53 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	calculate_color(t_data *data, t_vector point, t_color color)
{
	t_vector scaled_direction;
    t_vector hit_pos;
    t_vector norm;

	// TODO --> previous line was using uninitialized direction vector
	// for some reason that made the transition with facing light and "dark side"
	// much smoother, why?
	scaled_direction = vec_multis(data->scene.ray.dir, data->pix.closest_t);
	hit_pos = subtract(data->scene.ray.orig, point);
	hit_pos = vec_add(hit_pos, scaled_direction);
	norm = normalize(hit_pos);
	double d = fmax(dotProduct(norm, data->scene.light.position), 0.0);

	double ambientR = data->scene.ambient.color.red * data->scene.ambient.intensity;
	double ambientG = data->scene.ambient.color.green * data->scene.ambient.intensity;
	double ambientB = data->scene.ambient.color.blue * data->scene.ambient.intensity;

	ambientR *= color.red / 255.0;
	ambientG *= color.green / 255.0;
	ambientB *= color.blue / 255.0;

	double spotR = (d * data->scene.light.brightness * data->scene.light.color.red) * color.red / 255.0;
	double spotG = (d * data->scene.light.brightness * data->scene.light.color.green) *  color.green / 255.0;
	double spotB = (d * data->scene.light.brightness * data->scene.light.color.blue) * color.blue / 255.0;

	color.red = (int)(ambientR + spotR);
	color.green = (int)(ambientG + spotG);
	color.blue = (int)(ambientB + spotB);

	if (color.red > 255) color.red = 255;
	if (color.green > 255) color.green = 255;
	if (color.blue > 255) color.blue = 255;
	
	return ft_color(color.red,color. green, color.blue, 0xff);
}

void draw_plane(t_data *data) 
{
	double	max = 10;
	double	min = -1 * max;
	double t;
	
	t = hit_plane(data->scene.planes[0], data->scene.ray);

	if (t > 0) {
		t_vector intersection_point = vec_add(vec_multis(data->scene.ray.dir, t), data->scene.ray.orig);
		
    	if (intersection_point.x > max || intersection_point.x < min || intersection_point.z > max || intersection_point.z < min || intersection_point.y > max || intersection_point.y < min)
			return ;
		double d = dist(data->scene.ray.orig, intersection_point);
		if (d > data->pix.closest_t && data->pix.closest_t != 10)
			return ;
		data->pix.color = calculate_color(data, data->scene.planes[0].point, data->scene.planes[0].color);
	}
}

void	draw_sphere(t_data *data)
{
	t_vector scaled_direction;	
    t_vector hit_pos;
    t_vector norm;
    t_sphere aux;
    double t66;
    double hit;
    int a2;
	
	t66 = DBL_MAX;
	for (int idx = 0; idx < data->scene.num_spheres; idx++) {
		hit = hit_sphere(data->scene.spheres[idx].center, data->scene.spheres[idx].radius, data->scene.ray);
		if((hit < t66) && (hit > 0))
		{
			aux = data->scene.spheres[idx];
			t66 = hit;
			a2 =idx;
		}
	}
	if (t66 != DBL_MAX && t66 < data->pix.closest_t) {
		data->pix.closest_t = t66;
		data->pix.color = calculate_color(data, data->scene.spheres[a2].center, data->scene.spheres[a2].color);
	} 
}

int	render_pixel(t_data *data, int x, int y)
{
	data->pix.closest_t = DBL_MAX;
	data->pix.color = 0x000000ff;
	update_ray(data, x, y);
	// shoot_ray(data);
	draw_plane(data);
	draw_sphere(data);

	return (data->pix.color);
}