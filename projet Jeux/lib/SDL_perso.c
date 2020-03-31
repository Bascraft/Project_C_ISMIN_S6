#include "SDL/SDL.h"
#include "SDL/SDL_image.h" 
#include "SDL_perso.h"

Sprite* InitialiserSprite(Sint16 x_ecran,Sint16 y_ecran,Sint16 x_init,Sint16 y_init,char *sprite_image)
{   
    Sprite* sprite = malloc(sizeof(Sprite));
	sprite->image_sprite = IMG_Load(sprite_image);
    sprite->hauteur_perso = sprite->image_sprite->h;
    sprite->largeur_perso = sprite->image_sprite->w;
    sprite->position_ecran.x = x_ecran;
	sprite->position_ecran.y = y_ecran;
	sprite->position_ecran.w = sprite->largeur_perso;
	sprite->position_ecran.h = sprite->hauteur_perso;
    sprite->xscroll = x_init;
    sprite->yscroll = y_init;
	return sprite;
}
void LibereSprite(Sprite* sp)
{
	free(sp);
}



