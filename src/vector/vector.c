#include <miniRT.h>
#include <math.h>

t_vec3	vec3(float x, float y, float z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

// TODO pass by value or pass by reference? Which is more performant?
t_vec3	v_add(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x + b.x;
	result.y = a.y + b.y;
	result.z = a.z + b.z;
	return (result);
}

t_vec3	v_sub(t_vec3 a, t_vec3 b)
{
	t_vec3	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	result.z = a.z - b.z;
	return (result);
}

t_vec3	v_mul(t_vec3 v, float factor)
{
	t_vec3	result;

	result.x = v.x * factor;
	result.y = v.y * factor;
	result.z = v.z * factor;
	return (result);
}

t_vec3	v_mulv(t_vec3 v, t_vec3 factor)
{
	t_vec3	result;

	result.x = v.x * factor.x;
	result.y = v.y * factor.y;
	result.z = v.z * factor.z;
	return (result);
}

t_vec3	v_min(t_vec3 a, float min)
{
	t_vec3	result;

	result.x = fminf(a.x, min);
	result.y = fminf(a.y, min);
	result.z = fminf(a.z, min);
	return (result);
}

float	dot(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

float	length(t_vec3 a)
{
	return (sqrtf(a.x * a.x + a.y * a.y + a.z * a.z));
}

t_vec3	normalize(t_vec3 a)
{
	t_vec3	result;
	float	l;

	l = length(a);
	result.x = a.x / l;
	result.y = a.y / l;
	result.z = a.z / l;
	return (result);
}

t_vec3	v_lerp(t_vec3 *a, t_vec3 *b, float t)
{
	t_vec3	result;

	result.x = lerp(a->x, b->x, t);
	result.y = lerp(a->y, b->y, t);
	result.z = lerp(a->z, b->z, t);
	return (result);
}

t_vec3	at(const t_ray3 *r, float t)
{
	return (v_add(r->orig, v_mul(r->dir, t)));
}

t_vec3	reflect(t_vec3 incident, t_vec3 normal)
{
	return v_sub(incident, v_mul(normal, 2 * dot(normal, incident)));
}
