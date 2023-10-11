/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 10:50:44 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/10/11 15:54:04 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "parser.h"

// TODO --> better names for some variables in camera
// TODO --> replace all "magic numbers" to DEFINES with names
// TODO --> check if this can be done only once or when camera is moved
void	init_camera(t_data *data)
{
	data->scene.camera.vup.x = 0;
    data->scene.camera.vup.y = 1;
    data->scene.camera.vup.z = 0;
///--
	// data->scene.camera.hvac = tan(data->scene.camera.fov / 2);
	// data->scene.camera.focal = subtract(data->scene.camera.position, data->scene.camera.lookat);
    // data->scene.camera.f_len = length(data->scene.camera.focal);
	// data->scene.camera.viewport_height = 2.0 * data->scene.camera.hvac * data->scene.camera.f_len;// here
	// data->scene.camera.viewport_width =data->scene.camera.viewport_height * ((double)(WIDTH)/(double)HEIGHT);
    // data->scene.camera.w1 = normalize(data->scene.camera.focal);
    // data->scene.camera.u1 = cross(data->scene.camera.vup,data->scene.camera.w1);
    // data->scene.camera.u1 = normalize(data->scene.camera.u1);
    // data->scene.camera.v1 = cross(data->scene.camera.w1, data->scene.camera.u1);
    // data->scene.camera.u = vec_multis(data->scene.camera.u1, data->scene.camera.viewport_width);
    // data->scene.camera.v = vec_multis(data->scene.camera.v1, -data->scene.camera.viewport_height);
	// data->scene.camera.pixu =vec_divide(data->scene.camera.u, (float)WIDTH);
	// data->scene.camera.pixv = vec_divide(data->scene.camera.v, (float)HEIGHT);
    // data->scene.camera.help = vec_multis(data->scene.camera.w1, data->scene.camera.f_len);
    // data->scene.camera.help1 = subtract(data->scene.camera.position, data->scene.camera.help);// maybe in this part we need to check
	
	// data->scene.camera.help = vec_divide(data->scene.camera.u, 2.0);
	// data->scene.camera.up_left = subtract(data->scene.camera.help1, data->scene.camera.help);
	// data->scene.camera.help = (vec_divide(data->scene.camera.v, 2.0));
	// data->scene.camera.up_left = subtract(data->scene.camera.up_left, data->scene.camera.help);
	// data->scene.camera.help = vec_add(data->scene.camera.pixu, data->scene.camera.pixv);
	// data->scene.camera.help1 = vec_multis(data->scene.camera.help, 0.5); // I need to remember what is 0.5 
	// data->scene.camera.pixel = vec_add(data->scene.camera.up_left, data->scene.camera.help1);

	data->scene.camera.hvac = tan(data->scene.camera.fov / 2);
    //data->scene.camera.focal = subtract(data->scene.camera.position, data->scene.camera.orientation);
    //data->scene.camera.f_len = length(data->scene.camera.focal);
	data->scene.camera.f_len = 1;
	data->scene.camera.focal = vec_multis(data->scene.camera.orientation, -1 );
	data->scene.camera.viewport_height = 2.0 * data->scene.camera.hvac * data->scene.camera.f_len;
	data->scene.camera.viewport_width =data->scene.camera.viewport_height * ((double)(WIDTH)/(double)HEIGHT);
    data->scene.camera.w1 = normalize(data->scene.camera.focal);
    data->scene.camera.u1 = cross(data->scene.camera.vup,data->scene.camera.w1);
    data->scene.camera.u1 = normalize(data->scene.camera.u1);
    data->scene.camera.v1 = cross(data->scene.camera.w1, data->scene.camera.u1);
    data->scene.camera.u = vec_multis(data->scene.camera.u1, data->scene.camera.viewport_width);
    data->scene.camera.v = vec_multis(data->scene.camera.v1, -data->scene.camera.viewport_height);
	data->scene.camera.pixu =vec_divide(data->scene.camera.u, (float)WIDTH);
	data->scene.camera.pixv = vec_divide(data->scene.camera.v, (float)HEIGHT);
    data->scene.camera.help = vec_multis(data->scene.camera.w1, data->scene.camera.f_len);
    data->scene.camera.help1 = subtract(data->scene.camera.position, data->scene.camera.help);// maybe in this part we need to check
	data->scene.camera.help = vec_divide(data->scene.camera.u, 2.0);
	data->scene.camera.up_left = subtract(data->scene.camera.help1, data->scene.camera.help);
	data->scene.camera.help = (vec_divide(data->scene.camera.v, 2.0));
	data->scene.camera.up_left = subtract(data->scene.camera.up_left, data->scene.camera.help);
	data->scene.camera.help = vec_add(data->scene.camera.pixu, data->scene.camera.pixv);
	data->scene.camera.help1 = vec_multis(data->scene.camera.help, 0.5); // I need to remember what is 0.5 
	data->scene.camera.pixel = vec_add(data->scene.camera.up_left, data->scene.camera.help1);

	
	// data->scene.camera.hvac = tan(data->scene.camera.fov / 2);
    // data->scene.camera.focal = subtract(data->scene.camera.position, data->scene.camera.orientation);
    // data->scene.camera.f_len = length(data->scene.camera.focal);
	// data->scene.camera.viewport_height = 2.0 * data->scene.camera.hvac * data->scene.camera.f_len;
	// data->scene.camera.viewport_width =data->scene.camera.viewport_height * ((double)(WIDTH)/(double)HEIGHT);
    // data->scene.camera.w1 = normalize(data->scene.camera.focal);
    // data->scene.camera.u1 = cross(data->scene.camera.vup,data->scene.camera.w1);
    // data->scene.camera.u1 = normalize(data->scene.camera.u1);
    // data->scene.camera.v1 = cross(data->scene.camera.w1, data->scene.camera.u1);
    // data->scene.camera.u = vec_multis(data->scene.camera.u1, data->scene.camera.viewport_width);
    // data->scene.camera.v = vec_multis(data->scene.camera.v1, -data->scene.camera.viewport_height);
	// data->scene.camera.pixu =vec_divide(data->scene.camera.u, (float)WIDTH);
	// data->scene.camera.pixv = vec_divide(data->scene.camera.v, (float)HEIGHT);
    // data->scene.camera.help = vec_multis(data->scene.camera.w1, data->scene.camera.f_len);
    // data->scene.camera.help1 = subtract(data->scene.camera.position, data->scene.camera.help);// maybe in this part we need to check
	// data->scene.camera.help = vec_divide(data->scene.camera.u, 2.0);
	// data->scene.camera.up_left = subtract(data->scene.camera.help1, data->scene.camera.help);
	// data->scene.camera.help = (vec_divide(data->scene.camera.v, 2.0));
	// data->scene.camera.up_left = subtract(data->scene.camera.up_left, data->scene.camera.help);
	// data->scene.camera.help = vec_add(data->scene.camera.pixu, data->scene.camera.pixv);
	// data->scene.camera.help1 = vec_multis(data->scene.camera.help, 0.5); // I need to remember what is 0.5 
	// data->scene.camera.pixel = vec_add(data->scene.camera.up_left, data->scene.camera.help1);
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
