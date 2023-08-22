/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/22 12:39:14 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../src/libft/inc/libft.h"
# include "../src/mlx42/include/MLX42/MLX42.h"
# include <math.h>

# define WIDTH 1024
# define HEIGHT 1024

# define ERROR 2
# define OK 0

typedef struct s_ambient_light
{
	float	ratio;
	int		color[3];
}			t_ambient_light;

typedef struct s_camera
{
	float	fov;
	float	view_point[3];
	float	orientation[3];
}			t_camera;

typedef struct s_light
{
	int		color[3];
	float	brightness;
	float	position[3];
}			t_light;

typedef struct s_sphere
{
	float	diameter;
	int		color[3];
	float	center[3];
}			t_sphere;

typedef struct s_plane
{
	float	point[3];
	int		color[3];
	float	normal[3];
}			t_plane;

typedef struct s_cylinder
{
	float	height;
	float	axis[3];
	int		color[3];
	float	diameter;
	float	center[3];
}			t_cylinder;

typedef struct s_data
{
	mlx_image_t	*image;
	mlx_t		*mlx;
}				t_data;

#endif // !MINIRT_H