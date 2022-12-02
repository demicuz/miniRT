#include <stdlib.h>
#include <stdbool.h>

#include <miniRT.h>

bool	parse_objects(t_app *app) {
	app->obj_count = 4;
	app->objects[0].type = SPHERE;
	app->objects[0].sphere = (t_sphere) {.pos = vec3(-1, 0, 5.0F), .radius = 1.0F, .color = vec3(1, 0, 0)};

	app->objects[1].type = SPHERE;
	app->objects[1].sphere = (t_sphere) {.pos = vec3(2, 0, 4.0F), .radius = 1.0F, .color = vec3(0, 1, 0)};

	app->objects[2].type = SPHERE;
	app->objects[2].sphere = (t_sphere) {.pos = vec3(-2, -0.5F, 5.0F), .radius = 1.0F, .color = vec3(0, 0, 1)};

	app->objects[3].type = PLANE;
	app->objects[3].plane = (t_plane) {.normal = vec3(0, 1, 0), .h = 1.0F, .color = vec3(0.9F, 0.9F, 0.9F)};

	app->light = (t_light) {.pos = vec3(1, 5, 1), .brightness = 1};
	return (true);
}
