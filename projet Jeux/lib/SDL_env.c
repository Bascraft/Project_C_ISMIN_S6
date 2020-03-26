#include "SDL_env.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h" 
#include <string.h>


/*void init_map(Map *map){
    int i,j;
    for(i=0;i<nb_block_largeur;i++)
	{   

		for(j=0;j<nb_block_hauteur;j++)
		{
            map->tab_map[i][j] = '0';
            //printf("element %d/%d %c   ",i,j,map->tab_map[i][j]);
            //strcat(map.tab_map[i],"0");
		}
        map->tab_map[i][nb_block_hauteur] = '\0';
        //printf("une ligne :%s\n",map->tab_map[i]);
	}


}*/
void Bouge_sprite(SDL_Event event,Sprite *sprite,int *quit,Map map){
    int milieu_x,milieu_y;
	milieu_x = sprite->xscroll+sprite->largeur_perso/2;
	milieu_y = sprite->yscroll+sprite->hauteur_perso/2;
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
            switch( event.key.keysym.sym ){
                case SDLK_LEFT:
					if (sprite->xscroll <= 0)
					{
						sprite->xscroll = 0;
						sprite->position_ecran.x = sprite->xscroll;
					}
					
					else if (sprite->xscroll >= map.nb_block_largeur_monde*map.LARGEUR_TILE - map.largeur_fenetre/2)
					{
						sprite->xscroll -= 40;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else if (sprite->xscroll <= map.largeur_fenetre/2)
					{
						sprite->xscroll -= 40;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else{
						sprite->xscroll -= 40;}
                    break;
                case SDLK_RIGHT:
					if (sprite->xscroll >= map.nb_block_largeur_monde*map.LARGEUR_TILE)
					{
						sprite->xscroll = map.nb_block_largeur_monde*map.LARGEUR_TILE;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else if (sprite->xscroll >= map.nb_block_largeur_monde*map.LARGEUR_TILE - map.largeur_fenetre/2)
					{
						sprite->xscroll += 40;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else if (sprite->xscroll <= map.largeur_fenetre/2)
					{
						sprite->xscroll += 40;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else{
						sprite->xscroll += 40;}
                    break;
                    
                    break;
                case SDLK_UP:
                    sprite->yscroll -= 40;
                    break;
                case SDLK_DOWN:
                    sprite->yscroll += 40;
                    break;
                case SDLK_ESCAPE:
                    (*quit) = 1;
                    break;
                default:
                    break;
            }

            }
        }
    printf("xscroll = %d;yscroll = %d\n",sprite->xscroll,sprite->yscroll);
	printf("xdest = %d;ydest = %d\n",sprite->position_ecran.x,sprite->position_ecran.y);
}
void Afficher(SDL_Surface* screen,Map map,Sprite *sprite)
{
	int i,j,numblock;
	SDL_Rect Rect_dest;
	//SDL_Rect Rect_source;
	//Rect_source.w = map.LARGEUR_TILE;
	//Rect_source.h = map.HAUTEUR_TILE;
    int minx,miny,maxx,maxy;
	int milieu_x,milieu_y;
	milieu_x = sprite->xscroll+sprite->largeur_perso/2;
	milieu_y = sprite->yscroll+sprite->hauteur_perso/2;
	//condition selon X
	//printf("milieux : %d;milieuy : %d\n",milieu_x,milieu_y);
	if (milieu_x < map.largeur_fenetre/2)
	{
		minx = 0;
		maxx = map.largeur_fenetre/map.LARGEUR_TILE;
	}
	else if (milieu_x >map.nb_block_largeur_monde*map.LARGEUR_TILE - map.largeur_fenetre/2)
	{
		minx = (map.nb_block_largeur_monde*map.LARGEUR_TILE - map.largeur_fenetre)/map.LARGEUR_TILE;
		maxx = (map.nb_block_largeur_monde*map.LARGEUR_TILE)/map.LARGEUR_TILE;
	}
	else{
		minx = (milieu_x - map.largeur_fenetre/2)/map.LARGEUR_TILE;
		maxx = (milieu_x + map.largeur_fenetre/2)/map.LARGEUR_TILE;
	}
	//condition selon Y
	if (milieu_y < map.hauteur_fenetre/2)
	{
		miny = 0;
		maxy = map.hauteur_fenetre/map.HAUTEUR_TILE;
	}
	else if (milieu_y >map.nb_block_hauteur_monde*map.HAUTEUR_TILE - map.hauteur_fenetre/2)
	{
		miny = (map.nb_block_hauteur_monde*map.HAUTEUR_TILE - map.hauteur_fenetre)/map.HAUTEUR_TILE;
		maxy = map.nb_block_hauteur_monde*map.HAUTEUR_TILE/map.HAUTEUR_TILE;
	}
	else{
		miny = (milieu_y - map.hauteur_fenetre/2)/map.HAUTEUR_TILE;
		maxy = (milieu_y + map.hauteur_fenetre/2)/map.HAUTEUR_TILE;
	}
	printf("minx = %d;miny = %d;maxx = %d;maxy = %d\n",minx,miny,maxx,maxy);
	for(i=minx;i<maxx;i++)//y
	{   
        //printf("ligne : %s\n",map.tab_map[i]);
		for(j=miny;j<maxy;j++)//x
		{
			Rect_dest.x = (i-minx)*map.LARGEUR_TILE;// - sprite->xscroll;
			Rect_dest.y = (j-miny)*map.HAUTEUR_TILE ;//- sprite->yscroll;
            //printf("%c\n",map.tab_map[i][j]);
            //printf("map : %d\n",map.tab_map[i][j]-'0');
			/*Rect_source.x = (map.tab_map[j][i]-'0')*map.LARGEUR_TILE;
			Rect_source.y = 0;*/

            //printf("source : %d\n",Rect_source.x);
			//SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
            numblock = map.tab_map[j][i]-'0';
			//printf("destx = %d;desty = %d\n",Rect_dest.x ,Rect_dest.y);
			//printf("%d",numblock);
			SDL_BlitSurface(map.image_block,&(map.props[numblock].R),screen,&Rect_dest);
		}
		//printf("end\n");
	}
	
}

void ChargerMap_level(char* nom_fichier_prop,char* nom_fichier_level,Map* map){
    //a mettre autre part
    map->largeur_fenetre = 640;
    map->hauteur_fenetre = 480;
    //fin a mettre autre part
    FILE* fichier_prop;
    fichier_prop = fopen(nom_fichier_prop,"r");
    int num_block,i,j;
	char buf[Buffer_size];  //mémoire cache
	char buf2[Buffer_size];  //mémoire cache
    fscanf(fichier_prop,"%s",buf); // nom du fichier
    map->image_block = IMG_Load(buf);
    fscanf(fichier_prop,"%d %d",&map->nb_blockX_tileset,&map->nb_blockY_tileset);
    map->LARGEUR_TILE = map->image_block->w/map->nb_blockX_tileset;
	map->HAUTEUR_TILE = map->image_block->h/map->nb_blockY_tileset;
    map->props = malloc(map->nb_blockX_tileset*map->nb_blockY_tileset*sizeof(TileProp));
    for(j=0,num_block=0;j<map->nb_blockY_tileset;j++)
	{
		for(i=0;i<map->nb_blockX_tileset;i++,num_block++)
		{
			map->props[num_block].R.w = map->LARGEUR_TILE;
			map->props[num_block].R.h = map->HAUTEUR_TILE;
			map->props[num_block].R.x = i*map->LARGEUR_TILE;
			map->props[num_block].R.y = j*map->HAUTEUR_TILE;
			fscanf(fichier_prop,"%s %s",buf,buf2);
            if (strcmp(buf2,"background")==0){
			    map->props[num_block].env = 0;
            }
			else if (strcmp(buf2,"foreground")==0){
				map->props[num_block].env = 1;
            }
		}
	}
    fclose(fichier_prop);
    free(fichier_prop);
    FILE* fichier_level;
    fichier_level = fopen(nom_fichier_level,"r");
    fscanf(fichier_prop,"%d %d",&map->nb_block_largeur_monde,&map->nb_block_hauteur_monde); // taille du monde
    //printf("taille monde : %d %d\n",map->nb_block_largeur_monde,map->nb_block_hauteur_monde);
    //allocation memoire
    map->tab_map = malloc(map->nb_block_hauteur_monde*sizeof(blockind*));
    for(i=0;i<map->nb_block_hauteur_monde;i++){
		map->tab_map[i] = malloc(map->nb_block_largeur_monde*sizeof(blockind));
    }
    //importation donnee
    for(j=0;j<map->nb_block_largeur_monde;j++)
	{
		fscanf(fichier_level,"%c",buf);
		for(i=0;i<map->nb_block_hauteur_monde;i++)
		{
			//printf("i = %d %d\n",i,map->nb_block_largeur_monde);
			//int tmp;
			fscanf(fichier_level,"%c",&map->tab_map[j][i]);
			/*if (tmp>=map->nb_blockX_tileset*map->nb_blockY_tileset){
				ErrorQuit("level tile hors limite\n");
            }*/
			//map->tab_map[j][i] = (char)tmp;
            //printf("tile %d %d est %d\n",i,j,map->tab_map[j][i]);
		}
        map->tab_map[j][map->nb_block_largeur_monde] = 0;
		/*for (int k=0;k<20;k++){
			printf("tab: %d",map->tab_map[j][k]);
		}*/

		//printf("ligne :%s end\n",map->tab_map[j]);
    }
    
}    


void FreeMap(Map* map)
{
	int i;
	SDL_FreeSurface(map->image_block);
	for(i=0;i<map->nb_block_hauteur_monde;i++)
		free(map->tab_map[i]);
	free(map->tab_map);
	free(map->props);
	free(map);
}