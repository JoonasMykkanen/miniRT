# miniRT
MiniRT is a simple raytracer designed to teach students about raytracing and general computer graphics. It handles basic shapes like spheres, planes, and cylinders. For lighting, it uses ambient and spotlights, and it also computes specular lighting, shadows, and reflections. The original project didn't require multithreading, but with the addition of multiple lights, shadows, and reflections, it became quite slow as a single-threaded application. To improve performance, I implemented a thread pool.

### Usage (OSX)
#### Clone the repository
```
git clone https://github.com/joonasmykkanen/minirt
```
#### Install graphics library
```
brew install glfw
```
#### run make bonus to get full version.
```
make bonus
```
#### Run ./miniRT or ./miniRT_bonus with some map from evaluation folder
```
./miniRT evaluation/sphere.rt
```

![Logo](https://github.com/joonasmykkanen/minirt/blob/main/pictures/pillars.png)
![Logo](https://github.com/joonasmykkanen/minirt/blob/main/pictures/reflect.png)
![Logo](https://github.com/joonasmykkanen/minirt/blob/main/pictures/android.png)
![Logo](https://github.com/joonasmykkanen/minirt/blob/main/pictures/h2o.png)
![Logo](https://github.com/joonasmykkanen/minirt/blob/main/pictures/light.png)
![Logo](https://github.com/joonasmykkanen/minirt/blob/main/pictures/multi.png)
![Logo](https://github.com/joonasmykkanen/minirt/blob/main/pictures/smiley.png)
