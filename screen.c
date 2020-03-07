#include "screen.h"

char PIXEL[10] = {'m', 'n', '<', '=', '*', '_', '-', ';', ',', '.'};

struct FhpScreen* fhp_screen_create(unsigned int w, unsigned int h)
{
    struct FhpScreen *screen = malloc(sizeof(struct FhpScreen));
    screen->width = w;
    screen->height = h;
    screen->pixels = malloc(sizeof(char*) * w);
    for(int i = 0; i < w; i++){
        screen->pixels[i] = malloc(sizeof(char) * h);
    }
    
    return screen;
}

struct FhpVector fhp_screen_get_3d(struct FhpScreen *screen, int x, int y)
{
    double w = screen->width - 1;
    double h = screen->height - 1;
    return fhp_vector_create(16*x / w - 8, 4.5 - y*9 / h, 10);
}

void fhp_screen_print_to_terminal(struct FhpScreen *screen)
{
    printf("\033[H\033[J");
    for(int i = 0; i < screen->height; i++){
        for(int j = 0; j < screen->width; j++){
            printf("%c ", screen->pixels[j][i]);
        }
        printf("\n");
    }
}

struct FhpSpace* fhp_space_create()
{
    struct FhpSpace *space = malloc(sizeof(struct FhpSpace));
    space->object_count = 0;
    space->objects = 0;
    return space;
}

void fhp_space_add_object(struct FhpSpace *space, struct FhpShape *shape)
{
    space->object_count++;
    space->objects = realloc(space->objects, sizeof(struct FhpShape) * space->object_count);
    space->objects[space->object_count - 1] = *fhp_shape_get_copy(shape);
}

void fhp_space_translation(struct FhpSpace *space, struct FhpVector v)
{
    for(int i = 0; i < space->object_count; i++){
        fhp_shape_translation(&space->objects[i], v);
    }
}

void fhp_space_rotateXY(struct FhpSpace *space, double arc)
{
    for(int i = 0; i < space->object_count; i++){
        fhp_shape_rotateXY(&space->objects[i], arc);
    }
}

void fhp_space_rotateXZ(struct FhpSpace *space, double arc)
{
    for(int i = 0; i < space->object_count; i++){
        fhp_shape_rotateXZ(&space->objects[i], arc);
    }
}

void fhp_space_rotateYZ(struct FhpSpace *space, double arc)
{
    for(int i = 0; i < space->object_count; i++){
        fhp_shape_rotateYZ(&space->objects[i], arc);
    }
}
