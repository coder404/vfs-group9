//#ifndef MAINHEADERFILE_H
//#define MAINHEADERFILE_H

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


#define BLOCK_SIZE 1024
#define OFFSET sizeof(HEADER)+(sizeof(file_desc)+sizeof(int))*meta_data.max_fd

/* Global variables declared */

FILE *fs;     
HEADER meta_data; 
file_desc *fd_arr;
int *free_list;
int Number_of_Files_Deleted;
int Number_of_Files_Created;

/* Functions for the VFS Operations */

int mount(char fs_name[20]);
int create_vfs(char fs_name[20], int size);
void load_vfs_structure();
void load_bst_structure();
void loadHashTable();

int check_free_list(int num_blocks);
int unmount();

char * create_file(char* f_path, char f_name[], char data[]);
void delete_file(char* f_path);
void update_fd(char f_name[],char *f_path,int size,int start,int type);

void set_fd_values_null(file_desc fd);
char * make_dir(char *parent_path, char *dir_name);
//file_desc * add_fd(char *parent_path, char *dir_name, int att);


char * copy_file(char *src_path, char *dest_path);
//#endif
