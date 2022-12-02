#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec3
{
	float	x;
	float	y;
	float	z;
}	t_vec3;

typedef struct s_ray3
{
	t_vec3	orig;
	t_vec3	dir;
}	t_ray3;

// TODO maybe array would be better for this?
// typedef struct s_mat4
// {
// 	float x1;
// 	float y1;
// 	float z1;
// 	float w1;
// 	float x2;
// 	float y2;
// 	float z2;
// 	float w2;
// 	float x3;
// 	float y3;
// 	float z3;
// 	float w3;
// 	float x4;
// 	float y4;
// 	float z4;
// 	float w4;
// }	t_mat4;

typedef union u_mat4
{
	float arr[16];
	struct
	{
		float v1[4];
		float v2[4];
		float v3[4];
		float v4[4];
	};
	struct
	{
		float x1;
		float y1;
		float z1;
		float w1;
		float x2;
		float y2;
		float z2;
		float w2;
		float x3;
		float y3;
		float z3;
		float w3;
		float x4;
		float y4;
		float z4;
		float w4;
	};
} t_mat4;

t_vec3	vec3(float x, float y, float z);
t_vec3	v_add(t_vec3 a, t_vec3 b);
t_vec3	v_sub(t_vec3 a, t_vec3 b);
t_vec3	v_mul(t_vec3 v, float factor);
float	dot(t_vec3 a, t_vec3 b);
float	length(t_vec3 a);
t_vec3	normalize(t_vec3 a);
t_vec3	v_lerp(t_vec3 *a, t_vec3 *b, float t);
t_vec3	at(const t_ray3 *r, float t);

# endif
