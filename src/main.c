/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/22 12:48:10 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parse.h"

int	test(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(ERROR);
	}

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (OK);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		if (init(&data) == OK)
			test(&data);
		else
			ft_putchar_fd("Error", 2);
	}
	return (0);
}

// int	main(int argc, char** argv)
// {
// 	mlx_image_t	*image;
// 	mlx_t		*mlx;

// 	if (!(mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true)))
// 	{
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	if (!(image = mlx_new_image(mlx, 128, 128)))
// 	{
// 		mlx_close_window(mlx);
// 		puts(mlx_strerror(mlx_errno));
// 		return(EXIT_FAILURE);
// 	}
// 	
// }