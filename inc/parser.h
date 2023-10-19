/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:18:07 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/19 16:00:11 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define ORIENTATION 1
# define POSITION 0

# include "minirt.h"

// Checks to be done for each attribute category
int	check_color(int value);
int	check_size(double value);
int	check_overflow(double value);
int	check_brightness(double value);
int	check_orientation(double value);

// Main parsing functions, create different type of objects
int	read_input(t_data *data, char *file);
int	create_obj_plane(t_data *data, char **params);
int	create_obj_light(t_data *data, char **params);
int	create_obj_camera(t_data *data, char **params);
int	create_obj_sphere(t_data *data, char **params);
int	create_obj_ambient(t_data *data, char **params);
int	create_obj_cylinder(t_data *data, char **params);

// Helper functions for creating and assigning variables within objects
int	assign_color(void *target, char *str);
int	assign_vector(void *target, char *str, int mode);
int	check_number(char *str);

#endif // !PARSER_H