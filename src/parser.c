/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:15 by djames            #+#    #+#             */
/*   Updated: 2023/10/19 15:40:39 by djames           ###   ########.fr       */
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

static int	check_line_error(char *line)
{
	int		len;

	len = ft_strlen(line);
	if (!ft_isdigit(line[len - 1]))
		return (ERROR);
	return (OK);
}

static int	parse_line(t_data *data, char *line)
{
	char	**params;

	if (check_line_error(line))
	{
		ft_free(line);
		return (ERROR);
	}
	params = ft_split(line, ' ');
	ft_free(line);
	if (!params)
		return (ERROR);
	if (choose_object(data, params) == ERROR)
		return (ERROR);
	return (OK);
}

static void	remove_trailing_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
	{
		str[len - 1] = '\0';
	}
}

int	read_input(t_data *data, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error: opening file\n", 2);
		return (ERROR);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		remove_trailing_newline(line);
		if (ft_strlen(line) == 0)
			continue ;
		if (parse_line(data, line) == ERROR)
		{
			ft_putstr_fd("Error: Invalid map\n", 2);
			return (ERROR);
		}
	}
	return (OK);
}
