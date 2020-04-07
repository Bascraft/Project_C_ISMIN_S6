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
/*void voisin(Map map,Sprite perso,int* tab_voisin[]){
	int j = perso.xscroll/map.LARGEUR_TILE;
	int i = perso.yscroll/map.HAUTEUR_TILE;
	int v_l,v_r,v_u,v_d;
	v_l = (int)map.props[map.tab_map[j-1][i]-'0'].env;
	v_r =  (int)map.props[map.tab_map[j+1][i]-'0'].env;
	v_u =  (int)map.props[map.tab_map[j][i+1]-'0'].env;
	v_d =  (int)map.props[map.tab_map[j][i-1]-'0'].env;
	tab_voisin[0] = v_l;
	tab_voisin[1] = v_r ;
	tab_voisin[2] = v_u;
	tab_voisin[3] = v_d;
}*/

void new_house(int x,int y,int taille_x,int taille_y){
	char* nom_fichier_level;
	snprintf(nom_fichier_level,11*sizeof(char)+2*sizeof(int),"level/%d_%d.txt",x,y);
	FILE* fichier_level;
    fichier_level = fopen(nom_fichier_level,"w");
	fprintf(fichier_level,"%d %d\n",taille_x,taille_y);
	for (int i =0;i<taille_y;i++){
		for (int j = 0; j < taille_x; j++)
		{
			fprintf(fichier_level,"0");
		}
		fprintf(fichier_level,"\n");
	}
	fclose(fichier_level);
}

