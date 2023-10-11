/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 07:05:17 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/11 17:20:59 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double calculat_l(t_data *data, t_vector surface, t_vector point, t_vector center, double r)
{
	t_vector l;
	t_vector s;
	double t;
	double t1;
	double dot_product;
	t_vector radial;
	

	l = subtract(surface, center);
	t = length(l);
	t = (t * t) - (r * r);
	t = sqrt(t);
	radial = vec_multis(point, t);
	radial = vec_add(radial, center);
	s = subtract(surface, radial);
	//s = vec_add(s, surface);
	s = normalize(s);
	//s = vec_add(s, surface);
	radial = subtract(data->scene.light.position, surface);// add thi
	//radial = vec_multis(radial, -1); // we check this later on
	radial = normalize(radial);
	data->pix.light_dir = normalize(subtract(surface, s));// change this data->scene.light.position
	t1 = fmax(dotProduct(s, radial), 0.0);//data->pix.light_dir
	return t1;
}
double calculat_d(t_data *data, t_vector surface, t_vector point, t_vector center, double r)
{
	double	d;
	t_vector l;
	t_vector s;

	l = subtract(data->scene.light.position, surface);
	l = vec_multis(l, -1.0);
	l = normalize(l);
	//if()// do this 
	s = vec_multis(point, -1.0);
	s = normalize(s);
	d = fmax(dotProduct(l, s), 0.0);
	return d;	
}

int	calculate_color(t_data *data, t_vector point, t_color color, t_vector inter, t_vector center, double r)
{
	double 	d;
	double	s;
	t_color	ambient;
	t_color	spot;
	
	if(data->pix.obj_type != CYLINDER)
	{
		d = calculate_spot_light(data, point);
	}
	else
	{
		if (data->pix.is_cap == 0)
		{	
			d =calculat_l(data, inter, point, center, r);
			//d = fmax(d, 0.0);
			//d = fabs(d);
		//printf("%f\n", d);
		}
		else 
			d = calculat_d(data, inter, point, center, r);
	}
	ambient.red = data->scene.ambient.color.red * data->scene.ambient.intensity;
	ambient.green = data->scene.ambient.color.green * data->scene.ambient.intensity;
	ambient.blue = data->scene.ambient.color.blue * data->scene.ambient.intensity;
	ambient.red *= color.red / 255.0;
	ambient.green *= color.green / 255.0;
	ambient.blue *= color.blue / 255.0;
	spot.red = (d * data->scene.light.brightness * data->scene.light.color.red) * color.red / 255.0;
	spot.green = (d * data->scene.light.brightness * data->scene.light.color.green) *  color.green / 255.0;
	spot.blue = (d * data->scene.light.brightness * data->scene.light.color.blue) * color.blue / 255.0;
	color.red = (int)(ambient.red + spot.red);
	color.green = (int)(ambient.green + spot.green);
	color.blue = (int)(ambient.blue + spot.blue);
	check_rgb_values(&color);
	return ft_color(color.red,color. green, color.blue, 0xff);
}

double	calculate_spot_light(t_data *data, t_vector point)
{
	double	d;

	data->pix.scaled_dir = vec_multis(data->scene.ray.dir, data->pix.closest_t);
	data->pix.hit_pos = subtract(data->scene.ray.orig, point);//data->scene.//point);// aqui
	data->pix.hit_pos = vec_add(data->pix.hit_pos, data->pix.scaled_dir);
	data->pix.norm = normalize(data->pix.hit_pos);
	data->pix.light_dir = normalize(subtract(data->scene.light.position, data->pix.hit_pos));
	if (data->pix.obj_type == PLANE)
		d = fmax(dotProduct(data->scene.planes[data->pix.obj_idx].normal, data->pix.light_dir), 0.0);
	else if (data->pix.obj_type == CYLINDER)
		d = fmax(dotProduct(data->scene.cylinders[data->pix.obj_idx].axis, data->pix.light_dir), 0.0);
	else
		d = fmax(dotProduct(data->pix.norm, data->pix.light_dir), 0.0);	
	return (d);
}

void	check_rgb_values(t_color *color)
{
	if (color->red > 255)
		color->red = 255;
	if (color->green > 255)
		color->green = 255;
	if (color->blue > 255)
		color->blue = 255;
	if (color->red < 0)
		color->red = 0;
	if (color->green < 0)
		color->green = 0;
	if (color->blue < 0)
		color->blue = 0;
}
