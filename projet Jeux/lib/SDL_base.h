#include <SDL/SDL.h>
#include <SDL/SDL_image.h> 
//#define hauteur 480
//#define largeur 640
//cree la variable ecran extern et global

    
void init_SDL();
void pause();
void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void ErrorQuit(const char* error);
int check_click_in_rect(int x, int y, struct SDL_Rect *rect);