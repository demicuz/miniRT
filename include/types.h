#ifndef TYPES_H
# define TYPES_H

typedef struct s_imgdata
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_imgdata;

typedef struct s_rtdata
{
	double	x;
	double	y;
	double	zoom;
	int		max_iter;
	int		fr_type;
	int		color_type;
	double	c_re;
	double	c_im;
}	t_rtdata;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
	// t_rtdata	*rtdata;
}	t_app;

typedef unsigned int	t_color;

# endif
