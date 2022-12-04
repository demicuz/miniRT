#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <X11/X.h>

#include <float.h>

#include <miniRT.h>
#include <mlx.h>

#include <vector.h>

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

float	hit_sphere(t_vec3 center, float radius, const t_ray3 *ray, bool *inside)
{
	t_vec3 OC = v_sub(center, ray->orig);

	*inside = false;
	if (dot(OC, OC) <= radius * radius)
	{
		*inside = true;
		return 1.0F;
	}
	float OH_len = dot(OC, ray->dir);
	if (OH_len < 0 && !*inside)
		return -1.0F;

	float CH_len_sq = dot(OC, OC) - OH_len * OH_len;
	if (CH_len_sq > radius * radius)
		return -1.0F;
	float XH_len_sq = radius * radius - CH_len_sq;

	if (!*inside)
		return (OH_len - sqrtf(XH_len_sq));
	return (OH_len + sqrtf(XH_len_sq));
}

float	hit_plane(t_vec3 n, float h, const t_ray3 *ray)
{
	return (-(dot(ray->orig, n) + h) / dot(ray->dir, n));
}

float	hit_plane_new(t_vec3 p, t_vec3 normal, const t_ray3 *ray)
{
	float	d;
	float	t;

	d = -dot(p, normal);
	t = -(d + dot(ray->orig, normal)) / dot(ray->dir, normal);
	return (t);
}

t_color	background(const t_ray3 *ray)
{
	t_vec3	white = vec3(1, 1, 1);
	t_vec3	blue = vec3(0.5F, 0.7F, 1);

	t_vec3	color = v_lerp(&white, &blue, (ray->dir.y + (VIEWPORT_H / 2)) / VIEWPORT_H);
	// return rgb(2*fabsf(ray->dir.x), 2*fabsf(ray->dir.y), 0);
	return vec3_to_color(color);
}

t_color	phong(t_vec3 N, t_vec3 V, t_light *light, float shininess)
{
	return 0x0;
}

t_color	render_sphere(const t_ray3 *ray, t_obj *obj, float dist, t_app *app)
{
	t_light *light = &app->light;

	t_vec3	hit             = at(ray, dist);
	t_vec3	n               = normalize(v_sub(hit, obj->pos)); // TODO sphere of 0 diameter
	t_vec3	light_dir       = v_sub(light->pos, hit);
	// t_vec3	light_dir       = vec3(-1, 1, -4); // Sunlight
	float	light_intensity = 1.0F / dot(light_dir, light_dir);

	light_dir = normalize(light_dir);
	if (obj->inside)
		n = vec3(-n.x, -n.y, -n.z);

	float lambertian = fmaxf(dot(n, light_dir), 0);
	t_vec3 ill_color = v_mulv(obj->color, light->color);

	// Ambient light
	t_vec3	ambient = v_mul(ill_color, app->ambient_light * light_intensity);

	// t_vec3 ambient;
	// if (lambertian > 0)
		// ambient = v_mul(ill_color, app->ambient_light * light_intensity);
	// else
		// ambient = vec3(0, 0, 0);

	// Diffuse light
	t_vec3 diffusion = v_mul(v_mul(ill_color, lambertian), light->brightness * light_intensity);

	// Specular reflection, Blinn-Phong
	t_vec3 H = normalize(v_sub(light_dir, ray->dir));
	float blinnTerm = fmaxf(dot(n, H), 0);
	float spec_factor = powf(blinnTerm, obj->shininess) * light_intensity * obj->shininess;
	t_vec3	specular = v_mul(light->color, spec_factor);

	t_vec3	final_color = vec3(0, 0, 0);
	final_color = v_add(ambient, final_color);
	final_color = v_add(diffusion, final_color);
	final_color = v_add(specular, final_color);


	final_color = v_divv(final_color, v_add(final_color, vec3(1, 1, 1)));
	// final_color = v_min(final_color, 1.0F);

	// return vec3_to_color(final_color);
	return correct_gamma(final_color, GAMMA);
	// n.z = -n.z;
	// t_vec3 color = v_mul(v_add(n, vec3(1, 1, 1)), 0.5F);
	// return vec3_to_color(color);
}

t_color	render_plane(const t_ray3 *ray, t_obj *obj, float dist, t_app *app)
{
	t_light *light = &app->light;

	t_vec3 hit = at(ray, dist);
	t_vec3 light_dir = normalize(v_sub(light->pos, hit));
	float illumination = fmaxf(dot(obj->plane.normal, light_dir), 0.0F);
	t_vec3 final_color = v_mul(obj->color, illumination);

	return vec3_to_color(final_color);
}

t_obj *cast(const t_ray3 *ray, t_obj objects[], int obj_count, float *dist)
{
	int		i;
	float	current_dist;
	t_obj	*hit;

	hit = NULL;
	i = 0;
	current_dist = 0;
	while (i < obj_count)
	{
		if (objects[i].type == SPHERE)
			// TODO looks ugly
			current_dist = hit_sphere(objects[i].pos, objects[i].sphere.radius, ray, &objects[i].inside);
		else if (objects[i].type == PLANE)
			// current_dist = hit_plane(objects[i].plane.normal, 1, ray);
			current_dist = hit_plane_new(objects[i].pos, objects[i].plane.normal, ray);
		if (current_dist > 0.0F && current_dist < *dist)
		{
			*dist = current_dist;
			hit = &objects[i];
		}
		i++;
	}
	return hit;
}

t_color	get_pixel_color(int x, int y, t_app *app)
{
	t_ray3	ray;

	float ray_x = lerp(-VIEWPORT_W / 2, VIEWPORT_W / 2, (float) x / VIEW_W);
	float ray_y = lerp(-VIEWPORT_H / 2, VIEWPORT_H / 2, (float) (VIEW_H - y) / VIEW_H);

	ray.orig = vec3(0, 0, 0);
	// TODO Do I really need to normalize it?
	ray.dir = normalize(vec3(ray_x, ray_y, FOCAL_LENGTH));

	float dist = FLT_MAX;
	t_obj *hit_obj = cast(&ray, app->objects, app->obj_count, &dist);

	if (!hit_obj)
		return background(&ray);
	if (hit_obj->type == SPHERE)
		return render_sphere(&ray, hit_obj, dist, app);
	if (hit_obj->type == PLANE)
		return render_plane(&ray, hit_obj, dist, app);
	puts("object not implemented!");
	exit(1);
}

void	draw(t_app *app)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (y < app->img->height)
	{
		while (x < app->img->width)
		{
			img_put_pixel(app->img, x, y,
				// rgb(x / (float) VIEW_W, y / (float) VIEW_H, 0));
				get_pixel_color(x, y, app));
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
	draw(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img->img_ptr, 0, 0);
}

bool	init_app(t_app *a)
{
	if (!parse_objects(a))
		return false;
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

int loop(t_app *app)
{
	// puts("Loopin");
	update_window(app);
	usleep(500000); // TODO usleep is not allowed by the subject
	return (0);
}

int	main(int argc, const char *argv[])
{
	void		*mlx;
	void		*win;
	t_imgdata	img;
	t_app		app;

	// srand(time(NULL));

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
	{
		// mlx_loop_hook(mlx, &loop, &app);
		mlx_loop(mlx);
	}
	return (EXIT_SUCCESS);
}
