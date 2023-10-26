/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_ambient_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:07 by djames            #+#    #+#             */
/*   Updated: 2023/10/26 13:11:00 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

int	create_obj_ambient(t_data *data, char **params)
{
	t_ambient	*ptr;

	ptr = &data->scene[0].ambient;
	if (arr_len(params) != 3 || data->scene[0].status_ambient != false)
		return (ERROR);
	if (check_number(params[1]) == ERROR)
		return (ERROR);
	ptr->intensity = ft_atof(params[1]);
	if (check_brightness(ptr->intensity) == ERROR)
		return (ERROR);
	if (assign_color(&ptr->color, params[2]) == ERROR)
		return (ERROR);
	data->scene[0].status_ambient = true;
	return (OK);
}
