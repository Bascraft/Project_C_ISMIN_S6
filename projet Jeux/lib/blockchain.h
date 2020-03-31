typedef struct
{
	int index;
	char* author;
	int timestamp;
	char **map_house;
	Map house_info;
	int hash;
} Info;

typedef struct
{
	int total_rooms;
	int nb_kitchen;
	int nb_bedroom;
	int nb_WC;
} Map;

typedef struct Block
{
	Info* info;
	struct Block* previous_hash;
} Block;

typedef struct
{
	int size;
	Block* head;
	char* player;
} Blockchain;

//Procedures de bases des blockchains
void init_blockchain(Blockchain* chain);
void calc_new_hash(Block* block);
unsigned long hash_index(int index);
unsigned long hash_author(char* author);
unsigned long hash_timestamp(int timestamp);
void stock(char* file_name, Block* block, Blockchain* chain);
void proof_of_work(Block* block, Blockchain* Chains);

//Procedures de recuperation et sauvegarde de la blockchain
void save_write(char* file_name, Block* block);
Blockchain* get_save(char* file_name, Blockchain* Chains);
