/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_light_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:31:55 by djames            #+#    #+#             */
/*   Updated: 2023/10/27 18:24:22 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

int	create_obj_light(t_data *data, char **params)
{
	t_light	*ptr;
	int		*idx;

	idx = &data->scene[0].num_lights;
	ptr = &data->scene[0].lights[*idx];
	if (arr_len(params) != 4)
		return (ERROR);
	if (assign_vector(&ptr->position, params[1], POSITION) == ERROR)
		return (ERROR);
	ptr->brightness = ft_atof(params[2]);
	if (check_brightness(ptr->brightness) == ERROR)
		return (ERROR);
	if (assign_color(&ptr->color, params[3]) == ERROR)
		return (ERROR);
	*idx += 1;
	return (OK);
}
