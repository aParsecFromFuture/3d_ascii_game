#include "observer.h"

struct FhpObserver* fhp_observer_create()
{
    struct FhpObserver *observer = malloc(sizeof(struct FhpObserver));
    observer->camera = fhp_ray_create((struct FhpVector){0, 0, 0}, (struct FhpVector){0, 0, 1});
    observer->environment = 0;
    return observer;
}
void fhp_observer_connect_to_space(struct FhpObserver *observer, struct FhpSpace *space)
{
    observer->environment = space;
}

void fhp_observer_move_forward(struct FhpObserver *observer)
{
    fhp_space_translation(observer->environment, fhp_vector_negative(observer->camera.direction));
}

void fhp_observer_move_back(struct FhpObserver *observer)
{
    fhp_space_translation(observer->environment, observer->camera.direction);
}

void fhp_observer_move_on(struct FhpObserver *observer, struct FhpVector v)
{
    fhp_space_translation(observer->environment, fhp_vector_negative(v));
}

void fhp_observer_turn_left(struct FhpObserver *observer, double arc)
{
    fhp_space_rotateXZ(observer->environment, 2 * M_PI - arc);
}

void fhp_observer_turn_right(struct FhpObserver *observer, double arc)
{
    fhp_space_rotateXZ(observer->environment, arc);
}

void fhp_observer_turn_up(struct FhpObserver *observer, double arc)
{
    fhp_space_rotateYZ(observer->environment, arc);
}

void fhp_observer_turn_down(struct FhpObserver *observer, double arc)
{
    fhp_space_rotateYZ(observer->environment, 2 * M_PI - arc);
}

void fhp_observer_get_screen(struct FhpObserver *observer, struct FhpScreen *screen)
{
    struct FhpVector screen_vector;
    struct FhpRay ray = observer->camera;
    double distance, min_distance = 100000;
    for(int i = 0; i < screen->width; i++){
        for(int j = 0; j < screen->height; j++){
            screen_vector = fhp_screen_get_3d(screen, i, j);
            ray.direction = fhp_vector_normalize(fhp_vector_ex(screen_vector, ray.origin));
            for(int k = 0; k < observer->environment->object_count; k++){
                distance = fhp_shape_intersect_with_ray(&observer->environment->objects[k], ray);
                if(distance != 0 && distance < min_distance){
                    min_distance = distance;
                }
            }
            if(min_distance < 1000){
                screen->pixels[i][j] = PIXEL[((int)min_distance / 6) % 7];
            }else{
                screen->pixels[i][j] = ' ';
            }
            min_distance = 100000;
        }
    }
}

void fhp_observer_print_screen_to_terminal(struct FhpObserver *observer, int w, int h)
{
    struct FhpVector screen_vector;
    struct FhpRay ray = observer->camera;
    double width, height, distance, min_distance = 100000;
    width = w - 1;
    height = h - 1;
    printf("\033[H");
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            screen_vector = fhp_vector_create(16*j / width - 8, 4.5 - i*9 / height, 10);
            ray.direction = fhp_vector_normalize(fhp_vector_ex(screen_vector, ray.origin));
            for(int k = 0; k < observer->environment->object_count; k++){
                distance = fhp_shape_intersect_with_ray(&observer->environment->objects[k], ray);
                if(distance != 0 && distance < min_distance){
                    min_distance = distance;
                }
            }
            if(min_distance < 1000){
                printf("%c ", PIXEL[((min_distance) < 10)? (int)(min_distance) : 9]);
            }else{
                printf("%c ", ' ');
            }
            min_distance = 100000;
            distance = 100000;
        }
        printf("\n");
    }
}