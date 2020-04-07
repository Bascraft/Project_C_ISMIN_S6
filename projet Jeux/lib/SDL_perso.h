
#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 

typedef struct
{
	char key[SDLK_LAST];
	int mousex,mousey;
	int mousexrel,mouseyrel;
	char mousebuttons[8];
	char quit;
} Input;


typedef struct
{
	SDL_Rect position_ecran;
	SDL_Rect position_init;
    SDL_Surface *image_sprite;
    int hauteur_perso,largeur_perso;
	int xscroll,yscroll;//position de scroll
} Sprite;


Sprite* InitialiserSprite(Sint16 x_ecran,Sint16 y_ecran,Sint16 x_init,Sint16 y_init,char *sprite_image);
void LibereSprite(Sprite* sp);
