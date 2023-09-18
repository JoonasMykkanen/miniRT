/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/18 11:13:31 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int draw_plane(t_data *data, int x, int y, double *pt)
{
	double 	numerator = dotProduct(data->scene.planes[0].point, data->scene.planes[0].normal) - dotProduct(data->scene.ray.orig, data->scene.planes[0].normal);
	double 	denominator = dotProduct(data->scene.ray.dir, data->scene.planes[0].normal);
	
	double	max = 10;
	double	min = -1 * max;

	if (denominator == 0.0) {
		return (0x000000ff);
	}

	double t = numerator / denominator;
	*pt = t;

	if (t > 0) {
		t_vector intersection_point = vec_add(vec_multis(data->scene.ray.dir, t), data->scene.ray.orig);
		
    	if (intersection_point.x > max || intersection_point.x < min || intersection_point.z > max || intersection_point.z < min || intersection_point.y > max || intersection_point.y < min)
			return (0x000000ff);
		return (ft_color(100, 100, 100, 0xff));
	}
	return (0x000000ff);
}


double hit_sphere(const t_vector center, double radius, const t_ray r) {
    t_vector oc = subtract(r.orig, center);
    double a = dotProduct(r.dir, r.dir);
    double b = 2.0 * dotProduct(oc, r.dir);
    double c = dotProduct(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
	if(discriminant < 0)
		return -1;
	else
		return (-b - sqrt(discriminant) ) / (2.0 * a);
}

// TODO --> better names for some variables in camera
// TODO --> replace all "magic numbers" to DEFINES with names
// TODO --> check if this can be done only once or when camera is moved
void	init_camera(t_data *data)
{
	data->scene.camera.vup.x = 0;
    data->scene.camera.vup.y = 1;
    data->scene.camera.vup.z = 0;
	data->scene.camera.hvac = tan(data->scene.camera.fov / 2);
    data->scene.camera.focal = subtract(data->scene.camera.position, data->scene.camera.orientation);
    data->scene.camera.f_len = length(data->scene.camera.focal);
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
}

void	render(void *param)
{
	static int render_frame = 0;
	clock_t start, end;
    double cpu_time_used;
	start = clock();
	
	t_data *data = (t_data *)param;
	init_camera(data);
    
    t_vector scaled_direction;
	t_vector ray_d;
    t_vector hit_pos;
    t_vector norm;
	
	uint32_t color;

    t_sphere aux;
    double t66 = 5000000000000.0;
    double hit;
    int a2;
	
	for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
			update_ray(data, i, j, &ray_d);
			t66 = 5000000000000.0;
			// Check for sphere hit's
			for (int idx = 0; idx < data->scene.num_spheres; idx++) {
                hit = hit_sphere(data->scene.spheres[idx].center, data->scene.spheres[idx].radius, data->scene.ray);
                if((hit < t66) && (hit > 0))
                {
                    aux = data->scene.spheres[idx];
                    t66 = hit;
                    a2 =idx;
                }
            }
			
			double pt;
			color = draw_plane(data, j, i, &pt);
			if (pt < t66) {
				mlx_put_pixel(data->img, i, j, color);
			}
            else if (t66 != 5000000000000.0) {
			// if (t66 != 5000000000000.0) {
                scaled_direction = vec_multis(ray_d, t66);
                hit_pos = subtract(data->scene.ray.orig, data->scene.spheres[a2].center);
                hit_pos = vec_add(hit_pos, scaled_direction);
                norm =normalize(hit_pos);
               
                double d =fmax(dotProduct(norm, data->scene.light.position), 0.00f);

				double ambientR = data->scene.ambient.color.red * data->scene.ambient.intensity;
				double ambientG = data->scene.ambient.color.green * data->scene.ambient.intensity;
				double ambientB = data->scene.ambient.color.blue * data->scene.ambient.intensity;

				ambientR *= data->scene.spheres[a2].color.red / 255.0;
				ambientG *= data->scene.spheres[a2].color.green / 255.0;
				ambientB *= data->scene.spheres[a2].color.blue / 255.0;

				double spotR = (d * data->scene.light.brightness * data->scene.light.color.red) * data->scene.spheres[a2].color.red / 255.0;
				double spotG = (d * data->scene.light.brightness * data->scene.light.color.green) *  data->scene.spheres[a2].color.green / 255.0;
				double spotB = (d * data->scene.light.brightness * data->scene.light.color.blue) * data->scene.spheres[a2].color.blue / 255.0;

				int red = (int)(ambientR + spotR);
				int green = (int)(ambientG + spotG);
				int blue = (int)(ambientB + spotB);

				if (red > 255) red = 255;
				if (green > 255) green = 255;
				if (blue > 255) blue = 255;
                
                color  = ft_color(red, green, blue, 0xff);
			} else {
				color = 0x000000ff;
			}
		    mlx_put_pixel(data->img, i, j, color);
		}
	}
	
	render_frame++;
	end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	if (render_frame == 20) {
    	printf("render() took %f seconds to execute\n", cpu_time_used);
		render_frame = 0;
	}
}

void	ft_hook(void *param)
{
	t_data	*data = (t_data *)param;
	
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);

	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		update_camera(data, HORIZONTAL, -0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		update_camera(data, HORIZONTAL, 0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		update_camera(data, DEPTH, 0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		update_camera(data, DEPTH, -0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		update_camera(data, VERTICAL, 0.1f);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		update_camera(data, VERTICAL, -0.1f);
}
int	minirt(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1)
	{
		mlx_close_window(data->mlx);
		puts(mlx_strerror(mlx_errno));
		return(ERROR);
	}

	mlx_loop_hook(data->mlx, render, data);
	mlx_loop_hook(data->mlx, ft_hook, data);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (OK);
}

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc == 2)
	{
		if (init(&data, argv[1]) != OK)
			return (ERROR);
		minirt(&data);
	}
	else
		ft_putstr_fd("Error with inputfile\n", 2);
	return (OK);
}