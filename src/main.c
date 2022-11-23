#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <X11/X.h>

#include <miniRT.h>
#include <mlx.h>

#include <vector.h>

typedef struct s_sphere {
    t_vec3	center;
    float	radius;
}	t_sphere;


// bool ray_intersect_sphere(const t_vec3 *orig, const t_vec3 *dir, float *t0, t_sphere *s)
// {
// 	t_vec3 center = s->center;
// 	float radius = s->radius;

//     t_vec3 L = center - orig;
//     float tca = L*dir;
//     float d2 = L*L - tca*tca;
//     if (d2 > radius*radius) return false;
//     float thc = sqrtf(radius*radius - d2);
//     t0       = tca - thc;
//     float t1 = tca + thc;
//     if (t0 < 0) t0 = t1;
//     if (t0 < 0) return false;
//     return true;
// }

float	hit_plane(t_vec3 n, float h, const t_ray3 *ray)
{
	return (-(dot(ray->orig, n) + h) / dot(ray->dir, n));
}

float	hit_sphere(t_vec3 center, float radius, const t_ray3 *ray)
{
	t_vec3	oc;

	oc = v_sub(ray->orig, center);
	float b = dot(oc, ray->dir);
	float c = dot(oc, oc) - radius * radius;
	float h = b * b - c;
	if (h < 0)
		return (-1.0f);
	return -b - sqrtf(h);
	// float a = dot(ray->dir, ray->dir);
	// float b = 2.0f * dot(oc, ray->dir);
	// float c = dot(oc, oc) - radius * radius;

	// float discriminant = b*b - 4*a*c;
	// if (discriminant < 0)
	// 	return (-1.0f);
	// else
	// 	return (-b - sqrtf(discriminant)) / (2.0f * a);
}

t_color	cast(const t_ray3 *ray)
{
	t_vec3 center = vec3(0, 0, 3.0f);
	t_vec3 light = vec3(1, 1, 1);

	float s = hit_sphere(center, 1.0f, ray);
	if (s > 0)
	{
		t_vec3 hit = at(ray, s);
		t_vec3 n = normalize(v_sub(hit, center));
		// n.z = -n.z;
		// t_vec3 light_dir = normalize(v_sub(light, hit));
		t_vec3 light_dir = normalize(vec3(1, 1, -1));
		float illumination = clamp(dot(n, light_dir), 0.0f, 1.0f);
		return rgb(illumination, 0, 0);
		// t_vec3 color = v_mul(v_add(n, vec3(1, 1, 1)), 0.5f);
		// return vec3_to_color(color);
		// return correct_gamma(color, GAMMA);
	}

	s = hit_plane(vec3(0, 1, 0), 1, ray);
	if (s > 0)
	{
		t_vec3 hit = at(ray, s);
		t_vec3 n = normalize(v_sub(hit, center));
		// t_vec3 light_dir = normalize(v_sub(light, hit));

		t_vec3 light_dir = normalize(vec3(1, 1, -1));
		float illumination = clamp(dot(n, light_dir), 0.0f, 1.0f);
		return rgb(illumination, 0, 0);
	}

	t_vec3	white = vec3(1, 1, 1);
	t_vec3	blue = vec3(0.5, 0.7, 1);

	t_vec3	color = v_lerp(&white, &blue, (ray->dir.y + (VIEWPORT_H / 2)) / VIEWPORT_H);
	// printf("%f, %f, %f\n", color.x, color.y, color.z);
	// return rgb(2*fabsf(ray->dir.x), 2*fabsf(ray->dir.y), 0);
	return vec3_to_color(color);
}

t_color	get_pixel_color(const int x, const int y)
{
	t_ray3	ray;

	float ray_x = lerp(-VIEWPORT_W / 2, VIEWPORT_W / 2, (float) x / VIEW_W);
	float ray_y = lerp(-VIEWPORT_H / 2, VIEWPORT_H / 2, (float) (VIEW_H - y) / VIEW_H);

	ray.orig = vec3(0, 0, 0);
	// TODO why do I need to normalize it?
	ray.dir = normalize(vec3(ray_x, ray_y, FOCAL_LENGTH));
	return cast(&ray);
}

void	draw(t_imgdata *im)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < im->height)
	{
		while (x < im->width)
		{
			img_put_pixel(im, x, y,
				// rgb(x / (float) VIEW_W, y / (float) VIEW_H, 0));
				get_pixel_color(x, y));
			x++;
		}
		x = 0;
		y++;
	}
}

// For some reason mlx_destroy_display() leads to sigsegv in _XReadEvents()
int	quit(void)
{
	printf("Closing application\n");
	exit(EXIT_SUCCESS);
}

void	update_window(t_app *app)
{
	draw(app->img);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img_ptr, 0, 0);
}

bool	init_app(t_app *a)
{
	a->img->img_ptr = mlx_new_image(a->mlx, VIEW_W, VIEW_H);
	a->img->addr = mlx_get_data_addr(a->img->img_ptr, &a->img->bpp, \
		&a->img->line_len, &a->img->endian);
	a->img->width = VIEW_W;
	a->img->height = VIEW_H;
	// mlx_mouse_hook(a->win, mouse_hook, a);
	// mlx_key_hook(a->win, key_hook, a);
	mlx_hook(a->win, DestroyNotify, 0L, quit, a);
	update_window(a);
	return (true);
}

int	main(int argc, const char *argv[])
{
	void		*mlx;
	void		*win;
	t_imgdata	img;
	t_app		app;

	// if (!parse_arguments(argc, argv, &fractal))
	// {
	// 	printf(HELP_MESSAGE);
	// 	exit(EXIT_FAILURE);
	// }
	mlx = mlx_init();
	win = mlx_new_window(mlx, VIEW_W, VIEW_H, "miniRT");
	app.img = &img;
	// app.fractal = &fractal;
	app.mlx = mlx;
	app.win = win;
	if (init_app(&app))
		mlx_loop(mlx);
	return (EXIT_SUCCESS);
}
