/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 13:15:41 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/22 16:50:37 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	create_obj_sphere(t_data *data, char **params)
{
	if (arr_len(params) == 4)
	{
		return (OK);
	}
	return (ERROR);
}
