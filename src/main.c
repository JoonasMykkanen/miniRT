/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 13:27:04 by joonasmykka       #+#    #+#             */
/*   Updated: 2023/09/13 13:58:15 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// TESTING STARTS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int interpolate(int start, int end, float t)
{
    return (int)(start * (1 - t) + end * t);
}

double dotProduct(t_vector a, t_vector b)
{
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_vector subtract(t_vector a, t_vector b) {
    t_vector result;
	
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;
	
    return result;
}

t_vector normalize(t_vector vector)
{
    double length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    t_vector normalizedVector = {
        vector.x / length,
        vector.y / length,
        vector.z / length
    };
    return normalizedVector;
}

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

int	iterate_spheres(t_data *data, int x, int y, double *closest)
{
	t_vector scaled_direction;
	t_vector hit_pos;
	t_vector light;
	t_vector norm;
	t_vector ray_origin;
	t_vector ray_dir;

	for (int i = 0; i < data->scene.num_spheres; i++) {
		ray_origin.x = data->scene.camera.position.x - data->scene.spheres[i].center.x;
		ray_origin.y = data->scene.camera.position.y - data->scene.spheres[i].center.y;
		ray_origin.z = data->scene.camera.position.z - data->scene.spheres[i].center.z;
		ray_dir.x = ((double)x / (double)WIDTH - 0.5) * data->aspect_ratio * tan(data->scene.camera.fov / 2.0);
		ray_dir.y = (0.5 - (double)y / (double)HEIGHT) * tan(data->scene.camera.fov / 2.0);
		ray_dir.z = -1;
		ray_dir = normalize(ray_dir);
		
		double	r = data->scene.spheres[i].radius;
		
		float a = dotProduct(ray_dir, ray_dir);
		float b = 2.0 * (dotProduct(ray_dir, ray_origin));
		float c = (dotProduct(ray_origin, ray_origin)) - (r * r);
		float des = (b * b) - (4 * (a * c));
		if (des >= 0.0f)
		{
			double t = (-b - sqrt(des)) / (2.0f * a);
			scaled_direction.x = ray_dir.x * t;
			scaled_direction.y = ray_dir.y * t;
			scaled_direction.z = ray_dir.z * t;

			hit_pos.x = ray_origin.x + scaled_direction.x;
			hit_pos.y = ray_origin.y + scaled_direction.y;
			hit_pos.z = ray_origin.z + scaled_direction.z;

			light.x = hit_pos.x + data->scene.light.position.x;
			light.y = hit_pos.y + data->scene.light.position.y;
			light.z = hit_pos.z + data->scene.light.position.z;
			
			norm.x = hit_pos.x - data->scene.spheres[i].center.x;
			norm.y = hit_pos.y - data->scene.spheres[i].center.y;
			norm.z = hit_pos.z - data->scene.spheres[i].center.z;
			
			norm = normalize(norm);
			light = normalize(light);

			double d =fmax((dotProduct(norm, (light))), 0.00f);

			// Ambient Contributions
			double ambientR = data->scene.ambient.color.red * data->scene.ambient.intensity;
			double ambientG = data->scene.ambient.color.green * data->scene.ambient.intensity;
			double ambientB = data->scene.ambient.color.blue * data->scene.ambient.intensity;

			// Multiply ambient light with the object color
			ambientR *= data->scene.spheres[i].color.red / 255.0;
			ambientG *= data->scene.spheres[i].color.green / 255.0;
			ambientB *= data->scene.spheres[i].color.blue / 255.0;

			// Spot Light Contributions
			double spotR = (d * data->scene.light.brightness * data->scene.light.color.red) * data->scene.spheres[i].color.red / 255.0;
			double spotG = (d * data->scene.light.brightness * data->scene.light.color.green) *  data->scene.spheres[i].color.green / 255.0;
			double spotB = (d * data->scene.light.brightness * data->scene.light.color.blue) * data->scene.spheres[i].color.blue / 255.0;

			// Add both contributions
			int red = (int)(ambientR + spotR);
			int green = (int)(ambientG + spotG);
			int blue = (int)(ambientB + spotB);

			// Ensure values don't exceed 255
			if (red > 255) red = 255;
			if (green > 255) green = 255;
			if (blue > 255) blue = 255;
				
			int color = ft_color(red, green, blue, 0xff);
			// }
			// if (color != )
			return (color);
		}
		// else
		// 	continue ;
	}
	return (0x000000ff);
}

int	draw_plane(t_data *data, int x, int y)
{
	t_vector ray_origin;
	t_vector ray_dir;
	ray_origin.x = data->scene.camera.position.x;
	ray_origin.y = data->scene.camera.position.y;
	ray_origin.z = data->scene.camera.position.z;
	ray_dir.x = ((double)x / (double)WIDTH - 0.5) * data->aspect_ratio * tan(data->scene.camera.fov / 2.0);
	ray_dir.y = (0.5 - (double)y / (double)HEIGHT) * tan(data->scene.camera.fov / 2.0);
	ray_dir.z = -1;
	ray_dir = normalize(ray_dir);

	double numerator = dotProduct(subtract(data->scene.planes[0].point, ray_origin), data->scene.planes[0].normal);
    double denominator = dotProduct(ray_dir, data->scene.planes[0].normal);
	if(denominator == 0.0) {
        return (0x000000ff);
    }
    double t =  numerator / denominator;
	if (t > 0) {
		return (0xffffffff);		
	}
	return (0x000000ff);
}
//----
double lengthSquared(t_vector v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

// Function to calculate the length (magnitude) of a 3D vector given its components
double length(t_vector v) {
    return sqrt(lengthSquared(v));
}

t_vector cross(t_vector forward, t_vector position) {
    t_vector result;
    result.x = forward.y * position.z - forward.z * position.y;
    result.y = forward.z * position.x - forward.x * position.z;
    result.z = forward.x * position.y - forward.y * position.x;
    return (result);
}

t_vector vec_multis(const t_vector v, float r) {
    t_vector result;
    result.x = v.x * r;
    result.y = v.y * r;
    result.z = v.z * r;
    return result;
}
t_vector vec_divide(const t_vector v, float r) {
    t_vector result;
    result.x = v.x / r;
    result.y = v.y / r;
    result.z = v.z / r;
    return result;
}

t_vector vec_add(const t_vector v1, const t_vector v2) {
    t_vector result;
    result.x = v1.x + v2.x;
    result.y = v1.y + v2.y;
    result.z = v1.z + v2.z;
    return result;

}
// delete later
void create_sphere(t_sphere *sphe)
{
    //sphe->spheres[3];
    for(int i =0; i < 3; i++)
    {
        sphe[i].center.x =  1 + 0.30 * i;
        sphe[i].center.y =  0;
        sphe[i].center.z =  -i;
        sphe[i].radius = 0.25;
        
    }
    
}


t_ray ray_create(const t_vector origin, const t_vector direction) {
    t_ray r;
    r.orig = origin;
    r.dir = direction;
    return r;
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
    //return (discriminant >= 0);
}
t_vector ray_at(const t_ray r, double t) {
	t_vector help;
	help = vec_multis(r.dir, (float)t);
    return vec_add(r.orig, help);
}

t_vector add_color(const t_vector c1, const t_vector c2) {
    return (t_vector){c1.x + c2.x, c1.y + c2.y, c1.z + c2.z};
}

double hit_sphere(const t_vector center, double radius, const t_ray r);

t_vector ray_color(const t_ray r) {
    t_vector unit_direction = normalize(r.dir);
    double a = 0.5 * (unit_direction.y + 1.0);
    t_vector white;// = make_color(1.0, 1.0, 1.0);
    t_vector blue;// = make_color(0.5, 0.7, 1.0);
    t_vector help;
    t_vector n;
    help.x =0;
    help.y =0;
    help.z =0;
    double t = hit_sphere(help, 0.5, r);
    if (t > 0) {
        n = ray_at(r, t);
        n = subtract(n, help);
        n = normalize(n);
        n.x = 0.5 * (n.x + 1);
        n.y = 0.5 * (n.y + 1);
        n.z = 0.5 * (n.z + 1);
        return n;
    }
	white.x =1;
	white.y =1;
	white.z =1;
	blue.x = 0.5;
	blue.y = 0.7;
	blue.z = 1.0;
	// auto a = 0.5*(unit_direction.y() + 1.0);
    // return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
	white =  vec_multis(white, (float)(1.0 - a));
	blue =  vec_multis(blue, (float)(a));
    return add_color(white, blue);
}

///-----------

void perPixel(int x, int y, t_data *data)
{
	double closest = MAXFLOAT;
	int color = 0x000000ff;
	
    color = iterate_spheres(data, x, y, &closest);

	// color = draw_plane(data, x, y);

	mlx_put_pixel(data->img, x, y, color);
}

void	render(void *param)
{
	t_data *data = (t_data *)param;
	//--------
	t_vector camerac;
	
    //double fov  = 80 * M_PI / 180.0f; done 
	
    //double h = tan((fov / 2));
	data->scene.camera.htan = tan((data->scene.camera.fov) / 2);	//= tan((data->camerafov / 2));
	// camerac.x =-0;
	// camerac.y  =0;
	// camerac.z =1;
	data->scene.camera.position.x= 0;
	data->scene.camera.position.y= 0;
	data->scene.camera.position.z= 3;
	//t_vector ray_d;
	float fl=1;
	// t_vector u;
	// t_vector v;
	// t_vector z;
	// t_vector up_left;
	// t_vector help;
	// t_vector help1;
	// t_vector pixel;
	// t_vector center;
	// t_vector pixu;
	// t_vector pixv; 
    // t_vector lookat;//   = point3(0,0,0);   // Point camera is looking at
    // t_vector   vup;//      = vec3(0,1,0);
    // t_vector u1;
    // t_vector v1;
    // t_vector  w1;
    
    data->scene.camera.lookat.x =0;
    data->scene.camera.lookat.y =0;
    data->scene.camera.lookat.z =0;
    data->scene.camera.vup.x = 0;
    data->scene.camera.vup.y = 1;
    data->scene.camera.vup.z = 0;
    // t_vector w;
    // t_vector focal;
    // double f_len;
    //camerac= lookfrom; 
    
    data->scene.camera.focal = subtract(data->scene.camera.position, data->scene.camera.lookat);
    data->scene.camera.f_len = length(data->scene.camera.focal);
	data->scene.camera.viewport_height = 2.0 * data->scene.camera.htan * data->scene.camera.f_len;
	data->scene.camera.viewport_width =data->scene.camera.viewport_height * ((double)(WIDTH)/(double)HEIGHT);
	// double viewport_height = 2.0 * h * f_len;
	// double viewport_width = viewport_height * ((double)(WIDTH)/(double)HEIGHT);
    data->scene.camera.w1 = normalize(data->scene.camera.focal);
    data->scene.camera.u1 = cross(data->scene.camera.vup,data->scene.camera.w1);
    data->scene.camera.u1 = normalize(data->scene.camera.u1);
    data->scene.camera.v1 = cross(data->scene.camera.w1, data->scene.camera.u1);
	// z.x=0;
	// z.y =0;
	// z.z = fl;
	// u.x = viewport_width;
	// u.y = 0;
	// u.z =0;
    data->scene.camera.u = vec_multis(data->scene.camera.u1, data->scene.camera.viewport_width);
	// v.x =0;
	// v.y = -viewport_height;
	// v.z =0;
    data->scene.camera.v = vec_multis(data->scene.camera.v1, -data->scene.camera.viewport_height);
	data->scene.camera.pixu =vec_divide(data->scene.camera.u, (float)WIDTH);
	data->scene.camera.pixv = vec_divide(data->scene.camera.v, (float)HEIGHT);
    data->scene.camera.help = vec_multis(data->scene.camera.w1, data->scene.camera.f_len);
    data->scene.camera.help1 = subtract(data->scene.camera.position, data->scene.camera.help);// maybe in this part we need to check

    
	//help1 = vec_subtract(&camerac, &z);

	data->scene.camera.help = vec_divide(data->scene.camera.u, 2.0);
	//help = Vec_divide(&u, 2.0);
	data->scene.camera.up_left = subtract(data->scene.camera.help1, data->scene.camera.help);
	data->scene.camera.help = (vec_divide(data->scene.camera.v, 2.0));
	data->scene.camera.up_left = subtract(data->scene.camera.up_left, data->scene.camera.help);
	data->scene.camera.help = vec_add(data->scene.camera.pixu, data->scene.camera.pixv);
	data->scene.camera.help1 = vec_multis(data->scene.camera.help, 0.5); // I need to remember what is 0.5 
	data->scene.camera.pixel = vec_add(data->scene.camera.up_left, data->scene.camera.help1);
	
	
	// help = (Vec_divide(&v, 2.0));
	// up_left = vec_subtract(&up_left, &help);
	// help = vec_add(&pixu, &pixv);
	// help1 = vec_multis(&help, 0.5); 
	// pixel = vec_add(&up_left, &help1);
	// t_ray r;
	
	
	
	uint32_t color= ft_pixel(
				0x00, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
				0x00,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
				0x00, // B
				0xFF
				);
    double tc;
    double *t1, *t2;
    t_vector scaled_direction;
    t_vector hit_pos;
    t_vector norm;
    int blue =0;
    t_sphere sphe[3];
    create_sphere(sphe);
    t_sphere aux;
    double t66 = 5000000000000.0;
    double hit;
    int a2;
    int green;
    int red;
	t_sphere sphera;
	sphera.center.x = -0.5;
	sphera.center.y = 0;
	sphera.center.z = -1;

	t_vector ray_d;

	//-------
	for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
			data->scene.camera.help = vec_multis(data->scene.camera.pixu, (float)i);
			data->scene.camera.help1 = vec_multis(data->scene.camera.pixv, (float)j);
			data->scene.camera.center = vec_add(data->scene.camera.help, data->scene.camera.help1);
			data->scene.camera.center = vec_add(data->scene.camera.center, data->scene.camera.pixel);
			ray_d = subtract(data->scene.camera.center, data->scene.camera.position);
			data->scene.ray = ray_create(data->scene.camera.position, ray_d);
            //t66 = 5000000000000.0;
            // if(hit_sphere(sphera.center, 0.5, data->scene.ray)){
			// 	color = ft_pixel(
			// 	255, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
			// 	0x00,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
			// 	0x00, // B
			// 	0xFF
			// 	);
			
            // for(int a = 0; a < 3; a++)
            // {
				
            //     hit = hit_sphere(sphe[a].center, 0.5, data->scene.ray);
            //     if((hit < t66) && (hit > 0))
            //     {
            //         t66 = hit;
            //         aux = sphe[a];
            //         a2 =a;
            //     }
                
                
            // }
            // if(t66 != 5000000000000.0){
            //     scaled_direction = vec_multis(ray_d, t66);
			// 	// scaled_direction.x = ray_d.x * t55;
            //     // scaled_direction.y =ray_d.y * t55;
            //     // scaled_direction.z = ray_d.z * t55;
            //     hit_pos = subtract(data->scene.ray.orig, sphe[a2].center);
            //     hit_pos = vec_add(hit_pos, scaled_direction);
            //     // hit_pos.x = ray_o.x + scaled_direction.x;
            //     // hit_pos.y = ray_o.y + scaled_direction.y;
            //     // hit_pos.z = ray_o.z + scaled_direction.z;
            //     // hit_pos.x = r.orig.x  + scaled_direction.x;
            //     // hit_pos.y = origen.y + scaled_direction.y;
            //     // hit_pos.z = origen.z + scaled_direction.z;
            //     norm =normalize(hit_pos);
               
            //     double d2 =fmax((dotProduct(norm, (data->scene.light.position))), 0.00f);
                
            //     blue = (int)(0.7* (255 * d2)) + (int)((0.2 * 255));// make something 0  to 1 multiple  by 2551 I added the ambient // later we consider what is the color of the  this will grow with multiple by color of our object
            //     if(blue > 255)
            //         blue =255;
            //     red = (int)(0.7* (255 * d2)) + (int)((0.2 * 255));// make something 0  to 1 multiple  by 2551 I added the ambient // later we consider what is the color of the  this will grow with multiple by color of our object
            //     if(red > 255)
            //         red =255;
            //     green = (int)(0.7* (255 * d2)) + (int)((0.2 * 255));// make something 0  to 1 multiple  by 2551 I added the ambient // later we consider what is the color of the  this will grow with multiple by color of our object
            //     if(green > 255)
            //         green =255;
            //     if (a2 == 0)
            //     {
            //     color = ft_pixel(
			// 	0x00, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
			// 	0x00,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
			// 	blue, // B
			// 	0xFF
			// 	);
            //     }else if (a2 == 1)
            //     {
            //         color = ft_pixel(
			// 	0x00, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
			// 	green,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
			// 	0x00, // B
			// 	0xFF
			// 	);
                    
            //     }else if (a2 == 2)
            //     {
            //         color = ft_pixel(
			// 	red, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
			// 	0x00,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
			// 	0x00, // B
			// 	0xFF
			// 	);
            //     }
			// // if (t66 > 0.0)
			// // {
				
			// }else
			// {
				t_vector pixel_color = ray_color(data->scene.ray);
			
			color = ft_pixel(
				(int)(pixel_color.x * 255), //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
				(int)(pixel_color.y * 255),//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
				(int)(pixel_color.z *255), // B
				0xFF
				);
			//}
            
		    mlx_put_pixel(data->img, i, j, color);
			
		}
	}


	
	///--------
	
	// for (int y = 0; y < HEIGHT; y++) {
	// 	for (int x = 0; x < WIDTH; x++) {
	// 		perPixel(x, y, data);
	// 	}
	// }
}

void ft_hook(void* param) /// this move the camera now 
{
	t_data	*data = (t_data *)param;

	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
		//image->instances[0].y -= 5;
        data->scene.camera.position.y -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
		 data->scene.camera.position.y += 5;
        //image->instances[0].y += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		 data->scene.camera.position.x += 5;
        //image->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		 data->scene.camera.position.x -= 5;
        //image->instances[0].x += 5;
    if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
		 data->scene.camera.position.z += 5;
        //image->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		 data->scene.camera.position.z -= 5;
	
	// if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
	// 	mlx_close_window(mlx);
	// if (mlx_is_key_down(mlx, MLX_KEY_UP))
	// 	//image->instances[0].y -= 5;
    //     lookfrom.y += 0.1;
	// if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
	// 	lookfrom.y -= 0.1;
    //     //image->instances[0].y += 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
	// 	lookfrom.x += 0.1;
    //     //image->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
	// 	lookfrom.x -= 0.1;
    //     //image->instances[0].x += 5;
    // if (mlx_is_key_down(mlx, MLX_KEY_Q))
	// 	lookfrom.z += 0.1;
    //     //image->instances[0].x -= 5;
	// if (mlx_is_key_down(mlx, MLX_KEY_E))
	// 	lookfrom.z -= 0.1;
}

// void ft_hook(void* param) /// this move the camera now 
// {
// 	t_data	*data = (t_data *)param;

// 	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
// 		mlx_close_window(data->mlx);
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_UP))
// 		//image->instances[0].y -= 5;
//         data->scene.camera.position.y -= 0.1;
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_DOWN))
// 		 data->scene.camera.position.y += 0.1;
//         //image->instances[0].y += 5;
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
// 		 data->scene.camera.position.x += 0.1;
//         //image->instances[0].x -= 5;
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
// 		 data->scene.camera.position.x -= 0.1;
//         //image->instances[0].x += 5;
//     if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
// 		 data->scene.camera.position.z += 0.1;
//         //image->instances[0].x -= 5;
// 	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
// 		 data->scene.camera.position.z -= 0.1;
// }

int	test(t_data *data)
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
// TESTING ENDS

int	main(int argc, char **argv)
{
	t_data	data;
	
	if (argc == 2)
	{
		if (init(&data, argv[1]) != OK)
			return (ERROR);
		test(&data);
	}
	else
		ft_putstr_fd("Error with inputfile\n", 2);
	return (OK);
}