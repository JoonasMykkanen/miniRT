/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 11:03:26 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 11:34:06 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clamp_colors(t_color *color)
{
	if (color->red < 0)
		color->red = 0;
	if (color->green < 0)
		color->green = 0;
	if (color->blue < 0)
		color->blue = 0;
	if (color->red > 255)
		color->red = 255;
	if (color->green > 255)
		color->green = 255;
	if (color->blue > 255)
		color->blue = 255;
}

void	spotlight_effect(t_light *light, t_obj *obj, t_color *c, double d)
{
	float	b;

	b = light->brightness;
	c->red = (d * b * light->color.red) * obj->color.red / 255.0;
	c->green = (d * b * light->color.green) * obj->color.green / 255.0;
	c->blue = (d * b * light->color.blue) * obj->color.blue / 255.0;
}