/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cyl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:51:19 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/29 10:09:57 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

// Calculating light for cylinder body
double	calculate_body(t_data *data, t_vector inter, t_cylinder *cyl, int i, int idx)
{
	t_vector	vec_inter;
	t_vector	axis_point;
	double		s;
	double		d;

	vec_inter = subtract(inter, cyl->center);
	s = dot_product(vec_inter, cyl->axis) / dot_product(cyl->axis, cyl->axis);
	axis_point = vec_add(cyl->center, vec_multis(cyl->axis, s));
	data->pix[i].light_dir = subtract(data->scene[i].lights[idx].position, inter);
	data->pix[i].light_dir = normalize(data->pix[i].light_dir);
	data->pix[i].norm = subtract(inter, axis_point);
	data->pix[i].norm = normalize(data->pix[i].norm);
	d = fmax(dot_product(data->pix[i].norm, data->pix[i].light_dir), 0.0);
	return (d);
}

// Calculate ligth for cylinder caps
double	calculate_cap(t_data *data, t_vector inter, t_cylinder *cyl, int i, int idx)
{
	t_vector	opposite;
	double		d;

	opposite = cyl->axis;
	if (cyl->fcylinder == 2)
		opposite = vec_multis(cyl->axis, -1);
	data->pix[i].light_dir = subtract(data->scene[i].lights[idx].position, inter);
	data->pix[i].light_dir = vec_multis(data->pix[i].light_dir, -1);
	data->pix[i].light_dir = normalize(data->pix[i].light_dir);
	data->pix[i].norm = vec_multis(opposite, -1.0f);
	data->pix[i].norm = normalize(data->pix[i].norm);
	// d = fmax(dot_product(data->pix[i].light_dir, data->pix[i].norm), 0.0);
	d = 1;
	return (d);
}