int Bouge_sprite(SDL_Event event,Sprite *sprite,int *quit,Map map){
	//xblock = sprite->xscroll/
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
	int* tab_voisin[4];
    while( SDL_PollEvent( &event ) ){
        switch( event.type ){
            /* Look for a keypress */
            case SDL_KEYDOWN:
                /* Check the SDLKey values and move change the coords */
            switch( event.key.keysym.sym ){
                case SDLK_LEFT:
					if (sprite->xscroll <= 0){
						sprite->xscroll = 0;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else if (minx <= 0)
					{
						sprite->xscroll -= 40;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else if (maxx >= map.nb_block_largeur_monde*map.LARGEUR_TILE/map.LARGEUR_TILE && sprite->xscroll > map.nb_block_largeur_monde*map.LARGEUR_TILE -map.largeur_fenetre/2 )
					{
						sprite->xscroll -= 40;
						sprite->position_ecran.x = map.largeur_fenetre - (map.nb_block_largeur_monde*map.LARGEUR_TILE - sprite->xscroll);
					}
					
					else
					{
						sprite->xscroll -= 40;
						sprite->position_ecran.x = map.largeur_fenetre/2;
					}
                    break;
                case SDLK_RIGHT:
					if (sprite->xscroll > map.nb_block_largeur_monde*map.LARGEUR_TILE){
						sprite->xscroll = map.nb_block_largeur_monde*map.LARGEUR_TILE;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else if (minx <= 0 && sprite->xscroll < map.largeur_fenetre/2)
					{
						sprite->xscroll += 40;
						sprite->position_ecran.x = sprite->xscroll;
					}
					else if (maxx >= map.nb_block_largeur_monde*map.LARGEUR_TILE/map.LARGEUR_TILE)
					{
						sprite->xscroll += 40;
						sprite->position_ecran.x = map.largeur_fenetre - (map.nb_block_largeur_monde*map.LARGEUR_TILE - sprite->xscroll);
					}
					else
					{
						sprite->xscroll += 40;
						sprite->position_ecran.x = map.largeur_fenetre/2;
					}
                    break;
                    
                case SDLK_UP:
                    if (sprite->yscroll <= 0){
						sprite->yscroll = 0;
						sprite->position_ecran.y = sprite->yscroll;
					}
					else if (miny <= 0)
					{
						sprite->yscroll -= 40;
						sprite->position_ecran.y = sprite->yscroll;
					}
					else if (maxy >= map.nb_block_hauteur_monde*map.HAUTEUR_TILE/map.HAUTEUR_TILE && sprite->yscroll > map.nb_block_hauteur_monde*map.HAUTEUR_TILE -map.hauteur_fenetre/2 )
					{
						sprite->yscroll -= 40;
						sprite->position_ecran.y = map.hauteur_fenetre - (map.nb_block_hauteur_monde*map.HAUTEUR_TILE - sprite->yscroll);
					}
					
					else
					{
						sprite->yscroll -= 40;
						sprite->position_ecran.y = map.hauteur_fenetre/2;
					}
                    break;
                case SDLK_DOWN:
                   if (sprite->yscroll > map.nb_block_hauteur_monde*map.HAUTEUR_TILE ){
						sprite->yscroll = map.nb_block_hauteur_monde*map.HAUTEUR_TILE ;
						sprite->position_ecran.y = sprite->yscroll;
					}
					else if (miny <= 0 && sprite->yscroll < map.hauteur_fenetre/2)
					{
						sprite->yscroll += 40;
						sprite->position_ecran.y = sprite->yscroll;
					}
					else if (maxy >= map.nb_block_hauteur_monde*map.HAUTEUR_TILE/map.HAUTEUR_TILE )
					{
						sprite->yscroll += 40;
						sprite->position_ecran.y = map.hauteur_fenetre - (map.nb_block_hauteur_monde*map.HAUTEUR_TILE - sprite->yscroll);
					}
					
					else
					{
						sprite->yscroll += 40;
						sprite->position_ecran.y = map.hauteur_fenetre/2;
					}
                    break;
                case SDLK_ESCAPE:
                    (*quit) = 1;
                    break;
				case SDLK_w:
					map.tab_map[sprite->yscroll/map.LARGEUR_TILE + 1][sprite->xscroll/map.HAUTEUR_TILE] = '8';//creation maison 
					//new_house(sprite->yscroll/map.LARGEUR_TILE + 1,sprite->xscroll/map.HAUTEUR_TILE,10,10);
					break;
				case SDLK_a:
					map.tab_map[sprite->yscroll/map.LARGEUR_TILE][sprite->xscroll/map.HAUTEUR_TILE] = '0';// met bloc de terre 
					break;
				case SDLK_z:
					map.tab_map[sprite->yscroll/map.LARGEUR_TILE][sprite->xscroll/map.HAUTEUR_TILE] = '1';// mets bloc de pierre
					break;
				case SDLK_e:
					map.tab_map[sprite->yscroll/map.LARGEUR_TILE][sprite->xscroll/map.HAUTEUR_TILE] = '2';//met brique 
					break;
				case SDLK_r:
					map.tab_map[sprite->yscroll/map.LARGEUR_TILE][sprite->xscroll/map.HAUTEUR_TILE] = '3';//met plancher
					break;
				case SDLK_q:
					map.tab_map[sprite->yscroll/map.LARGEUR_TILE][sprite->xscroll/map.HAUTEUR_TILE] = '4';//met brique 
					break;
				case SDLK_s:
					map.tab_map[sprite->yscroll/map.LARGEUR_TILE][sprite->xscroll/map.HAUTEUR_TILE] = '5';//met brique 
					break;
                default:
                    break;
            }

            }
        }
    //printf("xscroll = %d;yscroll = %d\n",sprite->xscroll,sprite->yscroll);
	return 0;
	//printf("xdest = %d;ydest = %d\n",sprite->position_ecran.x,sprite->position_ecran.y);
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
	//printf("minx = %d;miny = %d;maxx = %d;maxy = %d\n",minx,miny,maxx,maxy);
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
    map->props = (TileProp*)malloc(map->nb_blockX_tileset*map->nb_blockY_tileset*sizeof(TileProp));
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
			else if (strcmp(buf2,"stairs_down")==0){
				map->props[num_block].env = 2;
            }
			else if (strcmp(buf2,"stairs_up")==0){
				map->props[num_block].env = 3;
            }
			else if (strcmp(buf2,"house")==0){
				map->props[num_block].env = 4;
            }
		}
	}
    fclose(fichier_prop);
    //free(fichier_prop);
    FILE* fichier_level;
    fichier_level = fopen(nom_fichier_level,"r");
    fscanf(fichier_prop,"%d %d",&map->nb_block_largeur_monde,&map->nb_block_hauteur_monde); // taille du monde
    //printf("taille monde : %d %d\n",map->nb_block_largeur_monde,map->nb_block_hauteur_monde);
    //allocation memoire
    map->tab_map = (blockind**)malloc(map->nb_block_hauteur_monde*sizeof(blockind*));
    for(i=0;i<map->nb_block_hauteur_monde;i++){
		map->tab_map[i] = (blockind*)malloc((map->nb_block_largeur_monde+1)*sizeof(blockind));
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
			//fscanf(fichier_level,"%d",&tmp);
			//map->tab_map[j][i] = tmp;
            //printf("tile %d %d est %d\n",i,j,map->tab_map[j][i]);
		}
        map->tab_map[j][map->nb_block_largeur_monde] = 0;
		/*for (int k=0;k<20;k++){
			printf("tab: %d",map->tab_map[j][k]);
		}*/

		printf("ligne :%s end\n",map->tab_map[j]);
    }
    fclose(fichier_level);
}    


