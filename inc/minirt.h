/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/21 07:52:22 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../src/mlx42/include/MLX42/MLX42.h"
# include "../src/libft/inc/libft.h"
# include <stdbool.h>
# include <pthread.h>
# include "stdbool.h"
# include <stdlib.h>
# include <float.h>
# include <stdio.h>
# include <math.h>
#include <time.h>

# define HEIGHT 800
# define WIDTH 1300

# define ERROR 2
# define OK 0

# define MAX_OBJ 100

# define HORIZONTAL 1
# define VERTICAL 2
# define DEPTH 3

# define NONE 0
# define PLANE 1
# define SPHERE 2
# define CYLINDER 3

# define BODY 0
# define TOP 1
# define BOTTOM 2

typedef struct s_vector
{
	double		x;
	double		y;
	double		z;
}				t_vector;

typedef struct s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct s_camera
{
	float		fov;
	t_vector	center;
	t_vector	position;
	t_vector	orientation;

	double		f_len;
	double		viewport_height;
	double		viewport_width;

	t_vector	pixv;
	t_vector	pixu;
	t_vector	pixel;
	t_vector	help;
	t_vector	help1;
	t_vector	focal;

	float		hvac;
	t_vector	up_left;
	t_vector	vup;
}				t_camera;

typedef struct s_r
{
	t_vector	orig;
	t_vector	dir;
}				t_ray;

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
	int			fcylinder;
}				t_cylinder;

typedef struct s_scene
{
	t_ambient	ambient;
	bool		status_ambient;

	t_camera	camera;
	bool		status_camera;

	t_light		light;
	bool		status_light;

	t_sphere	spheres[MAX_OBJ];
	int			num_spheres;

	t_plane		planes[MAX_OBJ];
	int			num_planes;
	t_ray		ray;

	t_cylinder	cylinders[MAX_OBJ];
	int			num_cylinders;
}				t_scene;

typedef struct s_obj
{
	int			idx;
	int			type;
	double		shine;
	double		specular;
	t_vector	axis;
	t_vector	point;
	t_color		color;
	double		radius;
}				t_obj;

typedef struct s_pixel
{
	double		closest_t;
	int			obj_type;
	int			obj_idx;
	t_color		ambient;
	int			shadow;
	int			color;
	int			side;

	t_vector	scaled_dir;
	t_vector	light_dir;
	t_vector	hit_pos;
	t_vector	norm;
}				t_pixel;

typedef struct s_data
{
	mlx_image_t	*img;
	mlx_t		*mlx;

	t_obj		obj;
	t_pixel		pix;
	t_scene		scene;
}				t_data;

typedef struct s_hitc
{
	t_vector	h1;
	t_vector	h;
	t_vector	w;
	t_vector	v;
	t_vector	sol;
	double		l;
	double		a;
	double		b;
	double		c;
	double		discriminant;
	double		t1;
	double		projection;
}				t_helpc;

typedef struct s_hitc1
{
	t_vector	hit;
	t_vector	cap;
	t_vector	normal;
	double		depth;
	double		axis_of;
	double		au;
	double		au1;
}				t_helpc2;

// GENERAL
double			ft_atof(char *str);
int				arr_len(char **arr);
void			free_arr(char **arr);
int				init(t_data *data, char *file);
int				ft_color(int r, int g, int b, int a);
double			hit_cylinder2(t_cylinder *cyl, t_ray r);
int				ay(t_helpc2 *point, t_cylinder *cyl, t_ray r);
void			clamp_colors(t_color *color);
void			hit_cylinder3(t_helpc *hit, t_ray r, t_vector cyl);
void			init_cyl(t_cylinder *cyl, const t_ray r, t_helpc2 *point);
void			init_camera(t_data *data, double vp_height, double vp_width);
double			hit_cap(t_ray r, t_vector position, t_vector normal, t_cylinder *cyl);

// LIGHT
void			check_rgb_values(t_color *color);
void			calculate_ambient(t_data *data, t_color *color);
int				calculate_color(t_data *data, t_obj *obj, t_vector inter);
void			spotlight_effect(t_light *light, t_obj *obj, t_color *c, double d);
int				is_in_shadow(t_vector surface_point, t_vector light_source_position, t_data *data, int self);

// HOOK
void			render(void *param);
void			ft_hook(void *param);

// MATH
double			length(t_vector v);
double			length_squared(t_vector v);
double			dist(t_vector a, t_vector b);
double			dot_product(t_vector a, t_vector b);
t_vector		subtract(t_vector a, t_vector b);
t_vector		vec_divide(const t_vector v, float r);
t_vector		vec_multis(const t_vector v, float r);
t_vector		cross(t_vector forward, t_vector position);
t_vector		vec_add(const t_vector v1, const t_vector v2);

// RAY
void			check_spheres(t_data *data);
void			check_planes(t_data *data);
void			check_cylinders(t_data *data);
t_vector		normalize(t_vector vector);
t_vector		ray_at(const t_ray r, double t);
double			hit_plane(const t_plane *plane, const t_ray *ray);
void			update_ray(t_data *data, int x, int y);
t_ray			ray_create(const t_vector origin, const t_vector direction);
t_ray			create_shadow_ray(t_vector surface_point, t_vector light_pos);
double			hit_sphere(const t_sphere *sp, const t_ray *r);
double			hit_cylinder(t_cylinder *cyl, const t_ray r);

// RENDER
void			shoot_ray(t_data *data);
void			reset_pix(t_pixel *pix);
int				render_pixel(t_data *data, int x, int y);

#endif // !MINIRT_H