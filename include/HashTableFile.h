// prototype for linked list each node

#define MAXBUCKETS 26
#define SUCCESS 1
#define RECORD_NOT_INSERTED 3
#define RECORD_NOT_DELETED 4
#define UNABLE_TO_OPEN_FILE 10
#define EMPTY_FILE 5
struct LinkedListNode
{
        char *key;
       
       
        struct LinkedListNode *next;
        
        
};


/* This function inserts in sorted order */
int insertIntoLinkedList(struct LinkedListNode **head, char *fileName);


/* This function deletes a node from the Linked List */
int deleteFromLinkedList(struct LinkedListNode **head, char *fileName);

/* This function searches for a given node in the Linked List */
int searchLinkedList(struct LinkedListNode **head, char *fileName);



struct HashTable
{
        struct LinkedListNode *buckets[MAXBUCKETS] ;
};

/* This function loads the hash-table from the file on to the main memory. */
//void loadHashTable();

/* This function allocates memory and initializes the hash-table.*/
void createHashTable(struct HashTable *hash);

/* This function inserts a given key in a hash-table. */
int hashInsert(struct HashTable *hash, char *fileName);

/* This function deletes a given key in a hash-table. */
int hashDelete(struct HashTable *hash, char *fileName);

/* This function calculates the key to a corresponding value in a hash-table. */
int calcHash(char *fileName);

/* This funtion searches the hash-table */
void hashSearch(struct HashTable *hash, char *fileName);



struct HashTable *Hash_Root;
