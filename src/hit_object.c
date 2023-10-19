/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_object.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 06:40:21 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/19 10:59:34 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	hit_sphere(const t_sphere *sp, const t_ray *r)
{
	double		discriminant;
	t_vector	oc;
	double		a;
	double		b;
	double		c;

	oc = subtract(r->orig, sp->center);
	a = dot_product(r->dir, r->dir);
	b = 2.0 * dot_product(oc, r->dir);
	c = dot_product(oc, oc) - sp->radius * sp->radius;
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (-1);
	return ((-b - sqrt(discriminant)) / (2.0 * a));
}

double	hit_plane(const t_plane *plane, const t_ray *ray)
{
	double	denominator;
	double	numerator;
	double	hit;

	numerator = dot_product(plane->point, plane->normal)
		- dot_product(ray->orig, plane->normal);
	denominator = dot_product(ray->dir, plane->normal);
	if (denominator == 0.0)
		return (-1);
	hit = numerator / denominator;
	return (hit);
}

double	hit_cap(t_ray r, t_vector position, t_vector normal, t_cylinder *cyl)
{
	float		depth;
	t_plane		cup;
	double		aux;
	t_vector	dir;
	t_ray		ray;

	dir = normalize(r.dir);
	ray.dir = r.dir;
	ray.orig = r.orig;
	cup.normal = normal;
	cup.point = position;
	depth = hit_plane(&cup, &ray);
	if (depth < 0)
		return (0);
	dir = vec_multis(ray.dir, depth);
	dir = vec_add(r.orig, dir);
	aux = length(subtract(dir, position));
	if (aux > cyl->diameter)
		return (0);
	cyl->fcylinder = 1;
	return (depth);
}

double	hit_cylinder2(t_cylinder *cyl, t_ray r)
{
	t_helpc	hit;

	hit.h = normalize(cyl->axis);
	hit.h = vec_multis(hit.h, cyl->height);
	hit.h = vec_add(hit.h, cyl->center);
	hit.h = subtract(hit.h, cyl->center);
	hit.l = length(hit.h);
	hit.h1 = vec_divide(hit.h, hit.l);
	hit.w = subtract((r.orig), cyl->center);
	hit.v = normalize(r.dir);
	hit.a = dot_product(hit.v, hit.v) - (dot_product(hit.v, hit.h1)
			* dot_product(hit.v, hit.h1));
	hit.b = 2.0 * ((dot_product(hit.v, hit.w)) - ((dot_product(hit.v, hit.h1))
				* (dot_product(hit.w, hit.h1))));
	hit.c = dot_product(hit.w, hit.w) - (dot_product(hit.w, hit.h1)
			* dot_product(hit.w, hit.h1)) - cyl->diameter * cyl->diameter;
	hit.discriminant = hit.b * hit.b - 4 * hit.a * hit.c;
	if (hit.discriminant > 0)
	{
		hit_cylinder3(&hit, r, cyl->center);
		if (hit.projection >= 0 && hit.projection <= sqrt(hit.h.x * hit.h.x
				+ hit.h.y * hit.h.y + hit.h.z * hit.h.z) && hit.t1 >= 0)
			return (hit.t1);
	}
	return (0.0);
}

double	hit_cylinder(t_cylinder *cyl, const t_ray r, t_data *data)
{
	t_helpc2	point;

	init_cyl(cyl, r, data, &point);
	if (point.axis_of > cyl->height)
	{
		point.au1 = hit_cap(r, point.cap, point.normal, cyl);
		if (point.au1 != 0)
		{
			if (point.au1 < point.depth || point.depth == 0)
				return (point.au1);
		}
	}
	if (point.axis_of < 0.0)
	{
		point.normal = vec_multis(point.normal, -1);
		point.au = hit_cap(r, cyl->center, point.normal, cyl);
		if (point.au != 0)
		{
			if (point.au < point.depth || point.depth == 0)
				return (point.au);
		}
	}
	cyl->fcylinder = 0;
	return (point.depth);
}
