/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test11.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: djames <djames@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 11:23:35 by djames            #+#    #+#             */
/*   Updated: 2023/09/13 13:56:00 by djames           ###   ########.fr       */
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
    t_vect albedo;
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
void recalculate_projection(t_camera cam)
{
    
}
void camera1(void* param)
{
	t_camera* cam = param;
    t_vect forward;
    t_vect delta;
    t_vect right;
    t_vect up_drec;
    int moved = 0;
    

    delta.x=0;
    delta.y = 0;
    up_drec.x = 0;
    up_drec.y = 1;
    up_drec.z = 0;
    cam->direction.x = 0;
    cam->direction.y = 0;
    cam->direction.z = -1;
    cam->position.x= 0;
    cam->position.y= 0;
    cam->position.z= 6;
    right = cross(cam->direction , up_drec);
    float speed = 5.0;

    if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
    if (mlx_is_key_down(mlx, MLX_KEY_UP))
    {
		cam->position.z += 5;
        delta.y =1;
        moved =1;
    }
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		image->instances[0].x += 5;
    // Rotation
	if (delta.x != 0.0f || delta.y != 0.0f)
	{
		float pitchDelta = delta.y * 0.3;
		float yawDelta = delta.x * 0.3;

		t_quaternion pitchRotation = { sin(pitchDelta / 2), 0.0f, 0.0f, cos(pitchDelta / 2) };
        t_quaternion yawRotation = { 0.0f, sin(yawDelta / 2), 0.0f, cos(yawDelta / 2) };

        // Combine the pitch and yaw rotations
        t_quaternion combinedRotation = normalize_quaternion(quaternion_cross(pitchRotation, yawRotation));

        // Define the forward direction vector
        //t_vect m_ForwardDirection = { 0.0f, 0.0f, -1.0f };

    // Rotate the forward direction using the combined rotation quaternion
        cam->direction = rotate_vector(cam->direction, combinedRotation);

		moved = true;
	}

	// if (moved)
	// {
	// 	RecalculateView();
	// 	RecalculateRayDirections();
	// }

}
    typedef struct s_cy {
    t_vect center;
    double radius;
    double height;
} t_cylinder;

    
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


// int intersect_sphere(const t_vect *origin, const t_vect *direction, const t_sphere *sphere, double *t) {
   
// 	double ocx = origin->x - sphere->center.x;
//     double ocy = origin->y - sphere->center.y;
//     double ocz = origin->z - sphere->center.z;

//     double a = direction->x * direction->x +
//                direction->y * direction->y +
//                direction->z * direction->z;

//     double b = 2.0 * (ocx * direction->x +
//                       ocy * direction->y +
//                       ocz * direction->z);

//     double c = ocx * ocx + ocy * ocy + ocz * ocz - sphere->radius * sphere->radius;

//     double discriminant = b * b - 4 * a * c;

//     if (discriminant > 0) {
//         double t1 = (-b - sqrt(discriminant)) / (2 * a);
//         double t2 = (-b + sqrt(discriminant)) / (2 * a);

//         if (t1 >= 0 || t2 >= 0) {
//             *t = (t1 < t2) ? t1 : t2;
//             return 1;
//         }
//     }

//     return 0;

// }
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

            origen.x = 
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

// -----------------------------------------------------------------------------
t_vect Vec_divide(const t_vect *v, float r) {
    t_vect result;
    result.x = v->x / r;
    result.y = v->y / r;
    result.z = v->z / r;
    return result;
}
void vec_divinplace(t_vect *v, float r) {
    v->x /= r;
    v->y /= r;
    v->z /= r;
}

t_vect vec_subtract(const t_vect *v1, const t_vect *v2) {
    t_vect result;
    result.x = v1->x - v2->x;
    result.y = v1->y - v2->y;
    result.z = v1->z - v2->z;
    return result;
}

