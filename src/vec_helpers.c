/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:57:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/07 07:34:25 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double dotProduct(t_vector a, t_vector b)
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

double lengthSquared(t_vector v)
{
    return (v.x * v.x + v.y * v.y + v.z * v.z);
}

t_vector cross(t_vector forward, t_vector position)
{
    t_vector result;
	
    result.x = forward.y * position.z - forward.z * position.y;
    result.y = forward.z * position.x - forward.x * position.z;
    result.z = forward.x * position.y - forward.y * position.x;
    return (result);
}

double length(t_vector vector)
{
    return (sqrt(lengthSquared(vector)));
}

double dist(t_vector a, t_vector b)
{
	double	cx;
	double	cy;
	double	cz;

	cx = b.x - a.x;
	cy = b.y - a.y;
	cz = b.z - a.z;
    return (sqrt(cx * cx + cy * cy + cz * cz));
}