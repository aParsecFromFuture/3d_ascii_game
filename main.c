#include <stdio.h>
#include "game.h"

int main(int argc, char **argv)
{
    struct FhpWorld *world = fhp_world_create();
    fhp_world_add_obstacle(world, 3, 3);
    fhp_world_add_obstacle(world, 3, 4);
    fhp_world_add_obstacle(world, 3, 5);
    fhp_world_add_sphere(world, 5, 5);
    
    fhp_observer_move_on(world->player, fhp_vector_create(0.5, 0, 0.5));
    
    char command;
    while(1){
        scanf("%c", &command);
        switch(command){
            case 'w' :
            fhp_world_player_move_forward(world);
            break;
            case 'a' :
            fhp_world_player_turn_left(world);
            break;
            case 's' :
            fhp_world_player_move_back(world);
            break;
            case 'd' :
            fhp_world_player_turn_right(world);
            break;
        }
        fhp_world_print_to_terminal(world);
    }
	return 0;
}
