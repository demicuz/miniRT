#include <stdlib.h>
#include <stdbool.h>

#include <miniRT.h>

bool	parse_objects(t_app *app) {
	app->obj_count = 5;
	app->objects[0].type = SPHERE;
	app->objects[0].color = vec3(1, 0, 0);
	app->objects[0].shininess = 30.0F;
	app->objects[0].sphere = (t_sphere) {.pos = vec3(-2.5F, 0, 6.0F), .radius = 1.0F, .shininess = 5.0F, .color = vec3(1, 0, 0)};

	app->objects[1].type = SPHERE;
	app->objects[1].sphere = (t_sphere) {.pos = vec3(0, 0, 6.0F), .radius = 1.0F, .shininess = 30.0F, .color = vec3(0, 1, 0)};

	app->objects[2].type = SPHERE;
	app->objects[2].sphere = (t_sphere) {.pos = vec3(2.5F, 0, 6.0F), .radius = 1.0F, .shininess = 60.0F, .color = vec3(0, 0, 1)};

	app->objects[3].type = SPHERE;
	app->objects[3].sphere = (t_sphere) {.pos = vec3(-1, 1, 2), .radius = .1F, .shininess = 30.0F, .color = vec3(1, 1, 1)};

	app->objects[4].type = PLANE;
	app->objects[4].plane = (t_plane) {.normal = vec3(0, 1, 0), .h = 1.0F, .color = vec3(0.8F, 0.8F, 0.8F)};

	app->light = (t_light) {.pos = vec3(-1, 1, 2), .brightness = 20, .color = vec3(.7F, .7F, .7F)};

	app->ambient_light = 2.1F;
	return (true);
}
