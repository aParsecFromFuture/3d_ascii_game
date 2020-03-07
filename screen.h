#ifndef SCREEN_H
#define SCREEN_H
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 500;
#include "shape.h"

extern char PIXEL[10];

struct FhpScreen{
    unsigned int width;
    unsigned int height;
    char **pixels;
};

struct FhpSpace{
    unsigned int object_count;
    struct FhpShape *objects;
};

struct FhpScreen* fhp_screen_create(unsigned int, unsigned int);
struct FhpVector fhp_screen_get_3d(struct FhpScreen*, int, int);
void fhp_screen_print_to_terminal(struct FhpScreen*);

struct FhpSpace* fhp_space_create();
void fhp_space_add_object(struct FhpSpace*, struct FhpShape*);

void fhp_space_translation(struct FhpSpace*, struct FhpVector);

void fhp_space_rotateXY(struct FhpSpace*, double);
void fhp_space_rotateXZ(struct FhpSpace*, double);
void fhp_space_rotateYZ(struct FhpSpace*, double);

#endif