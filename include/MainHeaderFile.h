#ifndef MAINHEADERFILE_H
#define MAINHEADERFILE_H


int mountstate;
char outputmsg[200];
 struct Block {
	int buffer;
};

typedef  struct
{
        char fs_name[20];
        int used_fd;
        int max_fd;
        int fs_size;
        
} HEADER;

typedef struct File_Descriptor
{
        char name[20];
        int fd_id;
        int start_block;
        int size;
        int attrib; // 0 - file ; 1- dir
        char type[6];
        char location[100];
}file_desc;

#define FILE_ATTRIBUTE 0
#define DIR_ATTRIBUTE 1
#define BLOCK_SIZE 1024
#define OFFSET sizeof(HEADER)+(sizeof(file_desc)+sizeof(int))*meta_data.max_fd

/* Global variables declared */

FILE *fs;     
HEADER meta_data; 
file_desc *fd_arr;
int *free_list;
int Number_of_fds_Deleted;
int Number_of_fds_Created;

/* Functions for the VFS Operations */

char * mount(char fs_name[20]);
char *create_vfs(char fs_name[20], int size);

struct bst * load_bst_structure();
struct hash_table * loadHashTable();

int check_free_list(int num_blocks);
char* unmount();

char * create_file(char* f_path, char f_name[], char data[]);
//void delete_file(char* f_path);
void update_fd(char f_name[],char *f_path,int size,int start,int type);

void set_fd_values_null(file_desc fd);
char * make_dir(char *parent_path, char *dir_name);
//file_desc * add_fd(char *parent_path, char *dir_name, int att);


char * copy_file(char *src_path, char *dest_path);
char* list_file(char *f_path,char *hd_path);
char* update_file(char* f_path, char* hd_path);
char* remove_file(char *f_path);
char* export_file(char *f_path,char *hd_path);
char * move_file(char *src_path, char *dest_path);
//char * search_file(struct hash_table * hash_root ,char *filename, char *filepath);
char * list_dir(char *dir_name,int flag , char *outputfile);
char * delete_dir(char *dir_path);
char * move_dir(char * src_dir_path , char * dest_dir_path);
#endif
