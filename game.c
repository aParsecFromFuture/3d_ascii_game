#include "game.h"

struct FhpWorld* fhp_world_create(char **map)
{
    struct FhpWorld *world = malloc(sizeof(struct FhpWorld));
    struct FhpVector left_top, right_top, right_bottom, left_bottom;
    world->map_width = 10;
    world->map_height = 10;
    world->player_coord_x = 0;
    world->player_coord_y = 0;
    world->player_direction_x = 0;
    world->player_direction_y = 1;
    world->space_unit = 1;
    
    for(int i = 0; i < 10; i++){
        for(int j = 0;j < 10; j++){
            world->map[i][j] = EMPTY;
        }
    }
    
    world->player = fhp_observer_create();
    world->space = fhp_space_create();
    
    left_top = fhp_vector_create(0, -0.5, 0);
    right_top = fhp_vector_create(10, -0.5, 0);
    right_bottom = fhp_vector_create(10, -0.5, 10);
    left_bottom = fhp_vector_create(0, -0.5, 10);
    
    fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(left_top, right_top, right_bottom)));
    fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(left_top, left_bottom, right_bottom)));
    
    fhp_observer_connect_to_space(world->player, world->space);
    
    return world;
}

void fhp_world_add_obstacle(struct FhpWorld *world, int x, int y)
{
    struct FhpVector f_left_top, f_right_top, f_right_bottom, f_left_bottom, c_left_top, c_right_top, c_right_bottom, c_left_bottom;
    double height = -0.5;
    if(world->map[x][y] == EMPTY){
        world->map[x][y] = OBSTACLE;
        
        f_left_top = fhp_vector_create(x, height, y);
        f_right_top = fhp_vector_create(x + world->space_unit, height, y);
        f_left_bottom = fhp_vector_create(x, height, y + world->space_unit);
        f_right_bottom = fhp_vector_create(x + world->space_unit, height, y + world->space_unit);
        c_left_top = fhp_vector_create(x, 1 + height, y);
        c_right_top = fhp_vector_create(x + world->space_unit, 1 + height, y);
        c_left_bottom = fhp_vector_create(x, 1 + height, y + world->space_unit);
        c_right_bottom = fhp_vector_create(x + world->space_unit, 1 + height, y + world->space_unit);
        
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(f_left_top, f_right_top, c_left_top)));
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(c_right_top, f_right_top, c_left_top)));
        
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(f_right_top, f_right_bottom, c_right_top)));
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(c_right_bottom, f_right_bottom, c_right_top)));
        
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(f_right_bottom, f_left_bottom, c_right_bottom)));
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(c_left_bottom, f_left_bottom, c_right_bottom)));
        
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(f_left_bottom, f_left_top, c_left_bottom)));
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_triangle_create(c_left_top, f_left_top, c_left_bottom)));
    }
}

void fhp_world_add_sphere(struct FhpWorld *world, int x, int y)
{
    if(world->map[x][y] == EMPTY){
        world->map[x][y] = OBSTACLE;
        
        fhp_space_add_object(world->space, FHP_SHAPE(fhp_sphere_create(fhp_vector_create(x + 0.5, -0.5, y + 0.5), 0.5)));
    }
}

void fhp_world_player_turn_left(struct FhpWorld *world)
{
    int swap = world->player_direction_x;
    world->player_direction_x = -world->player_direction_y;
    world->player_direction_y = swap;
    fhp_observer_turn_left(world->player, M_PI / 2);
}

void fhp_world_player_turn_right(struct FhpWorld *world)
{
    int swap = world->player_direction_x;
    world->player_direction_x = world->player_direction_y;
    world->player_direction_y = -swap;
    fhp_observer_turn_right(world->player, M_PI / 2);
}

void fhp_world_player_move_forward(struct FhpWorld *world)
{
    unsigned int x, y, new_x, new_y;
    x = world->player_coord_x;
    y = world->player_coord_y;
    new_x = x + world->player_direction_x;
    new_y = y + world->player_direction_y;
    if(new_x < world->map_width && new_y < world->map_height && world->map[new_x][new_y] == EMPTY){
        world->map[x][y] = EMPTY;
        world->map[new_x][new_y] = PLAYER;
        world->player_coord_x = new_x;
        world->player_coord_y = new_y;
        fhp_observer_move_forward(world->player);
    }
}

void fhp_world_player_move_back(struct FhpWorld *world)
{
    unsigned x, y, new_x, new_y;
    x = world->player_coord_x;
    y = world->player_coord_y;
    new_x = x - world->player_direction_x;
    new_y = y - world->player_direction_y;
    if(new_x < world->map_width && new_y < world->map_height && world->map[new_x][new_y] == EMPTY){
        world->map[x][y] = EMPTY;
        world->map[new_x][new_y] = PLAYER;
        world->player_coord_x = new_x;
        world->player_coord_y = new_y;
        fhp_observer_move_back(world->player);
    }
}

void fhp_world_print_to_terminal(struct FhpWorld *world)
{
    fhp_observer_print_screen_to_terminal(world->player, 160, 90);
    printf("\033[H");
    for(int i = 0; i < world->map_height; i++){
        for(int j = 0; j < world->map_width; j++){
            switch(world->map[j][i]){
                case EMPTY :
                printf("  ");
                break;
                case PLAYER :
                printf("o ");
                break;
                case OBSTACLE:
                printf("x  ");
                break;
            }
        }
        printf("\n");
    }
}
