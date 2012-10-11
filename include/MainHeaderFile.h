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
        int start_block;
        int size;
        int type;
        char location[1000];
}file_desc;

typedef struct node
{
        struct node * child;
        struct node * sibling;
        char data[20];
        file_desc fd;
}node;

node* VFS_Root;
#define BLOCK_SIZE 1024
#define OFFSET sizeof(HEADER)+(sizeof(file_desc)+sizeof(int))*meta_data.max_fd
FILE *fs;
HEADER meta_data;
file_desc *fd_arr;
int *free_list;

