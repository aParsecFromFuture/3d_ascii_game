#include "vector.h"

struct FhpVector fhp_vector_create(double x, double y, double z)
{
    struct FhpVector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

struct FhpVector fhp_vector_sum(struct FhpVector v1, struct FhpVector v2)
{
        return fhp_vector_create(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

struct FhpVector fhp_vector_ex(struct FhpVector v1, struct FhpVector v2)
{
    return fhp_vector_create(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

struct FhpVector fhp_vector_normalize(struct FhpVector v)
{
    double len = fhp_vector_length(v);
    return fhp_vector_create(v.x / len, v.y / len, v.z / len);
}

struct FhpVector fhp_vector_rotateXY(struct FhpVector v, double arc)
{
    return fhp_vector_create(v.x * cos(arc) - v.y * sin(arc), v.x * sin(arc) + v.y * cos(arc), v.z);
}

struct FhpVector fhp_vector_rotateXZ(struct FhpVector v, double arc)
{
    return fhp_vector_create(v.x * cos(arc) - v.z * sin(arc), v.y, v.x * sin(arc) + v.z * cos(arc));
}

struct FhpVector fhp_vector_rotateYZ(struct FhpVector v, double arc)
{
    return fhp_vector_create(v.x, v.y * cos(arc) - v.z * sin(arc), v.y * sin(arc) + v.z * cos(arc));
}

struct FhpVector fhp_vector_negative(struct FhpVector v)
{
    return fhp_vector_create(-v.x, -v.y, -v.z);
}

double fhp_vector_length(struct FhpVector v)
{
    return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

double fhp_vector_skaler_product(struct FhpVector v1, struct FhpVector v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

void fhp_vector_print_to_terminal(struct FhpVector v)
{
    printf("*** FhpVector ***\n");
    printf("x : %.2lf\n", v.x);
    printf("y : %.2lf\n", v.y);
    printf("z : %.2lf\n", v.z);
}

struct FhpRay fhp_ray_create(struct FhpVector v1, struct FhpVector v2)
{
    struct FhpRay ray;
    ray.origin = v1;
    ray.direction = fhp_vector_normalize(v2);
    return ray;
}

struct FhpVector fhp_ray_get_coord(struct FhpRay ray, double t)
{
    return fhp_vector_sum(ray.origin, fhp_vector_skaler_multiplication(ray.direction, t));
}

struct FhpVector fhp_vector_cross_product(struct FhpVector v1, struct FhpVector v2)
{
    return fhp_vector_create(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

struct FhpVector fhp_vector_skaler_multiplication(struct FhpVector v, double n)
{
    return fhp_vector_create(n * v.x, n * v.y, n * v.z);
}