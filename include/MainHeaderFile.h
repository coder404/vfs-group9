#ifndef MAINHEADERFILE_H
#define MAINHEADERFILE_H

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
        char type[6];
        char location[1000];
}file_desc;


#define BLOCK_SIZE 1024
#define OFFSET sizeof(HEADER)+(sizeof(file_desc)+sizeof(int))*meta_data.max_fd
FILE *fs;
HEADER meta_data;
file_desc *fd_arr;
int *free_list;

int mount(char fs_name[20]);
int create_vfs(char fs_name[20], int size);
void load_vfs_structure();
int check_free_list(int num_blocks);
int unmount();
void create_file(char* f_path, char f_name[], char data[]);
void delete_file(char* f_path);
void update_fd(char f_name[],char *f_path,int size,int start,int type);
file_desc add_fd(char f_name[], char *f_path, int size, int start, int type);
void set_fd_values_null(file_desc fd);
#endif
