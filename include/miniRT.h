#ifndef MINIRT_H
# define MINIRT_H

# include "types.h"
# include "x_events.h"

#include <stdbool.h>

# define VIEW_W 700
# define VIEW_H 450
# define ASPECT (float) VIEW_W / VIEW_H

// Camera settings, TODO the camera can be positioned
// # define FOV 30
# define FOCAL_LENGTH 1
# define VIEWPORT_H 1.0f
# define VIEWPORT_W VIEWPORT_H * ASPECT

# define GAMMA 2.2f

# define HELP_MESSAGE "Accepts one argument - file with the scene to render\n"

// graphics_utils
void	img_put_pixel(t_imgdata *im, int x, int y, t_color color);
t_color	rgb(float r, float g, float b);
t_color	vec3_to_color(t_vec3 v);
t_color	correct_gamma(t_vec3 color, float gamma);

// math_utils
float	lerp(float a, float b, float t);
float	clamp(float x, float lower, float upper);

// parser
bool	parse_objects(t_app *app);

# endif