#ifndef PLAYER_H
#define PLAYER_H
#include "screen.h"

struct FhpObserver{
    struct FhpRay camera;
    struct FhpSpace *environment;
};

struct FhpObserver* fhp_observer_create();
void fhp_observer_connect_to_space(struct FhpObserver*, struct FhpSpace*);

void fhp_observer_move_forward(struct FhpObserver*);
void fhp_observer_move_back(struct FhpObserver*);
void fhp_observer_move_on(struct FhpObserver*, struct FhpVector);

void fhp_observer_turn_left(struct FhpObserver*, double);
void fhp_observer_turn_right(struct FhpObserver*, double);
void fhp_observer_turn_up(struct FhpObserver*, double);
void fhp_observer_turn_down(struct FhpObserver*, double);

void fhp_observer_get_screen(struct FhpObserver*, struct FhpScreen*);
void fhp_observer_print_screen_to_terminal(struct FhpObserver*, int, int);

#endif