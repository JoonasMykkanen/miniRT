#include <stdio.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42/include/MLX42/MLX42.h"



#define WIDTH 512
#define HEIGHT 512

static mlx_image_t* image;


typedef struct s_vec{
    double x;
    double y;
    double z;
} t_vect;

typedef struct {
    double r;
    double g;
    double b;
} Color;

typedef struct {
    t_vect position;
    Color color;
} Light;


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



Color calculatePhongShading(t_vect normal, t_vect lightDir, t_vect viewDir, Color lightColor) {
    Color ambient = {0.5, 0.5, 0.5}; // Ambient lighting component
    double diffuseStrength = fmax(0.0, dotProduct(normal, lightDir));
    Color diffuse = {diffuseStrength, diffuseStrength, diffuseStrength}; // Diffuse lighting component
    t_vect reflectionDir = reflect(lightDir, normal);
    double specularStrength = pow(fmax(0.0, dotProduct(viewDir, reflectionDir)), 32.0);
    Color specular = {specularStrength, specularStrength, specularStrength}; // Specular lighting component

    Color finalColor;
    finalColor.r = ambient.r + lightColor.r * (diffuse.r + specular.r);
    finalColor.g = ambient.g + lightColor.g * (diffuse.g + specular.g);
    finalColor.b = ambient.b + lightColor.b * (diffuse.b + specular.b);

    return finalColor;
}

int32_t convertColorToInt(Color color) {
    int32_t r = (int32_t)(color.r * 255.0); // Convert color components to 0-255 range
    int32_t g = (int32_t)(color.g * 255.0);
    int32_t b = (int32_t)(color.b * 255.0);

    // Pack the color components into a 32-bit integer
    int32_t packedColor = (r << 16) | (g << 8) | b;

    return packedColor;
}

t_vect transformToWorldCoordinates(t_vect vertex, t_vect cameraPos) {
    t_vect transformedVertex;

    // Translate the vertex based on the camera's position
    transformedVertex.x = vertex.x + cameraPos.x;
    transformedVertex.y = vertex.y + cameraPos.y;
    transformedVertex.z = vertex.z + cameraPos.z;

    return transformedVertex;
}

t_vect normals[] = {
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    {0.0, 0.0, 1.0},
    // ... more normals
};

// int numVertices = sizeof(vertices) / sizeof(vertices[0]);

// Light light = {
//     {10.0, 10.0, 10.0}, // Light position
//     {1.0, 1.0, 1.0}     // Light color
// };


// -----------------------------------------------------------------------------

int32_t ft_rgbconvert(int32_t r, int32_t g, int32_t b, int32_t a)
{
    uint8_t r1 = (uint8_t)(r * 255.0f);
	uint8_t g1 = (uint8_t)(g * 255.0f);
	uint8_t b1 = (uint8_t)(b * 255.0f);
	uint8_t a1 = (uint8_t)(a * 255.0f);
    return (r << 24 | g << 16 | b << 8 | a);
}
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}






