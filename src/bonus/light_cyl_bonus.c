/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_cyl_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 16:51:19 by jmykkane          #+#    #+#             */
/*   Updated: 2023/10/31 11:52:32 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

double	calculate_body(t_data *data, t_vector inter, int i, int idx)
{
	t_vector	vec_inter;
	t_vector	axis_point;
	t_cylinder	*cyl;
	double		s;
	double		d;

	cyl = &data->scene[i].cylinders[data->obj[i].idx];
	vec_inter = subtract(inter, cyl->center);
	s = dot_product(vec_inter, cyl->axis) / dot_product(cyl->axis, cyl->axis);
	axis_point = vec_add(cyl->center, vec_multis(cyl->axis, s));
	data->pix[i].light_dir = subtract(data->scene[i].lights[idx].position,
			inter);
	data->pix[i].light_dir = normalize(data->pix[i].light_dir);
	data->pix[i].norm = subtract(inter, axis_point);
	data->pix[i].norm = normalize(data->pix[i].norm);
	d = fmax(dot_product(data->pix[i].norm, data->pix[i].light_dir), 0.0);
	return (d);
}

double	calculate_cap(t_data *data, t_vector inter, int i, int idx)
{
	t_vector	opposite;
	t_cylinder	*cyl;
	double		d;

	cyl = &data->scene[i].cylinders[data->obj[i].idx];
	opposite = cyl->axis;
	if (cyl->fcylinder == 2)
		opposite = vec_multis(cyl->axis, -1);
	data->pix[i].light_dir = subtract(data->scene[i].lights[idx].position,
			inter);
	data->pix[i].light_dir = vec_multis(data->pix[i].light_dir, -1);
	data->pix[i].light_dir = normalize(data->pix[i].light_dir);
	data->pix[i].norm = vec_multis(opposite, -1.0f);
	data->pix[i].norm = normalize(data->pix[i].norm);
	d = 1;
	return (d);
}

double	cylinder_light(t_data *data, t_vector inter, int i, int idx)
{
	double	d;

	if (data->pix[i].is_cap == 0)
		d = calculate_body(data, inter, i, idx);
	else
		d = calculate_cap(data, inter, i, idx);
	return (d);
}
