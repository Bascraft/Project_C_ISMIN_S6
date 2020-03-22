#include "SDL_env.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h" 



void init_map(SDL_Surface ***tab_map,SDL_Rect **tab_position){
    for (int ind_X = 0;ind_X < nb_block_X;ind_X++){
        for(int ind_Y = 0;ind_Y <nb_block_Y;ind_Y++){
            tab_map[ind_X][ind_Y] = IMG_Load("image_block/40x40_grass.png");
            tab_position[ind_X][ind_Y].x = ind_X*40;
            tab_position[ind_X][ind_Y].y = ind_Y*40;
            SDL_BlitSurface(tab_map[ind_X][ind_Y], NULL, screen, &tab_position[ind_X][ind_Y]);
        }
    }
}