void render(void* param)
{
    t_vect camera;
    t_vect  ray_o;
    t_vect ray_d;
    ray_o.x = 0.0;
    ray_o.y=0.0;
    ray_o.z= 3.0;

    double r = 0.5f; // radius of the sphere
    double a;
    double b;
    double c;
    double z1=0;
    int red =0;
    // (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
	// where
	// a = ray origin
	// b = ray direction
	// r = radius
	// t = hit distance
    // Quadratic forumula discriminant:
	// b^2 - 4ac

    ray_d.z = -1.0;
    double des;
    double t1;
    double t0;
    t_vect hit_pos;
    t_vect scaled_direction;
    t_vect norm;
    t_vect light;
    light.x = 1;
    light.y = 1;
    light.z = -1;
    light =normalize(light);
    int flag = 0;
    int blue =0xFA;
    int green =0 ;
    float ambien = 0.2; // ambient light when you have this you multipley by 255 * 0.2 in each channel rgb (180,0,0)

	
	for(int y = 0; y < 512; y++)//hight // change this
	{
        int blue =0xFA;
		for(int x = 0; x < 512; x++) //with 
		{
            //red=255;
            double x1 = (double)x / ((512));// use this 
            x1 = (2.0f * (double)x) / (512) - 1.0f;
            ray_d.x = x1;
            //     printf("esto es x %f\n", ray_d.x);
            double y1 = 1 - (double)y /(512);
            y1 = 1.0f - (2.0f * (double)y) / 512;
            ray_d.y = y1;


    //         int ray_intersects_sphere(Ray ray, Sphere sphere, float *t) {
    // Vector3 oc = {ray.origin.x - sphere.center.x, ray.origin.y - sphere.center.y, ray.origin.z - sphere.center.z};
    // float a = dot(ray.direction, ray.direction);
    // float b = 2.0f * dot(oc, ray.direction);
    // float c = dot(oc, oc) - sphere.radius * sphere.radius;
    // float discriminant = b * b - 4 * a * c;
            camera.x = ray_o.x - ray_d.x;
            camera.y = ray_o.y - ray_d.y;
            camera.z = ray_o.z - ray_d.z;
            a = dotProduct(ray_d, ray_d);//ray_d.x * ray_d.x + ray_d.y * ray_d.y + ray_o.z * ray_o.z;
            b = 2.0 * (dotProduct(ray_d, camera));//2.0 * ray_d.x * ray_o.x + 2.0 * ray_d.y * ray_o.y + 2.0 * ray_d.z * ray_o.z;
            c = (dotProduct(camera, camera)) - (r * r);
            des = (b * b) - (4.0 * (a * c));
            if(des < 0.0f)
            {
                red= 0;
                blue=0;
                green =0;

            }else {
                t0 = (-b + sqrt(des)) / (2.0f * a); // cahnge his
               //scaled_direction = [ray_d.x * t0, ray_d.y * t0, ray_d.z * t0];
                scaled_direction.x = ray_d.x * t0;
                scaled_direction.y =ray_d.y * t0;
                scaled_direction.z = ray_d.z * t0;
                //printf(" aqui estan : %f, %f , %f\n", scaled_direction.x, scaled_direction.y, scaled_direction.z);
                //hit_pos ={ray_o.x + scaled_direction.x, ray.origin.y + scaled_direction.y, ray.origin.z + scaled_direction.z};
                hit_pos.x = ray_o.x + scaled_direction.x;
                hit_pos.y = ray_o.y + scaled_direction.y;
                hit_pos.z = ray_o.z + scaled_direction.z;
                //normalize(hit_pos);
                norm =normalize(hit_pos);
                //printf(" aqui estan : %f, %f , %f\n", hit_pos.x, hit_pos.y, hit_pos.z);
                //red = ((int)((hit_pos.x * 255) * 0.5 + 0.5));
                // if(red < 0)
                // {
                //      red =  0;
                // }
                //     printf("rojo %d\n ", red);
                // green = (int)((hit_pos.y * 255) * 0.5 + 0.5);
                // if(green < 0)
                // {
                //     green =  0;
                // }
                // blue = ((int)((hit_pos.z * 255) * 0.5 + 0.5));
                // if(blue <= 0)
                // {
                //     blue =  abs(blue);
                // }
                // //green =255;
                double d =fmax((dotProduct(norm, (light))), 0.00f);
                //printf("%f\n", d);
                
                red = (int)(0.7* (255 * d)) + (int)((0.2 * 255));// make something 0  to 1 multiple  by 2551 I added the ambient // later we consider what is the color of the  this will grow with multiple by color of our object
                if(red > 255)
                    red =255;
                t1 = (-b - sqrt(des)) / (2.0f * a);
            // red =185;
            // blue=150;
            // green =255;
            //hit_pos.z = t1;
            }
            // if (y == 0)
                //printf("cordenadas  x= %f, y = %f\n", ray_d.x ,ray_d.y);
		    uint32_t color = ft_pixel(
				red, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
				0x00,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
				0x00, // B
				//interpo  // A
				0xFF
				);
		    mlx_put_pixel(image, x, y, color);
		}
	}

}
void ft_hook(void* param)
{
	mlx_t* mlx = param;

	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
	if (mlx_is_key_down(mlx, MLX_KEY_UP))
		image->instances[0].y -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
}

// -----------------------------------------------------------------------------

int32_t main(int32_t argc, const char* argv[])
{
	mlx_t* mlx;

	// Gotta error check this stuff
	if (!(mlx = mlx_init(WIDTH, HEIGHT, "Circle", true)))
	{
		puts(mlx_strerror(mlx_errno));
		return(EXIT_FAILURE);
	}
	if (!(image = mlx_new_image(mlx, 512, 512)))
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
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}