/*void FreeMap(Map* map)
{
	int i;
	SDL_FreeSurface(map->image_block);
	for(i=0;i<map->nb_block_hauteur_monde;i++)
		free(map->tab_map[i]);
	free(map->tab_map);
	free(map->props);
	free(map);
} */
void save_map(char* nom_fichier_level,Map* map){
	FILE* fichier_level;
    fichier_level = fopen(nom_fichier_level,"w");
	int x,y;
	x = map->nb_block_largeur_monde;
	y = map->nb_block_hauteur_monde;
	fprintf(fichier_level,"%d %d\n",x,y);
	for (int i =0;i<y;i++){
		for (int j = 0; j < x; j++)
		{
			fprintf(fichier_level,"%c",map->tab_map[x][y]);
		}
		fprintf(fichier_level,"\n");
	}
	fclose(fichier_level);
	}

void main_Menu(MainMenu *menu,SDL_Event event,int* quit_menu,int* quit_game,SDL_Surface* screen,int largeurscreen,int hauteurscreen){
	//menu = NULL;
	SDL_Rect pos_play;
    SDL_Rect pos_exit;
	menu->exit_enfonce =0;
	menu->play_enfonce =0;
	menu->image_play_default = IMG_Load("image_menu/Play_default.bmp");
	menu->image_exit_default = IMG_Load("image_menu/exit_default.bmp");
	menu->image_play_enfonce = IMG_Load("image_menu/play_enfonce.bmp");
	menu->image_exit_enfonce = IMG_Load("image_menu/exit_enfonce.bmp");
	pos_play.x = largeurscreen/2 - menu->image_play_default->w/2;
	pos_play.h = menu->image_play_default->h;
	pos_play.w = menu->image_play_default->w;
	pos_play.y = hauteurscreen/4;
	pos_exit.x = pos_play.x;
	pos_exit.y = hauteurscreen/2;
	pos_exit.h = menu->image_exit_default->h;
	pos_exit.w = menu->image_exit_default->w;		
	SDL_BlitSurface(menu->image_exit_default,NULL,screen,&pos_exit);
	SDL_BlitSurface(menu->image_play_default,NULL,screen,&pos_play);
	while( SDL_PollEvent( &event ) ){
		if( event.type == SDL_MOUSEBUTTONUP ){
			if (event.button.button == SDL_BUTTON_LEFT){
				menu->play_enfonce = check_click_in_rect(event.button.x,event.button.y,&pos_play);
				menu->exit_enfonce = check_click_in_rect(event.button.x,event.button.y,&pos_exit);
				printf("%d %d\n",menu->play_enfonce,menu->exit_enfonce);
				if (menu->play_enfonce == 1){
					pos_play.h = menu->image_play_enfonce->h;
					pos_play.w = menu->image_play_enfonce->w;
					SDL_FillRect(screen,NULL,0x000000);
					SDL_BlitSurface(menu->image_exit_default,NULL,screen,&pos_exit);
					apply_surface(pos_play.x,pos_play.y,menu->image_play_enfonce,screen);
					SDL_Flip(screen);
					(*quit_game) = 2;
					(*quit_menu) = 1;
				}
				if (menu->exit_enfonce == 1)
				{
					pos_exit.h = menu->image_exit_enfonce->h;
					pos_exit.w = menu->image_exit_enfonce->w;
					SDL_FillRect(screen,NULL,0x000000);
					SDL_BlitSurface(menu->image_play_default,NULL,screen,&pos_play);
					apply_surface(pos_exit.x,pos_exit.y,menu->image_exit_enfonce,screen);
					SDL_Flip(screen);
					(*quit_menu) = 1;
				}
			}
		}
	}
}





