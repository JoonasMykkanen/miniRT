/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:32:15 by djames            #+#    #+#             */
/*   Updated: 2023/10/25 15:01:24 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

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
	free_arr(params);
	return (status);
}

static int	check_line_error(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (!ft_isdigit(str[len - 1]) && str[len - 1] != ' ')
		return (ERROR);
	if (check_line_chars(str, len) == ERROR)
		return (ERROR);
	return (OK);
}

static int	parse_line(t_data *data, char *line)
{
	char	**params;

	if (check_line_error(line))
	{
		ft_free(line);
		ft_putstr_fd("Error: Map error\n", 2);
		return (ERROR);
	}
	params = ft_split(line, ' ');
	ft_free(line);
	if (!params)
	{
		ft_putstr_fd("Error: Malloc\n", 2);
		return (ERROR);
	}
	if (choose_object(data, params) == ERROR)
	{
		ft_putstr_fd("Error: Map error\n", 2);
		return (ERROR);
	}
	return (OK);
}

static int	remove_trailing_newline(char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (str[0] == '\n')
		return (ERROR);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (OK);
}

int	read_input(t_data *data, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: opening file\n", 2);
		return (ERROR);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		if (remove_trailing_newline(line) == ERROR)
		{
			ft_free(line);
			continue ;
		}
		if (parse_line(data, line) == ERROR)
			return (ERROR);
	}
	return (OK);
}
