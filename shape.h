#ifndef SHAPE_H
#define SHAPE_H
#include <stdlib.h>
#include "vector.h"

enum ShapeType{SPHERE, TRIANGLE};

struct FhpTriangle{
    enum ShapeType type;
    struct FhpVector vertex_1;
    struct FhpVector vertex_2;
    struct FhpVector vertex_3;
};

struct FhpSphere{
    enum ShapeType type;
    struct FhpVector center;
    double radius;
};

struct FhpShape{
    enum ShapeType type;
    unsigned char data[128];
};

struct FhpShape* FHP_SHAPE(void*);
struct FhpShape* fhp_shape_get_copy(struct FhpShape*);

void fhp_shape_translation(struct FhpShape*, struct FhpVector);

void fhp_shape_rotateXY(struct FhpShape*, double);
void fhp_shape_rotateXZ(struct FhpShape*, double);
void fhp_shape_rotateYZ(struct FhpShape*, double);

double fhp_shape_intersect_with_ray(struct FhpShape*, struct FhpRay);

struct FhpShape* fhp_shape_create(struct FhpVector, struct FhpVector);

struct FhpTriangle* FHP_TRIANGLE(struct FhpShape*);
struct FhpTriangle* fhp_triangle_create(struct FhpVector, struct FhpVector, struct FhpVector);
struct FhpTriangle* fhp_triangle_get_copy(struct FhpTriangle*);
struct FhpVector fhp_triangle_get_normal(struct FhpTriangle*);

void fhp_triangle_translation(struct FhpTriangle*, struct FhpVector);

void fhp_triangle_rotateXY(struct FhpTriangle*, double);
void fhp_triangle_rotateXZ(struct FhpTriangle*, double);
void fhp_triangle_rotateYZ(struct FhpTriangle*, double);

double fhp_triangle_get_area(struct FhpTriangle*);
double fhp_triangle_intersect_with_ray(struct FhpTriangle*, struct FhpRay);
double fhp_triangle_get_d_parameter(struct FhpTriangle*);
void fhp_triangle_print_to_terminal(struct FhpTriangle*);

struct FhpSphere* FHP_SPHERE(struct FhpShape*);
struct FhpSphere* fhp_sphere_create(struct FhpVector, double);
struct FhpSphere* fhp_sphere_get_copy(struct FhpSphere*);

void fhp_sphere_translation(struct FhpSphere*, struct FhpVector);

void fhp_sphere_rotateXY(struct FhpSphere*, double);
void fhp_sphere_rotateXZ(struct FhpSphere*, double);
void fhp_sphere_rotateYZ(struct FhpSphere*, double);

double fhp_sphere_intersect_with_ray(struct FhpSphere*, struct FhpRay);
#endif