int world(char* nom_fichier_prop,char* nom_fichier_level,SDL_Surface* screen,SDL_Event event,Sprite *perso,Map monde,Map maison){
	//Map monde;

	int* v[4];
	int quit_world = 0;
	int x_monde,y_monde;
	int x,y;
	int minx,miny,maxx,maxy;
	int milieu_x,milieu_y;
	while (!quit_world){

		milieu_x = perso->xscroll+perso->largeur_perso/2;
		milieu_y = perso->yscroll+perso->hauteur_perso/2;
		//condition selon X
		//printf("milieux : %d;milieuy : %d\n",milieu_x,milieu_y);
		if (milieu_x < monde.largeur_fenetre/2)
		{
			minx = 0;
			maxx = monde.largeur_fenetre/monde.LARGEUR_TILE;
		}
		else if (milieu_x >monde.nb_block_largeur_monde*monde.LARGEUR_TILE - monde.largeur_fenetre/2)
		{
			minx = (monde.nb_block_largeur_monde*monde.LARGEUR_TILE - monde.largeur_fenetre)/monde.LARGEUR_TILE;
			maxx = (monde.nb_block_largeur_monde*monde.LARGEUR_TILE)/monde.LARGEUR_TILE;
		}
		else{
			minx = (milieu_x - monde.largeur_fenetre/2)/monde.LARGEUR_TILE;
			maxx = (milieu_x + monde.largeur_fenetre/2)/monde.LARGEUR_TILE;
		}
		//condition selon Y
		if (milieu_y < monde.hauteur_fenetre/2)
		{
			miny = 0;
			maxy = monde.hauteur_fenetre/monde.HAUTEUR_TILE;
		}
		else if (milieu_y >monde.nb_block_hauteur_monde*monde.HAUTEUR_TILE - monde.hauteur_fenetre/2)
		{
			miny = (monde.nb_block_hauteur_monde*monde.HAUTEUR_TILE - monde.hauteur_fenetre)/monde.HAUTEUR_TILE;
			maxy = monde.nb_block_hauteur_monde*monde.HAUTEUR_TILE/monde.HAUTEUR_TILE;
		}
		else{
			miny = (milieu_y - monde.hauteur_fenetre/2)/monde.HAUTEUR_TILE;
			maxy = (milieu_y + monde.hauteur_fenetre/2)/monde.HAUTEUR_TILE;
		}
		//voisin(monde,(*perso),v);
		Bouge_sprite(event,perso,&quit_world,monde);
        Afficher(screen,monde,perso);
        affichersprite(screen,perso);

		x_monde = perso->xscroll/monde.LARGEUR_TILE;
		y_monde = perso->yscroll/monde.HAUTEUR_TILE;
        int numblock = monde.tab_map[y_monde][x_monde]-'0';
		printf("%d %d\n",x_monde,y_monde);
		printf("%d\n",numblock);
		if (monde.props[numblock].env == 4){
			//char* nom_fichier_level;
			//snprintf(nom_fichier_level,11*sizeof(char)+2*sizeof(int),"level/%d_%d.txt",x,y);
			
			in_house(screen,event,perso,maison);
		}
		SDL_Flip(screen);
	}
	return 2;
	
}
void in_house(SDL_Surface* screen,SDL_Event event,Sprite *perso,Map house){
	int quit_house = 0;
	while (!quit_house)
	{
		Bouge_sprite(event,perso,&quit_house,house);
        Afficher(screen,house,perso);
        affichersprite(screen,perso);
		SDL_Flip(screen);
	}
	
}


void affichersprite(SDL_Surface* screen,Sprite *sprite){
    SDL_BlitSurface(sprite->image_sprite,NULL,screen,&sprite->position_ecran);
}