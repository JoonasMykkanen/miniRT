/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joonasmykkanen <joonasmykkanen@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:50:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/17 08:51:18 by joonasmykka      ###   ########.fr       */
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
	cam->f_len = length(cam->focal);
	cam->focal = subtract(cam->position, cam->orientation);
	*vp_h = 2.0 * hvac * cam->f_len;
	*vp_w = *vp_h * ((double)(WIDTH)/(double)HEIGHT);
}

void	init_camera(t_data *data)
{
	double		viewport_height;
	double		viewport_width;
	t_vector	forward;
	t_vector	right;
	t_vector	up;
	
	basic_params(&data->scene.camera, &viewport_height, &viewport_width);
	forward = normalize(data->scene.camera.focal);
	right = cross(data->scene.camera.vup, forward);
	right = normalize(right);
	up = cross(forward, right);
	right = vec_multis(right, viewport_width);
	data->scene.camera.pixu = vec_divide(right, (float)WIDTH);
	up = vec_multis(up, -viewport_height);
	data->scene.camera.pixv = vec_divide(up, (float)HEIGHT);
	data->scene.camera.help = vec_multis(forward, data->scene.camera.f_len);
    data->scene.camera.help1 = subtract(data->scene.camera.position, data->scene.camera.help);
	data->scene.camera.help = vec_divide(right, 2.0);
	data->scene.camera.up_left = subtract(data->scene.camera.help1, data->scene.camera.help);
	data->scene.camera.help = vec_divide(up, 2.0);
	data->scene.camera.up_left = subtract(data->scene.camera.up_left, data->scene.camera.help);
	data->scene.camera.help = vec_add(data->scene.camera.pixu, data->scene.camera.pixv);
	data->scene.camera.help1 = vec_multis(data->scene.camera.help, 0.5);
	data->scene.camera.pixel = vec_add(data->scene.camera.up_left, data->scene.camera.help1);
}

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
