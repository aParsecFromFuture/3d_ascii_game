#include "shape.h"

struct FhpShape* FHP_SHAPE(void *shape)
{
    return (struct FhpShape*)shape;
}

struct FhpShape* fhp_shape_get_copy(struct FhpShape *shape)
{
    struct FhpShape *shape_2 = malloc(sizeof(struct FhpShape));
    shape_2->type = shape->type;
    for(int i = 0; i < 128; i++){
        shape_2->data[i] = shape->data[i];
    }
    return shape_2;
}

void fhp_shape_translation(struct FhpShape *shape, struct FhpVector v)
{
    switch(shape->type){
        case SPHERE :
        fhp_sphere_translation(FHP_SPHERE(shape), v);
        return;
        case TRIANGLE :
        fhp_triangle_translation(FHP_TRIANGLE(shape), v);
        return;
    }
}

void fhp_shape_rotateXY(struct FhpShape *shape, double arc)
{
    switch(shape->type){
        case SPHERE :
        fhp_sphere_rotateXY(FHP_SPHERE(shape), arc);
        return;
        case TRIANGLE :
        fhp_triangle_rotateXY(FHP_TRIANGLE(shape), arc);
        return;
    }
}

void fhp_shape_rotateXZ(struct FhpShape *shape, double arc)
{
    switch(shape->type){
        case SPHERE :
        fhp_sphere_rotateXZ(FHP_SPHERE(shape), arc);
        return;
        case TRIANGLE :
        fhp_triangle_rotateXZ(FHP_TRIANGLE(shape), arc);
        return;
    }
}

void fhp_shape_rotateYZ(struct FhpShape *shape, double arc)
{
    switch(shape->type){
        case SPHERE :
        fhp_sphere_rotateYZ(FHP_SPHERE(shape), arc);
        return;
        case TRIANGLE :
        fhp_triangle_rotateYZ(FHP_TRIANGLE(shape), arc);
        return;
    }
}

double fhp_shape_intersect_with_ray(struct FhpShape *shape, struct FhpRay ray)
{
    switch(shape->type){
        case SPHERE : 
        return fhp_sphere_intersect_with_ray(FHP_SPHERE(shape), ray);
        case TRIANGLE :
        return fhp_triangle_intersect_with_ray(FHP_TRIANGLE(shape), ray);
        default :
        return 0;
    }
}

struct FhpTriangle* FHP_TRIANGLE(struct FhpShape *shape)
{
    return (struct FhpTriangle*)shape;
}

struct FhpTriangle* fhp_triangle_create(struct FhpVector v1, struct FhpVector v2, struct FhpVector v3)
{
    struct FhpTriangle *ta = malloc(sizeof(struct FhpTriangle));
    ta->type = TRIANGLE;
    ta->vertex_1 = v1;
    ta->vertex_2 = v2;
    ta->vertex_3 = v3;
    return ta;
}

struct FhpTriangle* fhp_triangle_get_copy(struct FhpTriangle *ta)
{
    return fhp_triangle_create(ta->vertex_1, ta->vertex_2, ta->vertex_3);
}

struct FhpVector fhp_triangle_get_normal(struct FhpTriangle *ta)
{
    struct FhpVector v2_v1 = fhp_vector_ex(ta->vertex_2, ta->vertex_1);
    struct FhpVector v3_v2 = fhp_vector_ex(ta->vertex_3, ta->vertex_2);
    return fhp_vector_normalize(fhp_vector_cross_product(v2_v1, v3_v2));
}

void fhp_triangle_translation(struct FhpTriangle *ta, struct FhpVector v)
{
    ta->vertex_1 = fhp_vector_sum(ta->vertex_1, v);
    ta->vertex_2 = fhp_vector_sum(ta->vertex_2, v);
    ta->vertex_3 = fhp_vector_sum(ta->vertex_3, v);
}

void fhp_triangle_rotateXY(struct FhpTriangle *ta, double arc)
{
    ta->vertex_1 = fhp_vector_rotateXY(ta->vertex_1, arc);
    ta->vertex_2 = fhp_vector_rotateXY(ta->vertex_2, arc);
    ta->vertex_3 = fhp_vector_rotateXY(ta->vertex_3, arc);
}

void fhp_triangle_rotateXZ(struct FhpTriangle *ta, double arc)
{
    ta->vertex_1 = fhp_vector_rotateXZ(ta->vertex_1, arc);
    ta->vertex_2 = fhp_vector_rotateXZ(ta->vertex_2, arc);
    ta->vertex_3 = fhp_vector_rotateXZ(ta->vertex_3, arc);
}

