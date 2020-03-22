typedef struct
{
	int index;
	char* author;
	int timestamp;
	int **map_house;
	int hash;
} Info;
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
void hash_index(int index);
void hash_author(char* author);
void hash_timestamp(int timestamp);
void hash_message(char* message);
void stock(char* file_name, Block* block, Blockchain* chain);
void proof_of_work(Block* block, Blockchain* Chains);

//Procedures de recuperation et sauvegarde de la blockchain
void save_write(char* file_name, Block* block);
Blockchain* get_save(char* file_name, Blockchain* Chains);
