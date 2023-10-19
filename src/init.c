/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:50:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/19 13:01:14 by joonasmykka      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

// Defines up vector and calculates viewport height and width
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

	cam = &data->scene.camera;
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
	if (read_input(data, file) != OK)
		return (ERROR);
	data->mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!data->mlx)
	{
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), ERROR);
		return (ERROR);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		mlx_close_window(data->mlx);
		ft_putstr_fd((char *)mlx_strerror(mlx_errno), ERROR);
		return (ERROR);
	}
	return (OK);
}
