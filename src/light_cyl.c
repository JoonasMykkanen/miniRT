/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cyl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:51:19 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/25 06:40:43 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Calculating light for cylinder body
double	calculate_body(t_data *data, t_vector inter, t_cylinder *cyl)
{
	t_vector	vec_inter;
	t_vector	axis_point;
	double		s;
	double		d;

	vec_inter = subtract(inter, cyl->center);
	s = dot_product(vec_inter, cyl->axis) / dot_product(cyl->axis, cyl->axis);
	axis_point = vec_add(cyl->center, vec_multis(cyl->axis, s));
	data->pix.light_dir = subtract(data->scene.light.position, inter);
	data->pix.light_dir = normalize(data->pix.light_dir);
	data->pix.norm = subtract(inter, axis_point);
	data->pix.norm = normalize(data->pix.norm);
	d = fmax(dot_product(data->pix.norm, data->pix.light_dir), 0.0);
	return (d);
}

// Calculate ligth for cylinder caps
double	calculate_cap(t_data *data, t_vector inter, t_cylinder *cyl)
{
	t_vector	opposite;
	double		d;

	opposite = cyl->axis;
	if (cyl->fcylinder == 2)
		opposite = vec_multis(cyl->axis, -1);
	data->pix.light_dir = subtract(data->scene.light.position, inter);
	data->pix.light_dir = vec_multis(data->pix.light_dir, -1);
	data->pix.light_dir = normalize(data->pix.light_dir);
	data->pix.norm = vec_multis(opposite, -1.0f);
	data->pix.norm = normalize(data->pix.norm);
	d = fmax(dot_product(data->pix.light_dir, data->pix.norm), 0.0);
	return (d);
}
