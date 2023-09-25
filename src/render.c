/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 11:17:48 by jmykkane          #+#    #+#             */
/*   Updated: 2023/09/25 12:11:20 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void draw_plane(t_data *data, double *closest_t, int *color)
{
	double 	numerator = dotProduct(data->scene.planes[0].point, data->scene.planes[0].normal) - dotProduct(data->scene.ray.orig, data->scene.planes[0].normal);
	double 	denominator = dotProduct(data->scene.ray.dir, data->scene.planes[0].normal);
	
	double	max = 10;
	double	min = -1 * max;

	if (denominator == 0.0) {
		*color =  0x000000ff;
		return ;
	}

	double t = numerator / denominator;

	if (t > 0 && t < *closest_t) {
		t_vector intersection_point = vec_add(vec_multis(data->scene.ray.dir, t), data->scene.ray.orig);
		
    	if (intersection_point.x > max || intersection_point.x < min || intersection_point.z > max || intersection_point.z < min || intersection_point.y > max || intersection_point.y < min)
			return ;
		*color = ft_color(100, 100, 100, 0xff);
	}
}

void	draw_sphere(t_data *data, double *closest_t, int *color)
{
	t_vector scaled_direction;
	t_vector ray_d;
    t_vector hit_pos;
    t_vector norm;
    t_sphere aux;
    double t66 = 5000000000000.0;
    double hit;
    int a2;
	
	
	t66 = 5000000000000.0;
	for (int idx = 0; idx < data->scene.num_spheres; idx++) {
		hit = hit_sphere(data->scene.spheres[idx].center, data->scene.spheres[idx].radius, data->scene.ray);
		if((hit < t66) && (hit > 0))
		{
			aux = data->scene.spheres[idx];
			t66 = hit;
			a2 =idx;
		}
	}
	if (t66 != 5000000000000.0) {
		scaled_direction = vec_multis(ray_d, t66);
		hit_pos = subtract(data->scene.ray.orig, data->scene.spheres[a2].center);
		hit_pos = vec_add(hit_pos, scaled_direction);
		norm = normalize(hit_pos);
		
		double d =fmax(dotProduct(norm, data->scene.light.position), 0.00f);

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
		
		*color = ft_color(red, green, blue, 0xff);
	} 
}

int	render_pixel(t_data *data, int x, int y)
{
	double		closest_t;
	int			color;
	
	color = 0x000000ff;
	update_ray(data, x, y, &data->scene.ray.dir);
	draw_sphere(data, &closest_t, &color);
	draw_plane(data, &closest_t, &color);

	return color;
}