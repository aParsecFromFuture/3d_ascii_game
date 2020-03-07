#ifndef VECTOR_H
#define VECTOR_H
#include <stdio.h>
#include <math.h>

struct FhpVector{
    double x;
    double y;
    double z;
};

struct FhpRay{
    struct FhpVector origin;
    struct FhpVector direction;
};

struct FhpVector fhp_vector_create(double, double, double);
struct FhpVector fhp_vector_sum(struct FhpVector, struct FhpVector);
struct FhpVector fhp_vector_ex(struct FhpVector, struct FhpVector);
struct FhpVector fhp_vector_normalize(struct FhpVector);

struct FhpVector fhp_vector_rotateXY(struct FhpVector, double);
struct FhpVector fhp_vector_rotateXZ(struct FhpVector, double);
struct FhpVector fhp_vector_rotateYZ(struct FhpVector, double);

struct FhpVector fhp_vector_negative(struct FhpVector);

double fhp_vector_length(struct FhpVector);
double fhp_vector_skaler_product(struct FhpVector, struct FhpVector);

struct FhpVector fhp_vector_cross_product(struct FhpVector, struct FhpVector);
struct FhpVector fhp_vector_skaler_multiplication(struct FhpVector, double);

void fhp_vector_print_to_terminal(struct FhpVector);

struct FhpRay fhp_ray_create(struct FhpVector, struct FhpVector);
struct FhpVector fhp_ray_get_coord(struct FhpRay, double);

#endif