t_vect vec_add(const t_vect *v1, const t_vect *v2) {
    t_vect result;
    result.x = v1->x + v2->x;
    result.y = v1->y + v2->y;
    result.z = v1->z + v2->z;
    return result;
}
t_vect vec_multis(const t_vect *v, float r) {
    t_vect result;
    result.x = v->x * r;
    result.y = v->y * r;
    result.z = v->z * r;
    return result;
}
// class ray {
//   public:
//     ray() {}

//     ray(const point3& origin, const vec3& direction) : orig(origin), dir(direction) {}

//     point3 origin() const  { return orig; }
//     vec3 direction() const { return dir; }

//     point3 at(double t) const {
//         return orig + t*dir;
//     }

//   private:
//     point3 orig;
//     vec3 dir;
// };

typedef struct s_r{
    t_vect orig;
    t_vect dir;
} t_ray;

// ray ray_create() {
//     ray r;
//     r.orig = point3_create(0, 0, 0);
//     r.dir = vec3_create(0, 0, 0);
//     return r;
// }

int intersectRay_cylinder(t_vect rayOrigin, t_vect rayDirection,
                          t_vect cylinderCenter, t_vect cylinderAxis,
                          double cylinderRadius, double cylinderHeight,
                          double* t1, double* t2);
t_ray ray_create(const t_vect origin, const t_vect direction) {
    t_ray r;
    r.orig = origin;
    r.dir = direction;
    return r;
}

t_vect ray_origin(const t_ray r) {
    return r.orig;
}

t_vect ray_direction(const t_ray r) {
    return r.dir;
}

t_vect ray_at(const t_ray r, double t) {
	t_vect help;
	help = vec_multis(&(r.dir), (float)t);
    return vec_add(&r.orig, &help);
}

typedef struct s_c{
    double r, g, b;
} t_color;
t_vect make_color(double r, double g, double b) {
    return (t_vect){r, g, b};
}

