#include <miniRT.h>

// Hardcoded 32 bits per pixel, little-endian
// To use arbitrary bpp:
// char *dst;
// dst = im->addr + (y * im->line_length + x * (im->bits_per_pixel / 8));
// *(unsigned int*)dst = color;
void	img_put_pixel(t_imgdata *im, int x, int y, t_color color)
{
	t_color	*dst;

	dst = (t_color *)im->addr + (y * im->width + x);
	*dst = color;
}
