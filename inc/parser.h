/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:18:07 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 11:23:41 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minirt.h"

int	assign_color(void *target, float alpha, char *str);

int	check_color(int	value);
int	check_size(float value);
int	check_value(float value);
int	check_overflow(double value);
int	check_brightness(float value);

int	read_input(t_data *data, char *file);
int	create_obj_plane(t_data *data, char **params);
int	create_obj_light(t_data *data, char **params);
int	create_obj_camera(t_data *data, char **params);
int	create_obj_sphere(t_data *data, char **params);
int	create_obj_ambient(t_data *data, char **params);
int	create_obj_cylinder(t_data *data, char **params);


#endif // !PARSER_H