// Function to add two colors
t_vect add_color(const t_vect c1, const t_vect c2) {
    return (t_vect){c1.x + c2.x, c1.y + c2.y, c1.z + c2.z};
}
double hit_sphere(const t_vect center, double radius, const t_ray r);
t_vect ray_color(const t_ray r) {
    t_vect unit_direction = normalize(r.dir);
    double a = 0.5 * (unit_direction.y + 1.0);
    t_vect white;// = make_color(1.0, 1.0, 1.0);
    t_vect blue;// = make_color(0.5, 0.7, 1.0);
    t_vect help;
    t_cylinder cylinder = {{1.0, 1.0, 1.0}, 0.5, 1.0};
    t_vect n;
    help.x =0;
    help.y =0;
    help.z =0;
    double t = hit_sphere(help, 0.5, r);
    if (t > 0.0) {
        n = ray_at(r, t);
        n = vec_subtract(&n, &help);
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
	white =  vec_multis(&white, (float)(1.0 - a));
	blue =  vec_multis(&blue, (float)(a));
    return add_color(white, blue);
}
double lengthSquared(t_vect v) {
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

// Function to calculate the length (magnitude) of a 3D vector given its components
double length(t_vect v) {
    return sqrt(lengthSquared(v));
}
double hit_sphere(const t_vect center, double radius, const t_ray r) {
    t_vect oc = subtract(r.orig, center);
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

// typedef struct s_r{
//     t_vect orig;
//     t_vect dir;
// } t_ray;

typedef struct s_material
{
	t_vect albedo;
	float roughness ;
	float metallic ;
	t_vect emissionColor;
	float emissionPower;

	///t_vect GetEmission() const { return EmissionColor * EmissionPower; }
}t_material;

typedef struct s_ecena
{
	t_sphere *spheres;
	//std::vector<Material> Materials;
}t_scene;
t_vect lookfrom;// = point3(0,0,-1);  // Point camera is looking from
// lookfrom.x = 0;
// lookfrom.y =0;
// lookfrom.z = -3;
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
void ft_test(void* param)
{
	t_vect camerac;
    double fov  = 80 * M_PI / 180.0f;
    double h = tan((fov / 2));
	camerac.x =-0;
	camerac.y  =0;
	camerac.z =1;
	float fl=1;
	t_vect u;
	t_vect ray_d;
	t_vect v;
	t_vect z;
	t_vect up_left;
	t_vect help;
	t_vect help1;
	t_vect pixel;
	t_vect center;
	t_vect pixu;
	t_vect pixv; 
    t_vect lookat;//   = point3(0,0,0);   // Point camera is looking at
    t_vect   vup;//      = vec3(0,1,0);
    t_vect u1;
    t_vect v1;
    t_vect  w1;
    
    lookat.x =0;
    lookat.y =0;
    lookat.z =0;
    vup.x = 0;
    vup.y = 1;
    vup.z = 0;
    t_vect w;
    t_vect focal;
    double f_len;
    camerac= lookfrom; 
    
    focal = vec_subtract(&lookfrom, &lookat);
    f_len = length(focal);
	double viewport_height = 2.0 * h * f_len;
	double viewport_width = viewport_height * ((double)(WIDTH)/(double)HEIGHT);
    w1 = normalize(focal);
    u1 = cross(vup,w1);
    u1 = normalize(u1);
    v1 = cross(w1, u1);
	z.x=0;
	z.y =0;
	z.z = fl;
	// u.x = viewport_width;
	// u.y = 0;
	// u.z =0;
    u = vec_multis(&u1, viewport_width);
	// v.x =0;
	// v.y = -viewport_height;
	// v.z =0;
    v = vec_multis(&v1, -viewport_height);
	pixu =Vec_divide(&u, (float)WIDTH);
	pixv = Vec_divide(&v, (float)HEIGHT);
    help = vec_multis(&w1, f_len);
    help1 = vec_subtract(&camerac, &help);

    
	//help1 = vec_subtract(&camerac, &z);
	help = Vec_divide(&u, 2.0);
	up_left = vec_subtract(&help1, &help);
	help = (Vec_divide(&v, 2.0));
	up_left = vec_subtract(&up_left, &help);
	help = vec_add(&pixu, &pixv);
	help1 = vec_multis(&help, 0.5); 
	pixel = vec_add(&up_left, &help1);
	t_ray r;
	t_vect centersph;
	centersph.x =0.5;
	centersph.y =0;
	centersph.z=-1;
	double radius =0.5;
	uint32_t color= ft_pixel(
				0x00, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
				0x00,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
				0x00, // B
				0xFF
				);
    double tc;
    t_cylinder cylinder = {{0, 0, 0.0}, 0.5, 2.0};
    t_vect cylinderAxis;
    cylinderAxis.x=  0;
    cylinderAxis.y= 0;
    cylinderAxis.z=0;
    t_vect cylinderCenter;
    cylinderCenter.x= 0;
    cylinderCenter.y=0;
    cylinderCenter.z =1;
    double cylinderRadius =0.5;
    double cylinderHeight =1;
    double *t1, *t2;
    t_vect scaled_direction;
    t_vect hit_pos;
    t_vect norm;
    int blue =0;
    t_vect light;
    light.x = 1;
    light.y = 5;
    light.z = -2;
    t_sphere sphe[3];
    create_sphere(sphe);
    t_sphere aux;
    double t66 = 5000000000000.0;
    double hit;
    int a2;
    int green;
    int red;
    //printf("esto es %f/n:", sphe[0].center.x);
	for (int j = 0; j < HEIGHT; ++j) {
        for (int i = 0; i < WIDTH; ++i) {
			help = vec_multis(&pixu, (float)i);
			help1 = vec_multis(&pixv, (float)j);
			center = vec_add(&help, &help1);
			center = vec_add(&center, &pixel);
			ray_d = vec_subtract(&center, &camerac);
			r= ray_create(lookfrom, ray_d); //chance 
            t66 = 5000000000000.0;
            double t55 =hit_sphere(centersph, radius, r);
            // for(int a = 0; a < 3; a++)
            // {
            //     hit = hit_sphere(sphe[a].center, 0.5, r);
            //     if((hit < t66) && (hit > 0))
            //     {
            //         t66 = hit;
            //         aux = sphe[a];
            //         a2 =a;
            //     }
                
                
            // }
            // if(t66 != 5000000000000.0){
            //     scaled_direction = vec_multis(&ray_d, t66);
			// 	// scaled_direction.x = ray_d.x * t55;
            //     // scaled_direction.y =ray_d.y * t55;
            //     // scaled_direction.z = ray_d.z * t55;
            //     hit_pos = vec_subtract(&r.orig, &sphe[a2].center);
            //     hit_pos = vec_add(&hit_pos, &scaled_direction);
            //     // hit_pos.x = ray_o.x + scaled_direction.x;
            //     // hit_pos.y = ray_o.y + scaled_direction.y;
            //     // hit_pos.z = ray_o.z + scaled_direction.z;
            //     // hit_pos.x = r.orig.x  + scaled_direction.x;
            //     // hit_pos.y = origen.y + scaled_direction.y;
            //     // hit_pos.z = origen.z + scaled_direction.z;
            //     norm =normalize(hit_pos);
               
            //     double d2 =fmax((dotProduct(norm, (light))), 0.00f);
                
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
			t_vect pixel_color = ray_color(r);
			
			color = ft_pixel(
				(int)(pixel_color.x * 255), //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
				(int)(pixel_color.y * 255),//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
				(int)(pixel_color.z *255), // B
				0xFF
				);
			//}
            // if(intersectRay_cylinder(r.orig, r.dir,
            //               cylinderCenter, cylinderAxis,
            //               cylinderRadius,  cylinderHeight,
            //               t1, t2)){
            //     color = ft_pixel(
			// 	0x00, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
			// 	255,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
			// 	0x00, // B
			// 	0xFF
			// 	);
            // }
            // if (intersect_cylinder(&origen, &ray_d, &cylinder, &tc))
            // {
            //     color = ft_pixel(
			// 	0x00, //((int)(255 * x1)), // R // this we need to do all for us color in float we will do it in a bt
			// 	255,//(int)(255 * y1), // G uv(0.1) reverse the coordinate  // color entre 0  y 1
			// 	0x00, // B
			// 	0xFF
			// 	);
                
            // }
		    mlx_put_pixel(image, i, j, color);
			
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
        lookfrom.y += 0.1;
	if (mlx_is_key_down(mlx, MLX_KEY_DOWN))
		lookfrom.y -= 0.1;
        //image->instances[0].y += 5;
	if (mlx_is_key_down(mlx, MLX_KEY_LEFT))
		lookfrom.x += 0.1;
        //image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_RIGHT))
		lookfrom.x -= 0.1;
        //image->instances[0].x += 5;
    if (mlx_is_key_down(mlx, MLX_KEY_Q))
		lookfrom.z += 0.1;
        //image->instances[0].x -= 5;
	if (mlx_is_key_down(mlx, MLX_KEY_E))
		lookfrom.z -= 0.1;
}


// focal_length = 1.0;
//     auto viewport_height = 2.0;
//     auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);
	
//  auto viewport_u = vec3(viewport_width, 0, 0);
//     auto viewport_v = vec3(0, -viewport_height, 0);

//     // Calculate the horizontal and vertical delta vectors from pixel to pixel.
//     auto pixel_delta_u = viewport_u / image_width;
//     auto pixel_delta_v = viewport_v / image_height;

//     // Calculate the location of the upper left pixel.
//     auto viewport_upper_left = camera_center
//                              - vec3(0, 0, focal_length) - viewport_u/2 - viewport_v/2;
//     auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

//     // Render

//     std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

//     for (int j = 0; j < image_height; ++j) {
//         std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
//         for (int i = 0; i < image_width; ++i) {
//             auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
//             auto ray_direction = pixel_center - camera_center;
//             ray r(camera_center, ray_direction);

//             color pixel_color = ray_color(r);
//             write_color(std::cout, pixel_color);
//         }
//     }

//     std::clog << "\rDone.                 \n";
// }


int32_t main(int32_t argc, const char* argv[])
{
	//mlx_t* mlx;

	// Gotta error check this stuff
origen.x = -2.0;
origen.y = 2.0;
origen.z = 4.0;
lookfrom.x = 0;
lookfrom.y =0;
lookfrom.z = 3;
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
	mlx_loop_hook(mlx, ft_test, mlx);
    //mlx_loop_hook(mlx, camera1, came);
	mlx_loop_hook(mlx, ft_hook, mlx);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
} 

// you can run with this 
//cc test3.5.c MLX42/build/libmlx42.a -IMLX42/include -ldl -lglfw -L"/Users/djames/.brew/Cellar/glfw/3.3.8/lib/"









// Function to calculate the intersection between a ray and a cylinder
int intersectRay_cylinder(t_vect rayOrigin, t_vect rayDirection,
                          t_vect cylinderCenter, t_vect cylinderAxis,
                          double cylinderRadius, double cylinderHeight,
                          double* t1, double* t2) {
    // Calculate vector from the ray origin to the cylinder center
    t_vect oc = {rayOrigin.x - cylinderCenter.x, rayOrigin.y - cylinderCenter.y, rayOrigin.z - cylinderCenter.z};

    // Calculate coefficients for the quadratic equation
    double a = lengthSquared(rayDirection) - pow(dotProduct(rayDirection, cylinderAxis), 2);
    double b = 2.0 * (dotProduct(oc, rayDirection) - dotProduct(rayDirection, cylinderAxis) * dotProduct(oc, cylinderAxis));
    double c = lengthSquared(oc) - pow(dotProduct(oc, cylinderAxis), 2) - pow(cylinderRadius, 2);

    // Calculate the discriminant
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        // No intersection
        *t1 = -1;
        *t2 = -1;
        return 0;
    } else {
        // Compute the two intersection points (t-values)
        *t1 = (-b - sqrt(discriminant)) / (2 * a);
        *t2 = (-b + sqrt(discriminant)) / (2 * a);

        // Check if the intersections are within the cylinder height
        double t_min = fmin(*t1, *t2);
        double t_max = fmax(*t1, *t2);

        if (t_min < 0) {
            t_min = t_max;
        }

        if (t_min < 0 || t_min > cylinderHeight) {
            // No intersection within the cylinder height
            *t1 = -1;
            *t2 = -1;
            return 0;
        }

        return 1; // Intersection detected
    }
}

// int main() {
//     // Ray parameters
//     Vector3D rayOrigin = {14.2, 21.42, 10.0};
//     Vector3D rayDirection = {0.0, 0.0, 255.0}; // Assuming the direction is normalized

//     // Cylinder parameters
//     Vector3D cylinderCenter = {50.0, 0.0, 20.6};
//     Vector3D cylinderAxis = {0.0, 0.0, 1.0};
//     double cylinderRadius = 14.2;
//     double cylinderHeight = 10.0;

//     double t1, t2;
    
//     int intersection = intersectRayCylinder(rayOrigin, rayDirection, cylinderCenter, cylinderAxis, cylinderRadius, cylinderHeight, &t1, &t2);

//     if (intersection) {
//         printf("Ray intersects the cylinder.\n");
//         printf("Intersection points: t1 = %.2lf, t2 = %.2lf\n", t1, t2);
//     } else {
//         printf("Ray does not intersect the cylinder.\n");
//     }

//     return 0;
// }
