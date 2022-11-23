#include <stddef.h>
#include <math.h>

#include <miniRT.h>

// Hardcoded 32 bits per pixel, little-endian
// To use arbitrary bpp:
// char *dst;
// dst = im->addr + (y * im->line_length + x * (im->bits_per_pixel / 8));
// *(unsigned int*)dst = color;
void	img_put_pixel(t_imgdata *im, int x, int y, t_color color)
{
	t_color	*dst;

	// TODO how fast is pointer dereferecing for every pixel?
	dst = (t_color *)im->addr + (y * im->width + x);
	*dst = color;
}

// Hardcoded 32 bits per pixel, little-endian
t_color	rgb(float r, float g, float b)
{
	t_color	color;

	color = 0;
	color += r * 255.0f;
	color <<= 8;
	color += g * 255.0f;
	color <<= 8;
	color += b * 255.0f;
	return (color);
}

// Hardcoded 32 bits per pixel, little-endian
t_color	vec3_to_color(t_vec3 v)
{
	t_color	color;

	color = 0;
	color += v.x * 255.0f;
	// color += fmodf(v.x, 1.0f) * 255.0f;
	color <<= 8;
	color += v.y * 255.0f;
	// color += fmodf(v.y, 1.0f) * 255.0f;
	color <<= 8;
	color += v.z * 255.0f;
	// color += fmodf(v.z, 1.0f) * 255.0f;
	return (color);
}

t_color	correct_gamma(t_vec3 color, float gamma)
{
	t_vec3	result;

	result.x = powf(color.x, 1.0f / gamma);
	result.y = powf(color.y, 1.0f / gamma);
	result.z = powf(color.z, 1.0f / gamma);
	return (vec3_to_color(result));
}
