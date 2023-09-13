/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/13 16:39:14 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <math.h>
# include "stdbool.h"
# include "../src/libft/inc/libft.h"
# include "../src/mlx42/include/MLX42/MLX42.h"

# define HEIGHT 1000
# define WIDTH 1000

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
	t_vector	position; // same as lookfrom
	t_vector	orientation;
	float		fov;
	float 		htan;
	t_vector	lookfrom;
	t_vector u;
	t_vector v;
	t_vector z;
	t_vector up_left;
	t_vector help;
	t_vector help1;
	t_vector pixel;
	t_vector pixu;
	t_vector pixv; 
    t_vector lookat;//   = point3(0,0,0);   // Point camera is looking at
    t_vector   vup;//      = vec3(0,1,0);
    t_vector u1;
    t_vector v1;
    t_vector  w1;
	t_vector w;
    t_vector focal;
    double f_len;
	double viewport_height; 
	double viewport_width;
	t_vector center;
}				t_camera;

typedef struct s_r{
    t_vector orig;
    t_vector dir;
} t_ray;

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
	float		radius;
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
	t_ray		ray;

	t_cylinder	cylinders[10];
	int			num_cylinders;
}				t_scene;

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_t		*mlx;

	float		aspect_ratio;
	
	
	

	t_scene		scene;
}				t_data;

double	ft_atof(char *str);
int		arr_len(char **arr);
void	free_arr(char **arr);
int		normalize_alpha(float value);
int		init(t_data *data, char *file);
int 	ft_color(int r, int g, int b, int a);

#endif // !MINIRT_H