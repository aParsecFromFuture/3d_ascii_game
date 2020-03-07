#ifndef GAME_H
#define GAME_H
#include "observer.h"

enum GAME_OBJECT{EMPTY, PLAYER, OBSTACLE};

struct FhpWorld{
    int map_width;
    int map_height;
    int player_coord_x;
    int player_coord_y;
    int player_direction_x;
    int player_direction_y;
    double space_unit;
    enum GAME_OBJECT map[10][10];
    struct FhpSpace *space;
    struct FhpObserver *player;
};

struct FhpWorld* fhp_world_create();
void fhp_world_add_obstacle(struct FhpWorld*, int, int);
void fhp_world_add_sphere(struct FhpWorld*, int, int);

void fhp_world_player_turn_left(struct FhpWorld*);
void fhp_world_player_turn_right(struct FhpWorld*);

void fhp_world_player_move_forward(struct FhpWorld*);
void fhp_world_player_move_back(struct FhpWorld*);

void fhp_world_print_to_terminal(struct FhpWorld*);
#endif