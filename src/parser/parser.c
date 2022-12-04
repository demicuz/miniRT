#include <stdlib.h>
#include <stdbool.h>

#include <miniRT.h>

bool	parse_objects(t_app *app) {
	app->obj_count = 5;
	t_obj *o;

	o            = &app->objects[0];
	o->type      = SPHERE;
	o->color     = vec3(1, 0, 0);
	o->shininess = 30.0F;
	o->pos       = vec3(-2.5F, 0, 6.0F);
	o->sphere    = (t_sphere) {.radius = 1.0F};

	o            = &app->objects[1];
	o->type      = SPHERE;
	o->color     = vec3(0, 1, 0);
	o->shininess = 20.0F;
	o->pos       = vec3(0, 0, 6.0F);
	o->sphere    = (t_sphere) {.radius = 1.0F};

	o            = &app->objects[2];
	o->type      = SPHERE;
	o->color     = vec3(0, 0, 1);
	o->shininess = 10.0F;
	o->pos       = vec3(2.5F, 0, 6.0F);
	o->sphere    = (t_sphere) {.radius = 1.0F};

	o            = &app->objects[3];
	o->type      = SPHERE;
	o->color     = vec3(1, 0, 0);
	o->shininess = 0.0F;
	o->pos       = vec3(-1, 1, 2);
	o->color     = vec3(0.8F, 0.8F, 0.8F);
	o->sphere    = (t_sphere) {.radius = .05F};

	o            = &app->objects[4];
	o->type      = PLANE;
	o->color     = vec3(0.8F, 0.8F, 0.8F);
	o->shininess = 0.0F;
	o->pos       = vec3(0, -1, 0);
	o->color     = vec3(0.8F, 0.8F, 0.8F);
	o->plane     = (t_plane) {.normal = vec3(0, 1, 0)};

	app->light = (t_light) {.pos = vec3(-1, 1, 2), .brightness = 20, .color = vec3(.7F, .7F, .7F)};

	app->ambient_light = 2.1F;
	return (true);
}
