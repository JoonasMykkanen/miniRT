/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:48:30 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/23 10:49:55 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

static int	choose_object(t_data *data, char **params)
{
	int	status;
	
	status = ERROR;
	if (ft_strcmp(params[0], "A") == OK)
		status = create_obj_ambient(data, params);
	else if (ft_strcmp(params[0], "C") == OK)
		status = create_obj_camera(data, params);
	else if (ft_strcmp(params[0], "L") == OK)
		status = create_obj_light(data, params);
	else if (ft_strcmp(params[0], "sp") == OK)
		status = create_obj_sphere(data, params);
	else if (ft_strcmp(params[0], "pl") == OK)
		status = create_obj_plane(data, params);
	else if (ft_strcmp(params[0], "cy") == OK)
		status = create_obj_cylinder(data, params);
	return (status);
}

static int parse_line(t_data *data, char *line)
{
	char	**params;

	params = ft_split(line, ' ');
	ft_free(line);
	if (!params)
		return (ERROR);
	if (choose_object(data, params) == ERROR)
	{
		ft_putstr_fd("Scene error\n", 2);
		return (ERROR);
	}
	return (OK);
}

int	read_input(t_data *data, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (parse_line(data, line) == ERROR)
		{
			ft_putstr_fd("Map error\n", 2);
			return (ERROR);
		}
	}	
	return (OK);
}
