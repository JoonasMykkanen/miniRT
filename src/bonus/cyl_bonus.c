/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cyl_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 10:58:56 by djames            #+#    #+#             */
/*   Updated: 2023/10/27 13:17:55 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"

void	init_cyl(t_cylinder *cyl, const t_ray r, t_helpc2 *point)
{
	point->normal = normalize(cyl->axis);
	cyl->center1 = (vec_multis(point->normal, -1));
	cyl->center1 = vec_multis(cyl->center1, (cyl->height / 2.0));
	cyl->center1 = vec_add(cyl->center1, cyl->center);
	if (cyl->flag == 0)
	{
		cyl->center = cyl->center1;
		cyl->flag = 1;
	}
	point->depth = hit_cylinder2(cyl, r);
	point->hit = normalize(r.dir);
	point->hit = vec_multis(point->hit, point->depth);
	point->hit = vec_add(r.orig, point->hit);
	point->hit = subtract(point->hit, cyl->center);
	point->axis_of = dot_product(point->hit, cyl->axis);
	cyl->fcylinder = 0;
	point->cap = vec_multis(point->normal, cyl->height);
	point->cap = vec_add(point->cap, cyl->center);
}

void	hit_cylinder3(t_helpc *hit, t_ray r, t_vector cyl)
{
	hit->t1 = (-hit->b - sqrt(hit->discriminant)) / (2.0 * hit->a);
	hit->sol = vec_multis(hit->v, hit->t1);
	hit->sol = vec_add((r.orig), hit->sol);
	hit->sol = subtract(hit->sol, cyl);
	hit->projection = dot_product(hit->sol, hit->h1);
}

int	ay(t_helpc2 *point, t_cylinder *cyl, t_ray r)
{
	point->au1 = hit_cap(r, point->cap, point->normal, cyl);
	if (point->au1 != 0)
	{
		if (point->au1 < point->depth || point->depth == 0)
		{
			cyl->fcylinder = 3;
			return (1);
		}
	}
	return (0);
}
