#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <miniRT.h>
#include <mlx.h>

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
			img_put_pixel(im, x, im->height - y - 1, 0x00ffff);
			x++;
		}
		x = 0;
		y++;
	}
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
	// mlx_hook(a->win, 17, (1L << 2), off, a);
	update_window(a);
	return (true);
}

int main(int argc, const char *argv[])
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
