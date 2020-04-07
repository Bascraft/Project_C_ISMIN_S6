#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "reseau.h"

void send_message_house_created(ordi *pc){
    FILE *fichier_reseau;
    fichier_reseau = fopen(pc->nom_fichier_reseau,"a");
    time_t crt = time(NULL);
    //fprintf("%d: PC%d, I've_created_a_house\n",(int)crt,pc->nom_pc);

}

void read_file(ordi *pc){
    FILE *fichier_reseau;
    fichier_reseau = fopen(pc->nom_fichier_reseau,"r");
    char* buf,buf2,buf3;
    //while (fscanf(fichier_reseau,"%s %s %s",buf,buf2,buf3) == 3)
    {
        
    }
    
}
