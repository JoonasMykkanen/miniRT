/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:50:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/11 16:43:03 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

int	init(t_data *data, char *file)
{
	ft_memset(&data->scene, 0, sizeof(data->scene));
	if (read_input(data, file) != OK)
	{
		ft_putstr_fd("Error with input file\n", 2);
		return (ERROR);
	}
	if (!(data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), ERROR);
		return (ERROR);
	}
	if (!(data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(data->mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), ERROR);
		return (ERROR);
	}
	data->aspect_ratio = (float)WIDTH / (float)HEIGHT;
	return (OK);	
}
