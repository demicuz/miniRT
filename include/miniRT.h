#ifndef MINIRT_H
# define MINIRT_H

# include "types.h"

# define VIEW_W 1400
# define VIEW_H 900
# define ASPECT 1.55555555

# define HELP_MESSAGE "Accepts one argument - file with the scene to render"

void	img_put_pixel(t_imgdata *im, int x, int y, t_color color);

# endif