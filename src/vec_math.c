/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_math.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:57:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 08:52:36 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vec_multis(const t_vector v, float r)
{
	t_vector	result;

	result.x = v.x * r;
	result.y = v.y * r;
	result.z = v.z * r;
	return (result);
}

t_vector	vec_divide(const t_vector v, float r)
{
	t_vector	result;

	result.x = v.x / r;
	result.y = v.y / r;
	result.z = v.z / r;
	return (result);
}

t_vector	vec_add(const t_vector v1, const t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	subtract(t_vector a, t_vector b)
{
	t_vector	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}
