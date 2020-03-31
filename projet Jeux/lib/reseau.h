#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include "../lib/blockchain.h"

typedef struct 
{
    int nom_pc;
    char *nom_fichier_reseau;
    int nb_pc;
}ordi;


void send_message_house_created(ordi *pc);
void read_file(ordi *pc);