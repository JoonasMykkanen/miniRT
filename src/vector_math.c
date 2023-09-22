/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:57:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/18 11:09:46 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double dotProduct(t_vector a, t_vector b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

double lengthSquared(t_vector v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

t_vector subtract(t_vector a, t_vector b)
{
    t_vector result;
	
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
    return result;
}

t_vector cross(t_vector forward, t_vector position) {
    t_vector result;
	
    result.x = forward.y * position.z - forward.z * position.y;
    result.y = forward.z * position.x - forward.x * position.z;
    result.z = forward.x * position.y - forward.y * position.x;
    return (result);
}

t_vector vec_multis(const t_vector v, float r) {
    t_vector result;

    result.x = v.x * r;
    result.y = v.y * r;
    result.z = v.z * r;
    return result;
}
t_vector vec_divide(const t_vector v, float r) {
    t_vector result;

    result.x = v.x / r;
    result.y = v.y / r;
    result.z = v.z / r;
    return result;
}

t_vector vec_add(const t_vector v1, const t_vector v2) {
    t_vector result;

    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;

}

double length(t_vector v) {
    return sqrt(lengthSquared(v));
}