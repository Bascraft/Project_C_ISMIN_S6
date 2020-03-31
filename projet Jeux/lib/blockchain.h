typedef struct
{
	int index;
	char* author;
	int timestamp;
	char* name_house;
	int posx, posy;
	int hash;
} Info;

typedef struct
{
	Info* info;
	int previous_hash;
} Block;

typedef struct
{
	int size;
	Block* head;
	char* player;
} Blockchain;

typedef struct
{
	int nb_players;
	char* list;
} Arena;

//Procedures de bases des blockchains
void init_blockchain(Blockchain* chain);
void calc_new_hash(Block* block);
unsigned long hash_timestamp(int timestamp);
void stock(char* file_name, Block* block, Blockchain* Chains, Arena* Players);
int proof_of_work(Block* block, Blockchain* Chains, Arena* Players);

//Procedures de recuperation et sauvegarde de la blockchain
void save_write(char* file_name, Block* block);
Blockchain* get_save(char* file_name, Blockchain* Chains);
