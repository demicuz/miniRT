#ifndef TYPES_H
# define TYPES_H

# include <stdbool.h>

# include "vector.h"

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

// typedef struct s_rtdata
// {

// }	t_rtdata;

typedef unsigned int	t_color;

// typedef struct s_cam
// {
// 	t_vec3	pos;
// 	t_vec3	dir;
// }	t_cam;

typedef enum	e_obj_type {
	PLANE,
	SPHERE,
	CYLINDER
}	t_obj_type;

typedef struct	s_sphere
{
	float		radius;
}	t_sphere;

typedef struct	s_plane
{
	t_vec3		normal;
}	t_plane;

typedef struct	s_cylinder
{
	float	height;
	float	radius;
}	t_cylinder;

typedef struct	s_obj
{
	t_vec3		pos;
	t_vec3		color;
	union
	{
		t_sphere	sphere;
		t_plane		plane;
		t_cylinder	cylinder;
	};
	float		shininess;
	t_obj_type	type;
	bool		inside;
}	t_obj;

typedef struct	s_light
{
	t_vec3	pos;
	float	brightness;
	t_vec3	color;
}	t_light;

typedef struct s_app
{
	void		*mlx;
	void		*win;
	t_imgdata	*img;
	// t_rtdata	*rtdata;

	float		ambient_light;
	t_light		light;
	int			obj_count;
	t_obj		objects[5]; // TODO malloc
}	t_app;

# endif