void fhp_triangle_rotateYZ(struct FhpTriangle *ta, double arc)
{
    ta->vertex_1 = fhp_vector_rotateYZ(ta->vertex_1, arc);
    ta->vertex_2 = fhp_vector_rotateYZ(ta->vertex_2, arc);
    ta->vertex_3 = fhp_vector_rotateYZ(ta->vertex_3, arc);
}

double fhp_triangle_get_area(struct FhpTriangle *ta)
{
    struct FhpVector v2_v1 = fhp_vector_ex(ta->vertex_2, ta->vertex_1);
    struct FhpVector v3_v2 = fhp_vector_ex(ta->vertex_3, ta->vertex_2);
    return fhp_vector_length(fhp_vector_cross_product(v2_v1, v3_v2));
}

double fhp_triangle_intersect_with_ray(struct FhpTriangle *ta, struct FhpRay ray)
{
    struct FhpTriangle *ta_sub;
    struct FhpVector normal, ray_coord;
    double s1, s2, s3, s_sum, t, D, epsilon = 0.05;
    
    normal = fhp_triangle_get_normal(ta);
    D = fhp_triangle_get_d_parameter(ta);
    t = -((fhp_vector_skaler_product(normal, ray.origin) + D) / fhp_vector_skaler_product(normal, ray.direction));
    
    if(t > 0){
        ray_coord = fhp_ray_get_coord(ray, t);
        ta_sub = fhp_triangle_create(ray_coord, ta->vertex_2, ta->vertex_3);
        s1 = fhp_triangle_get_area(ta_sub);
        free(ta_sub);
        ta_sub = fhp_triangle_create(ta->vertex_1, ray_coord, ta->vertex_3);
        s2 = fhp_triangle_get_area(ta_sub);
        free(ta_sub);
        ta_sub = fhp_triangle_create(ta->vertex_1, ta->vertex_2, ray_coord);
        s3 = fhp_triangle_get_area(ta_sub);
        free(ta_sub);
        s_sum = s1 + s2 + s3;
        if(fabs(s_sum - fhp_triangle_get_area(ta)) < epsilon){
            return t;
        }
    }
    return 0;
}

double fhp_triangle_get_d_parameter(struct FhpTriangle *ta)
{
    struct FhpVector normal = fhp_triangle_get_normal(ta);
    struct FhpVector vertex = ta->vertex_1;
    return -fhp_vector_skaler_product(normal, vertex);
}

void fhp_triangle_print_to_terminal(struct FhpTriangle *ta)
{
    printf("*** FhpTriangle ***\n");
    fhp_vector_print_to_terminal(ta->vertex_1);
    fhp_vector_print_to_terminal(ta->vertex_2);
    fhp_vector_print_to_terminal(ta->vertex_3);
}

struct FhpSphere* FHP_SPHERE(struct FhpShape *shape)
{
    return (struct FhpSphere*)shape;
}

struct FhpSphere* fhp_sphere_create(struct FhpVector c, double r)
{
    struct FhpSphere *sphere = malloc(sizeof(struct FhpSphere));
    sphere->type = SPHERE;
    sphere->center = c;
    sphere->radius = r;
    return sphere;
}

struct FhpSphere* fhp_sphere_get_copy(struct FhpSphere *sphere)
{
    return fhp_sphere_create(sphere->center, sphere->radius);
}

void fhp_sphere_translation(struct FhpSphere *sphere, struct FhpVector v)
{
    sphere->center = fhp_vector_sum(sphere->center, v);
}

void fhp_sphere_rotateXY(struct FhpSphere *sphere, double arc)
{
    sphere->center = fhp_vector_rotateXY(sphere->center, arc);
}

void fhp_sphere_rotateXZ(struct FhpSphere *sphere, double arc)
{
    sphere->center = fhp_vector_rotateXZ(sphere->center, arc);
}

void fhp_sphere_rotateYZ(struct FhpSphere *sphere, double arc)
{
    sphere->center = fhp_vector_rotateYZ(sphere->center, arc);
}

double fhp_sphere_intersect_with_ray(struct FhpSphere *sphere, struct FhpRay ray)
{
    struct FhpVector l;
    double s, q, s2, l2, m2, r2;
    
    l = fhp_vector_ex(sphere->center, ray.origin);
    s = fhp_vector_skaler_product(l, ray.direction);
    l2 = fhp_vector_skaler_product(l, l);
    r2 = sphere->radius * sphere->radius;
    
    if(s < 0 && l2 > r2){
        return 0;
    }
    
    s2 = s * s;
    m2 = l2 - s2;
    
    if(m2 > r2){
        return 0;
    }
    
    q = sqrt(r2 - m2);
    
    return (l2 > r2)? (s - q) : (s + q);
}
