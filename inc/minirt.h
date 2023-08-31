/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/08/30 12:09:26 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include "stdbool.h"
# include "../src/libft/inc/libft.h"
# include "../src/mlx42/include/MLX42/MLX42.h"

# define HEIGHT 878
# define WIDTH 1352

# define ERROR 2
# define OK 0

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}				t_vector;

typedef struct s_color
{
	int	red;
	int	green;
	int	blue;
}				t_color;

typedef struct s_camera
{
	t_vector	position;
	t_vector	orientation;
	int			fov;
}				t_camera;

typedef struct s_ambient
{
	float		intensity;
	t_color		color;
}				t_ambient;

typedef struct s_light
{
	t_vector	position;
	float		brightness;
	t_color		color;
}				t_light;

typedef struct s_sphere
{
	t_vector	center;
	float		diameter;
	t_color		color;
}				t_sphere;

typedef struct s_plane
{
	t_vector	point;
	t_vector	normal;
	t_color		color;
}				t_plane;

typedef struct s_cylinder
{
	t_vector	center;
	t_vector	axis;
	float		diameter;
	float		height;
	t_color		color;
}				t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	bool		status_ambient;
	
	t_camera	camera;
	bool		status_camera;

	t_light		light;
	bool		status_light;

	t_sphere	spheres[10];
	int			num_spheres;

	t_plane		planes[10];
	int			num_planes;

	t_cylinder	cylinders[10];
	int			num_cylinders;
}				t_scene;

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_t		*mlx;

	t_scene		scene;
}				t_data;

double	ft_atof(char *str);
int		arr_len(char **arr);
void	free_arr(char **arr);
int		normalize_alpha(float value);
int		init(t_data *data, char *file);
int 	ft_color(int r, int g, int b, int a);

#endif // !MINIRT_H