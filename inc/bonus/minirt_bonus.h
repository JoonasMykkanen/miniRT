/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 12:17:31 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/31 11:17:27 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_BONUS_H
# define MINIRT_BONUS_H

# include "../../src/mlx42/include/MLX42/MLX42.h"
# include "../../src/libft/inc/libft.h"
# include <stdbool.h>
# include <pthread.h>
# include <sys/time.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# define FLT_MAX 3.402823e+38
# define FLT_MIN 1.175494e-38
# define EPSILON 0.001
# define MAX_OBJ 100

# define WORKERS 5

# define HEIGHT 800
# define WIDTH 1300

# define ERROR 2
# define OK 0

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

# define PLANE_SHINE 100
# define PLANE_SPECULAR 0.5
# define PLANE_REFLECTION 0.5

# define SPHERE_SHINE 100
# define SPHERE_SPECULAR 0.5
# define SPHERE_REFLECTION 0.0

# define CYLINDER_SHINE 100
# define CYLINDER_SPECULAR 0.5
# define CYLINDER_REFLECTION 0.0

typedef struct s_data	t_data;
typedef struct s_job 	t_job;

typedef struct s_job
{
	bool	done;
	int		row;

	t_job	*next;
}				t_job;

typedef struct	s_worker
{
	pthread_t	employee;
	t_data		*data;
	int			index;
}				t_worker;

typedef struct s_threadpool
{
	pthread_mutex_t	queue;
	pthread_mutex_t	alive;
	pthread_mutex_t	write;
	pthread_cond_t	cond;
	
	bool			ready;
	bool			done;
	
	t_job		*job_list;
	t_worker	workers[WORKERS];
	
}				t_threadpool;

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
	t_vector	center1;
	t_vector	axis;
	int			flag;
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

	t_light		lights[MAX_OBJ];
	bool		in_shadow[MAX_OBJ];
	int			num_lights;

	t_sphere	spheres[MAX_OBJ];
	int			num_spheres;

	t_plane		planes[MAX_OBJ];
	int			num_planes;
	t_ray		ray;

	t_cylinder	cylinders[MAX_OBJ];
	int			num_cylinders;
}				t_scene;

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

typedef struct s_obj
{
	int			idx;
	int			type;
	double		radius;

	double		shine;
	double		specular;
	double		reflection;

	t_vector	axis;
	t_vector	point;
	t_color		color;
}				t_obj;

typedef struct s_pixel
{
	bool		reflection_found;
	t_color		cache_color;
	double		closest_t;
	int			obj_type;
	int			obj_idx;
	t_color		ambient;
	int			shadow;
	int			is_cap;
	int			color;
	int			self;
	int			side;

	t_vector	scaled_dir;
	t_vector	light_dir;
	t_vector	hit_pos;
	t_vector	hit_norm;
	t_vector	norm;
}				t_pixel;

typedef struct s_data
{
	mlx_image_t		*img;
	mlx_t			*mlx;

	t_threadpool	pool;

	t_obj			obj[WORKERS];
	t_pixel			pix[WORKERS];
	t_scene			scene[WORKERS];
}				t_data;

// GENERAL
double		ft_atof(char *str);
int			arr_len(char **arr);
void		free_arr(char **arr);
void		clamp_colors(t_color *color);
int			validate_scene(t_data *data);
int			init(t_data *data, char *file);
t_color		color_add(t_color c1, t_color c2);
int			ft_color(int r, int g, int b, int a);
double		hit_cylinder2(t_cylinder *cyl, t_ray r);
int			ay(t_helpc2 *point, t_cylinder *cyl, t_ray r);
void		hit_cylinder3(t_helpc *hit, t_ray r, t_vector cyl);
void		init_cyl(t_cylinder *cyl, const t_ray r, t_helpc2 *point);
void		init_camera(t_data *data, double vp_height, double vp_width);
double		hit_cap(t_ray r, t_vector pos, t_vector normal, t_cylinder *cyl);

// LIGHT
void		check_rgb_values(t_color *color);
int			is_in_shadow(t_vector point, t_data *d, int i);
t_color		calculate_ambient(t_data *data, t_color *color, int i);
t_color		calculate_color(t_data *data, t_obj *obj, t_vector inter, int i);
double		calculate_cap(t_data *data, t_vector inter, t_cylinder *cyl, int i, int idx);
double		calculate_body(t_data *data, t_vector inter, t_cylinder *cyl, int i, int idx);
void		check_reflections(t_data *data, t_vector inter, t_color surface, int i);
void		spotlight_effect(t_light *light, t_obj *obj, t_color *c, double d);


// HOOK
void		render(void *param);
void		ft_hook(void *param);
void		handle_exit(void *param);

// MATH
double		length(t_vector v);
double		length_squared(t_vector v);
double		dist(t_vector a, t_vector b);
t_vector	subtract(t_vector a, t_vector b);
double		dot_product(t_vector a, t_vector b);
t_vector	vec_divide(const t_vector v, float r);
t_vector	vec_multis(const t_vector v, float r);
t_vector	cross(t_vector forward, t_vector position);
t_vector	vec_add(const t_vector v1, const t_vector v2);

// RAY
t_vector	normalize(t_vector vector);
t_vector	ray_at(const t_ray r, double t);
double		hit_cylinder(t_cylinder *cyl, const t_ray r);
void		update_ray(t_data *data, int x, int y, int i);
void		check_planes(t_data *data, t_ray *ray, int i);
void		check_spheres(t_data *data, t_ray *ray, int i);
double		hit_sphere(const t_sphere *sp, const t_ray *r);
void		check_cylinders(t_data *data, t_ray *ray, int i);
double		hit_plane(const t_plane *plane, const t_ray *ray);
t_ray		ray_create(const t_vector origin, const t_vector direction);

// RENDER
void		reset_pix(t_data *data, int i);
void		shoot_ray(t_data *data, t_ray *ray, int i);
int			render_pixel(t_data *data, int x, int y, int i);

// Job queue
t_job		*new_job(int data);
int			create_jobs(t_data *data);
int			get_next_job(t_job *start);
void		free_job_list(t_job *start);
void		reset_job_list(t_job *start);
int			push_job_list(t_job **start, int data);

// Threadpool
void		*routine(void *param);
int			check_alive(t_data *data);
int			kill_workers(t_data *data);
int			wakeup_workers(t_data *data);

#endif // !MINIRT_H