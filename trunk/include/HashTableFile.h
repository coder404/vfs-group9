#ifndef HASHTABLEFILE_H
#define HASHTABLEFILE_H


struct ll_node
{
        char *data;
        char *path;
        struct ll_node *link;
};



struct hash_table
{
        struct ll_node *buckets[26] ;
};



struct hash_table * hashtable_create(struct hash_table *table);


int insert_in_hashtable(struct hash_table *table, char *fileName,char *fpath);


int delete_from_hashtable(struct hash_table *table, char *fileName,char *fpath);


int calculate_mapping(char *fileName);


int search_from_hashtable(struct hash_table *table, char *fileName,char * filepath);



struct hash_table *hash_root;
char * search_file(struct hash_table * hash_root ,char *filename, char *filepath);
#endif
