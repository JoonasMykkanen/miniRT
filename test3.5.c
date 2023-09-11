/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmykkane <jmykkane@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:26:20 by djames            #+#    #+#             */
/*   Updated: 2023/09/11 12:24:30 by jmykkane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */




/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:23:35 by djames            #+#    #+#             */
/*   Updated: 2023/09/08 13:52:09 by djames           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/include/MLX42/MLX42.h"



#define WIDTH 1000
#define HEIGHT 900
//#define M_PI (3.14159265358979323846)
static mlx_image_t* image;
mlx_t* mlx;



typedef struct s_vec{
    double x;
    double y;
    double z;
} t_vect;
t_vect origen;

typedef struct {
    double r;
    double g;
    double b;
} Color;

typedef struct {
    t_vect position;
    Color color;
} Light;
typedef struct s_sphe{
    t_vect center;
    double radius;
} t_sphere;


typedef struct s_quaternion{
    float x;
    float y;
    float z;
    float w;
} t_quaternion;

t_quaternion normalize_quaternion(t_quaternion q) {
    float length = sqrt(q.x * q.x + q.y * q.y + q.z * q.z + q.w * q.w);
    return (t_quaternion){q.x / length, q.y / length, q.z / length, q.w / length};
}

t_quaternion quaternion_cross(t_quaternion a, t_quaternion b) 
{
    t_quaternion result;
    result.x = a.w * b.x + a.x * b.w + a.y * b.z - a.z * b.y;
    result.y = a.w * b.y + a.y * b.w + a.z * b.x - a.x * b.z;
    result.z = a.w * b.z + a.z * b.w + a.x * b.y - a.y * b.x;
    result.w = a.w * b.w - a.x * b.x - a.y * b.y - a.z * b.z;
    return result;
}
t_quaternion vector_quaternion(t_vect v) {
    return (t_quaternion){v.x, v.y, v.z, 0.0f};
}

t_vect rotate_vector(t_vect v, t_quaternion q) 
{
    t_quaternion conjugateQ = { -q.x, -q.y, -q.z, q.w };
    t_quaternion resultQ = quaternion_cross(q, quaternion_cross((vector_quaternion(v)), conjugateQ));
    return (t_vect){resultQ.x, resultQ.y, resultQ.z};
}

double dotProduct(t_vect a, t_vect b) {
    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}

t_vect normalize(t_vect vector) {
    double length = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    t_vect normalizedVector = {
        vector.x / length,
        vector.y / length,
        vector.z / length
    };
    return normalizedVector;
}

t_vect subtract(t_vect a, t_vect b) {
    t_vect result = {
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    };
    return result;
}

t_vect reflect(t_vect lightDir, t_vect normal) {
    double dotProduct = lightDir.x * normal.x + lightDir.y * normal.y + lightDir.z * normal.z;

    t_vect reflection = {
        2 * dotProduct * normal.x - lightDir.x,
        2 * dotProduct * normal.y - lightDir.y,
        2 * dotProduct * normal.z - lightDir.z
    };

    return normalize(reflection);
}


// -----------------------------------------------------------------------------


int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}
t_vect cross(t_vect forward, t_vect position) {
    t_vect result;
    result.x = forward.y * position.z - forward.z * position.y;
    result.y = forward.z * position.x - forward.x * position.z;
    result.z = forward.x * position.y - forward.y * position.x;
    return (result);
}

//------------------------------------ aqui estamos haciendo lo que nos dan --------
typedef struct s_cam{
    // Position of the camera in 3D space
    t_vect position;

    // Direction the camera is facing (look-at vector)
    t_vect direction;

    // Up vector of the camera
    t_vect up;

    // Field of view (FOV) in radians
    float fov;

    // Aspect ratio (width / height)
    float aspect_ratio;

    // Near and far clipping planes
    float near_clip;
    float far_clip;
} t_camera;

typedef struct {
    float m[16];
} t_atrix4x4;

// Function to create a perspective projection matrix
t_atrix4x4 perspective(float fov, float aspect, float near, float far) {
    float f = 1.0f / tan(fov * 0.5f);
    float rangeInv = 1.0f / (near - far);

    t_atrix4x4 result = 
    {
        f / aspect, 0.0f, 0.0f, 0.0f,
        0.0f, f, 0.0f, 0.0f,
        0.0f, 0.0f, (far + near) * rangeInv, -1.0f,
        0.0f, 0.0f, 2.0f * far * near * rangeInv, 0.0f
    };

    return (result);
}

    
int intersect_cylinder(const t_vect *origin, const t_vect *direction, const t_cylinder *cylinder, double *t) {
    // Implementation of intersect_cylinder function (from previous code)
    // ...
    double a = direction->x * direction->x + direction->z * direction->z;
    double b = 2.0 * (origin->x * direction->x + origin->z * direction->z);
    double c = origin->x * origin->x + origin->z * origin->z - cylinder->radius * cylinder->radius;

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        // Calculate the two possible intersection points
        double t1 = (-b - sqrt(discriminant)) / (2 * a);
        double t2 = (-b + sqrt(discriminant)) / (2 * a);

        // Check if either intersection point is within the height bounds of the cylinder
        double y1 = origin->y + t1 * direction->y;
        double y2 = origin->y + t2 * direction->y;

        if ((y1 >= cylinder->center.y && y1 <= cylinder->center.y + cylinder->height) || (y2 >= cylinder->center.y && y2 <= cylinder->center.y + cylinder->height)) {
            // At least one intersection point is within the cylinder's height bounds
            // Choose the closer intersection point
            if (t1 < t2 && t1 >= 0) {
                *t = t1;
            } else if (t2 >= 0) {
                *t = t2;
            } else {
                return 0; // Both intersection points are behind the ray's origin
            }

            return 1; // Intersection found
        }
    }

    return 0; // No intersection


}

int intersect_sphere(const t_vect *origin, const t_vect *direction, const t_sphere* sphere, double* t) {
    t_vect oc = subtract(*origin, sphere->center);
    float a = dotProduct(*direction, *direction);
    float b = 2.0f * dotProduct(oc, *direction);
    float c = dotProduct(oc, oc) - (sphere->radius * sphere->radius);
    float discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        // Calculate the two solutions for t
        float t1 = (-b - sqrt(discriminant)) / (2.0f * a);
        float t2 = (-b + sqrt(discriminant)) / (2.0f * a);

        // Check if either solution is positive
        if (t1 >= 0 || t2 >= 0) {
            // Choose the smallest positive t
            if (t1 >= 0 && t2 >= 0) {
                *t = (t1 < t2) ? t1 : t2;
            } else if (t1 >= 0) {
                *t = t1;
            } else {
                *t = t2;
            }
			*t = t2;
            return 1;
        }
    }
    return 0;
}

void render(void* param)
{
    
    t_vect camera;
    t_vect  ray_o;
    t_vect ray_d;
    ray_o.x = 0.0;
    ray_o.y= 0.0;
    ray_o.z= 4.0;
    

    double r = 0.5f; // radius of the sphere
    double a;
    double b;
    double c;
    int red =0;
	double t4;

    ray_d.z = -1.0;
    double des;
    double t1;
    double t0;
    t_vect hit_pos;
    t_vect scaled_direction;
    t_vect norm;
    t_vect light;
    light.x = 1;
    light.y = 3;
    light.z = -2;
    double tc;
	t_sphere sphere = {{0.0, 0.0, 0.0}, 0.5};
    t_cylinder cylinder = {{1.0, 1.0, 1.0}, 0.5, 1.0};
    light =normalize(light);
    int flag = 0;
    int blue =0xFA;
    int green =0 ;
    float ambien = 0.2; // ambient light when you have this you multipley by 255 * 0.2 in each channel rgb (180,0,0)
	float fov = 90 *  M_PI / 180.0f; // here is the angle of the camera
	float imageaspectratio = (float)WIDTH / (float)HEIGHT; // assuming width > height
	for(int y = 0; y < HEIGHT; y++)
	{
        int blue =0xFA;
		for(int x = 0; x < WIDTH; x++) 
		{
            double u = ((double)x / (double)WIDTH - 0.5) * imageaspectratio * tan(fov / 2.0);
            double v = (0.5 - (double)y / (double)HEIGHT) * tan(fov / 2.0);
            ray_d.x = u;
			ray_d.y = v;
			ray_d.z = -1;
			ray_d = normalize(ray_d); // it's a direction so don't forget to normalize
            a = dotProduct(ray_d, ray_d);//ray_d.x * ray_d.x + ray_d.y * ray_d.y + ray_o.z * ray_o.z;
            //b = 2.0 * (dotProduct(ray_d, ray_o));//2.0 * ray_d.x * ray_o.x + 2.0 * ray_d.y * ray_o.y + 2.0 * ray_d.z * ray_o.z;
            //c = (dotProduct(ray_o, ray_o)) - (r * r);
            b = 2.0 * (dotProduct(ray_d, origen));
            c = (dotProduct(origen, origen)) - (r * r);
            des = (b * b) - (4.0 * (a * c));
            if (intersect_cylinder(&origen, &ray_d, &cylinder, &tc))
            {
				scaled_direction.x = ray_d.x * tc;
                scaled_direction.y =ray_d.y * tc;
                scaled_direction.z = ray_d.z * tc;
                // hit_pos.x = ray_o.x + scaled_direction.x;
                // hit_pos.y = ray_o.y + scaled_direction.y;
                // hit_pos.z = ray_o.z + scaled_direction.z;
                hit_pos.x = origen.x + scaled_direction.x;
                hit_pos.y = origen.y + scaled_direction.y;
                hit_pos.z = origen.z + scaled_direction.z;
                norm =normalize(hit_pos);
               
                double d1 =fmax((dotProduct(norm, (light))), 0.00f);
                
                green = (int)(0.7* (255 * d1)) + (int)((0.2 * 255));// make something 0  to 1 multiple  by 2551 I added the ambient // later we consider what is the color of the  this will grow with multiple by color of our object
                if(green > 255)
                    green =255;
            }else 
                green =0;
			if(intersect_sphere(&origen, &ray_d, &sphere, &t4))
			{
				scaled_direction.x = ray_d.x * t4;
                scaled_direction.y =ray_d.y * t4;
                scaled_direction.z = ray_d.z * t4;
                // hit_pos.x = ray_o.x + scaled_direction.x;
                // hit_pos.y = ray_o.y + scaled_direction.y;
                // hit_pos.z = ray_o.z + scaled_direction.z;
                hit_pos.x = origen.x + scaled_direction.x;
                hit_pos.y = origen.y + scaled_direction.y;
                hit_pos.z = origen.z + scaled_direction.z;
                norm =normalize(hit_pos);
               
                double d2 =fmax((dotProduct(norm, (light))), 0.00f);
                
                blue = (int)(0.7* (255 * d2)) + (int)((0.2 * 255));// make something 0  to 1 multiple  by 2551 I added the ambient // later we consider what is the color of the  this will grow with multiple by color of our object
                if(blue > 255)
                blue =255;
           
				
				
			}else
				blue =0;
            if(des < 0.0f)
            {
                red= 0;
                blue= 0;
                //green = 0;

            }else {
                t0 = (-b + sqrt(des)) / (2.0f * a); // cahnge his
                t1 = (-b - sqrt(des)) / (2.0f * a);
                scaled_direction.x = ray_d.x * t0;
                scaled_direction.y =ray_d.y * t0;
                scaled_direction.z = ray_d.z * t0;
                // hit_pos.x = ray_o.x + scaled_direction.x;
                // hit_pos.y = ray_o.y + scaled_direction.y;
                // hit_pos.z = ray_o.z + scaled_direction.z;
                hit_pos.x = origen.x + scaled_direction.x;
                hit_pos.y = origen.y + scaled_direction.y;
                hit_pos.z = origen.z + scaled_direction.z;
                norm =normalize(hit_pos);
               
                double d =fmax((dotProduct(norm, (light))), 0.00f);
                
                // red = (int)(0.7* (255 * d)) + (int)((0.2 * 255));// make something 0  to 1 multiple  by 2551 I added the ambient // later we consider what is the color of the  this will grow with multiple by color of our object
                // if(red > 255)
                //     red =255;
           
            }
            
		    uint32_t color = ft_pixel(
				red, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
				green,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
				blue, // B
				0xFF
				);
		    mlx_put_pixel(image, x, y, color);
		}
	}

}
void ft_hook(void* param) /// this move the camera now 
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		//image->instances[0].y -= 5;
        origen.y += 0.01;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		origen.y -= 0.01;
        //image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		origen.x += 0.01;
        //image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		origen.x -= 0.01;
        //image->instances[0].x += 5;
    if (mlx_is_key_down(mlx, MLX_KEY_Q))
		origen.z += 0.01;
        //image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_E))
		origen.z -= 0.01;
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	//mlx_t* mlx;

	// Gotta error check this stuff
origen.x = 0.0;
origen.y = 0.0;
origen.z = 6.0;
    t_camera came;
    came.far_clip =100;
    came.near_clip = 1;
    came.fov = 45 *  M_PI / 180.0f;
    came.aspect_ratio =4/3;
    
    
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "Circle", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, WIDTH, HEIGHT)))
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (mlx_image_to_window(mlx, image, 0, 0) == -1)
	{
		mlx_close_window(mlx);
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	mlx_loop_hook(mlx, render, mlx);
    //mlx_loop_hook(mlx, camera1, came);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
} 

// you can run with this 
//cc test3.5.c MLX42/build/libmlx42.a -IMLX42/include -ldl -lglfw -L"/Users/djames/.brew/Cellar/glfw/3.3.8/lib/"

