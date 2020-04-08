#include "SDL_env.h"
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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
	nom_fichier_level = (char*)malloc(11*sizeof(char)+2*sizeof(int));
	snprintf(nom_fichier_level,11*sizeof(char)+2*sizeof(int),"level/%d_%d.txt",x,y);
	printf("%s\n",nom_fichier_level);
	FILE* fichier_level;
    fichier_level = fopen(nom_fichier_level,"w");
	fprintf(fichier_level,"%d %d\n",taille_x,taille_y);
	for (int i =0;i<taille_y;i++){
		for (int j = 0; j < taille_x; j++)
		{
			fprintf(fichier_level,"0");
		}
		if (i != taille_y-1)
		{
			fprintf(fichier_level,"\n");
		}
		

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
					map.tab_map[sprite->yscroll/map.LARGEUR_TILE ][sprite->xscroll/map.HAUTEUR_TILE] = '8';//creation maison 
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
	printf("ligne debut afficher: %s\n",map.tab_map[0]);
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
	printf("milieux : %d;milieuy : %d\n",milieu_x,milieu_y);
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
	printf("nb_block_hauteur_monde = %d,nb_block_largeur_monde = %d\n",map.nb_block_hauteur_monde,map.nb_block_largeur_monde);
	printf("map.hauteur_fenetre = %d,map.largeur_fenetre = %d\n",map.hauteur_fenetre,map.largeur_fenetre);
	printf("map.LARGEUR_TILE = %d,map.HAUTEUR_TILE = %d\n",map.LARGEUR_TILE,map.HAUTEUR_TILE);
	printf("minx = %d;miny = %d;maxx = %d;maxy = %d\n",minx,miny,maxx,maxy);
	for(i=minx;i<maxx;i++)//y
	{ 
		printf("i = %d\n",i);  
        printf("ligne : %s\n",map.tab_map[i]);
		for(j=miny;j<maxy;j++)//x
		{
			Rect_dest.x = (i-minx)*map.LARGEUR_TILE;// - sprite->xscroll;
			Rect_dest.y = (j-miny)*map.HAUTEUR_TILE ;//- sprite->yscroll;
            printf("%c\n",map.tab_map[i][j]);
            printf("map : %d\n",map.tab_map[i][j]-'0');
			/*Rect_source.x = (map.tab_map[j][i]-'0')*map.LARGEUR_TILE;
			Rect_source.y = 0;*/

            //printf("source : %d\n",Rect_source.x);
			//SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
			printf("test tab_map : %d\n", map.tab_map[j][i]);
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
	printf("chargement fini");
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
	//printf("%d %d\n",x,y);
	for (int i =0;i<x;i++){
		for (int j = 0; j < y; j++)
		{
			//printf("%d %d \n",i,j);
			fprintf(fichier_level,"%c",map->tab_map[i][j]);
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
	if ((*quit_game) == 1){	
		SDL_BlitSurface(menu->image_exit_default,NULL,screen,&pos_exit);
		SDL_BlitSurface(menu->image_play_default,NULL,screen,&pos_play);
	}
	if ((*quit_game) == 3)
	{
		SDL_Surface* image = IMG_Load("image_menu/but_jeu.bmp");
		SDL_BlitSurface(image,NULL,screen,NULL);
	}
	if ((*quit_game) == 4)
	{
		SDL_Surface* image = IMG_Load("image_menu/Instructions.bmp");
		SDL_BlitSurface(image,NULL,screen,NULL);
	}
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
					(*quit_game) = 3;
					//(*quit_menu) = 1;
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
		if (event.type == SDL_KEYDOWN ){
			if(event.key.keysym.sym == SDLK_SPACE && ((*quit_game) == 3)){
				(*quit_game) = 4;
			}
			else if(event.key.keysym.sym == SDLK_SPACE && ((*quit_game) == 4)){
				(*quit_game) = 2;
				(*quit_menu) = 1;

			}
		}
	}

	//printf("%d",(*quit_game));
	
}





int world(char* file_name_blockchain, char* player, Blockchain* Chains[9], Arena* Players,char* nom_fichier_prop,char* nom_fichier_level,SDL_Surface* screen,SDL_Event event,Sprite *perso,Map monde,Map maison){
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
			Block *block;
			block = find_block(Chains[0],x_monde,y_monde);
			Map map;
			printf("i got here\n");
			if (block == NULL){// quand il trouve pas 
				block = make_block(file_name_blockchain, player, Chains, Players, perso, &map, 0, block);
				printf("ligne apres makeblock %s\n",block->info->house_info.tab_map[0]);
			}
			printf("init_done\n");
			printf("ligne apres if %s\n",block->info->house_info.tab_map[0]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[1]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[2]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[3]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[4]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[5]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[6]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[7]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[8]);
			printf("ligne apres if %s\n",block->info->house_info.tab_map[9]);

			in_house(screen, event, perso, block->info->house_info, block);
			stock(file_name_blockchain,block,Chains,Players);
		}
		SDL_Flip(screen);
	}
	return 2;
	
}
void in_house(SDL_Surface* screen,SDL_Event event,Sprite *perso,Map house,Block *block){
	int quit_house = 0;
	printf("dans inhouse ligne avant while: %s\n",house.tab_map[0]);
	while (!quit_house)
	{
		printf("dans inhouse ligne: %s\n",house.tab_map[0]);
		Bouge_sprite(event,perso,&quit_house,house);
		printf("dans inhouse apres bouge: %s\n",house.tab_map[0]);
        Afficher(screen,house,perso);
        affichersprite(screen,perso);
		SDL_Flip(screen);
	}
	//make_block(file_name_blockchain,player,Chains,Players,perso,&house,1,block);
}


void affichersprite(SDL_Surface* screen,Sprite *sprite){
    SDL_BlitSurface(sprite->image_sprite,NULL,screen,&sprite->position_ecran);
}


//Procedures de bases des blockchains
Blockchain* init_blockchain(int player)     //Initialise la chaine de bloc
{
    Blockchain* chain = (Blockchain*)malloc(sizeof(Blockchain));
    chain->head = (Block*)malloc(sizeof(Block));
    chain->head->info = (Info*)malloc(sizeof(Info));
    chain->courant = (Block*)malloc(sizeof(Block));
    chain->courant->info = (Info*)malloc(sizeof(Info));
    Block* block = (Block*)malloc(sizeof(Block));
    block->info = (Info*)malloc(sizeof(Info));
    if (chain == NULL || block == NULL)
    {
        exit(EXIT_FAILURE);
    }

    //block->info = NULL;
    block->previous_hash = 0;
    block->suivant = NULL;

    chain->size = 0;
    chain->head = block;
    chain->courant = block;
    char player_name = (char) player;
    chain->player = player_name;

    return chain;
}

void calc_new_hash(Block* block)    //Calcule le hash du nouveau bloc
{
    int hash;
    int index = block->info->index;
    int author;
    sscanf(block->info->author,"%d", &author); //on convertit author en entier
    int timestamp = block->info->timestamp;
    hash = floor((index*HASH_KEY + author) % hash_timestamp(timestamp));
    if (block->previous_hash != 0)
    {
        //hash = hash % block->previous_hash;
    }
    block->info->hash = hash;
}


unsigned long hash_timestamp(int timestamp)
{
    unsigned long hashValue = 0;
    hashValue = timestamp / 8;	//on cherche a perdre de la donnee binaire
    hashValue = hashValue*HASH_KEY;
    return hashValue % HASH_SIZE;
}

void stock(char* file_name, Block* block, Blockchain* Chains[9], Arena* Players)     //On ajoute un bloc a la chaine, a repeter pour tout les joueurs
{
    int ref_player = 0;
    Blockchain* chain = init_blockchain(Players->list[ref_player]);
    chain = Chains[ref_player];
    int hash = chain->courant->info->hash;
    block->previous_hash = hash;

    if (proof_of_work(block, Chains, Players)) //Si le block est valide on l'ajoute sur la chaine de chaque joueur
    {
        
        chain->size ++;
        chain->courant->suivant = block;
        chain->courant = block;
        for (int player = 0; player<Players->nb_players; player ++)
        {
            
            Chains[player] = chain;
            //printf("player : %d\nsize : %d\n", player, Chains[player]->size);
            //Chains[player]->courant->suivant = block;
            //Chains[player]->courant = block;
        }
        save_write(file_name, block);
    }
}

int proof_of_work(Block* block, Blockchain* Chains[9], Arena* Players)      //On teste que le nouveau bloc est bien present chez tout les joueurs
{
    FILE *f_house; 
    f_house = fopen(block->info->name_house, "r");
	int x_size, y_size;
	fscanf(f_house, "%d %d", &x_size, &y_size);
    int house_size;
	house_size = x_size * y_size;
    if (house_size < 400)
        {
            printf("Une habitation doit faire plus de 20 blocs de cote pour etre valide.\n");
            return 0; //On suppose qu'une maison doit avoir une taille minimum de 25m2
        }
    //Si la maison est valide on verifie quelle est bien coherente avec toute les chaines du reseau
    int correct = 0;
	int wrong = 0;
    Blockchain* chain = init_blockchain(Players->list[0]);
    Block* block_test = (Block*)malloc(sizeof(Block));
    block_test->info = (Info*)malloc(sizeof(Info));
    for (int player = 0; player<Players->nb_players; player ++)
    {
        //printf("player : %d\nsize : %d\n", player, Chains[player]->size);
        if (Chains[0]->size == 0)
        {
            return 1;   //C'est la premiere maison construite
        }
        else
        {
            chain = Chains[player];
            block_test->info = chain->courant->info;
            int previous_hash = block->previous_hash;
            int hash = chain->courant->info->hash;
            if (hash == previous_hash)
            {
                if (Chains[player]->courant->info->index == block->info->index-1)
                {
                    correct ++;
                }
                else
                {
                    wrong ++;
                }
            }
            else
            {
                wrong ++;
            }
        }
    }
    if (correct >= wrong)
    {
        printf("correct\n");
        return 1;
    }
    else
    {
        printf("wrong...\n");
        return 0;
    }
}

//Procedures de recuperation et sauvegarde de blockchains
void save_write(char* file_name_blockchain, Block* block)
{
	FILE* file;
	file = fopen(file_name_blockchain, "a");
	if (file!= NULL)
	{
        int author;
        sscanf(block->info->author,"%d", &author); //on convertit author en entier
		fprintf(file, "%d %d %d %s %d %d %d %d\n", block->info->index, author, block->info->timestamp, (*block->info).name_house, block->info->posx, block->info->posy, block->info->hash, block->previous_hash);
        ChargerMap_level("level/level_prop.txt", block->info->name_house, &(block->info->house_info));
	}
	fclose(file);
}

Blockchain* get_save(char* file_name_blockchain, int player)
{
    Blockchain* new_chain = (Blockchain*)malloc(sizeof(Blockchain));
    new_chain = init_blockchain(player);
    FILE* file;
    file = fopen(file_name_blockchain, "r");
    Block* block = (Block*)malloc(sizeof(Block));
    block->info = (Info*)malloc(sizeof(Info));
    while (fscanf(file, "%d %hhd %d %s %d %d %d %d\n",&block->info->index, block->info->author, &block->info->timestamp, (*block->info).name_house, &block->info->posx, &block->info->posy, &block->info->hash, &block->previous_hash) == 6)
    {
        new_chain->size ++;
        block->previous_hash = new_chain->head->info->hash;
        new_chain->head = block;
        ChargerMap_level("level/level_prop.txt", block->info->name_house, &(block->info->house_info));
    }
	fclose(file);
    
    //il faut ajouter la nouvelle chaine a Chains !!!!!!!!!!!!!
    return new_chain;
}

Block* make_block(char* file_name_blockchain, char* player, Blockchain* Chains[9], Arena* Players, Sprite* perso, Map* map,int sauv,Block *block){
    if (sauv == 0)
	{
		int ref_player = 0;
    	Blockchain* chain = init_blockchain(Players->list[ref_player]);
    	chain = Chains[ref_player];
		int x, y, taille_x;
		x = perso->xscroll;
		y = perso->yscroll;
		printf("Mettez une dimenssion de la maison carree en blocs : ");
		scanf("%d", &taille_x);

		new_house(x, y, taille_x, taille_x);

		char* nom_fichier_map = (char*)malloc(11*sizeof(char)+2*sizeof(int));
		snprintf(nom_fichier_map,11*sizeof(char)+2*sizeof(int),"level/%d_%d.txt",x,y);
		
		printf("coucou");
		ChargerMap_level("level/level_prop.txt", nom_fichier_map, map);
		printf("chargermap_okey"); 
		block = (Block*)malloc(sizeof(Block));
		printf("%d\n",chain->size);
		Info* info = (Info*)malloc(sizeof(Info));
        info->index = Chains[0]->size + 1;
		printf("a\n");
        info->author = player;
        info->timestamp = (int) time(NULL);
        info->name_house = nom_fichier_map;
        info->house_info = *map;
        printf("b\n");
        info->posx = x;
        info->posy = y;
        printf("c\n");
  		block->info = info;
  		printf("test map : %s\n", block->info->house_info.tab_map[0]);
  		printf("d\n");
        calc_new_hash(block);
        printf("e\n");
        block->suivant = NULL;
        printf("f\n");
        block->previous_hash = Chains[0]->courant->info->hash;
		printf("finished make_block\n"); 
		return block;
	}
	
	else {
		stock(file_name_blockchain, block, Chains, Players);
	}
}

Block* find_block(Blockchain* chain, int x, int y)
{
    Block* block = (Block*)malloc(sizeof(Block));
    block->info = (Info*)malloc(sizeof(Info));
    block = chain->head;
    printf("okey");
    while (1)
    {
        block = block->suivant;
        if (block == NULL)
        {
            return NULL;    //la liste chainee est vide
        }
        else if (block->info->posx == x && block->info->posy == y)
        {
            return block;
        }
        else if (block == chain->courant)
        {
            return NULL;
        }
    }
}

void new_player(char* file_name_blockchain, Arena* Players, Blockchain* Chains[9])
{
    Players->list[Players->nb_players] = Players->nb_players;
    Chains[Players->nb_players] = Chains[0];
    Players->nb_players ++;
}
