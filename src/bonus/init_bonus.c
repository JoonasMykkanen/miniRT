/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 15:30:00 by djames            #+#    #+#             */
/*   Updated: 2023/11/03 15:13:25 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/bonus/minirt_bonus.h"
#include "../../inc/bonus/parser_bonus.h"

void	copy_scenes(t_data *data)
{
	int	idx;

	idx = 0;
	while (++idx < WORKERS)
	{
		ft_memcpy(&data->scene[idx], &data->scene[0], sizeof(t_scene));
	}
}

int	validate_scene(t_data *data)
{
	t_scene	*s;
	int		status;

	status = OK;
	s = &data->scene[0];
	if (!s->status_ambient)
		status = ERROR;
	if (!s->status_camera)
		status = ERROR;
	if (status == ERROR)
		ft_putstr_fd("Error: Map error\n", ERROR);
	if (s->ambient.intensity == 0 && status != ERROR)
	{
		status = ERROR;
		ft_putstr_fd("Error: No ambient light found in scene\n", ERROR);
	}
	if (check_inside(data, 0) != OK)
	{
		status = ERROR;
		ft_putstr_fd("Error: Camera inside object\n", 2);
	}
	return (status);
}

void	basic_params(t_camera *cam, double *vp_h, double *vp_w)
{
	double	hvac;

	cam->vup.x = 0;
	cam->vup.y = 1;
	cam->vup.z = 0;
	hvac = tan(cam->fov / 2);
	cam->focal = subtract(cam->position, cam->orientation);
	cam->f_len = length(cam->focal);
	cam->focal = vec_multis(cam->orientation, -1);
	*vp_h = 2.0 * hvac * cam->f_len;
	*vp_w = *vp_h * ((double)(WIDTH) / (double)HEIGHT);
}

void	init_camera(t_data *data, double vp_height, double vp_width)
{
	t_vector	forward;
	t_vector	right;
	t_camera	*cam;
	t_vector	up;

	cam = &data->scene[0].camera;
	basic_params(cam, &vp_height, &vp_width);
	forward = normalize(cam->focal);
	right = cross(cam->vup, forward);
	right = normalize(right);
	up = cross(forward, right);
	right = vec_multis(right, vp_width);
	cam->pixu = vec_divide(right, (float)WIDTH);
	up = vec_multis(up, -vp_height);
	cam->pixv = vec_divide(up, (float)HEIGHT);
	cam->help = vec_multis(forward, cam->f_len);
	cam->help1 = subtract(cam->position, cam->help);
	cam->help = vec_divide(right, 2.0);
	cam->up_left = subtract(cam->help1, cam->help);
	cam->help = vec_divide(up, 2.0);
	cam->up_left = subtract(cam->up_left, cam->help);
	cam->help = vec_add(cam->pixu, cam->pixv);
	cam->help1 = vec_multis(cam->help, 0.5);
	cam->pixel = vec_add(cam->up_left, cam->help1);
}

int	init(t_data *data, char *file)
{
	ft_memset(&data->scene, 0, sizeof(data->scene));
	if (check_filename(file) != OK)
	{
		ft_putstr_fd("Error: filename\n", ERROR);
		return (ERROR);
	}
	if (read_input(data, file) != OK)
		return (ERROR);
	init_camera(data, 0, 0);
	copy_scenes(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!data->mlx)
	{
		ft_putstr_fd("Error: mlx init\n", ERROR);
		return (ERROR);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		ft_putstr_fd("Error: mlx window init\n", ERROR);
		return (ERROR);
	}
	return (OK);
}
