#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"

node* VFS_Root;
#define BLOCK_SIZE 1024
#define OFFSET sizeof(HEADER)+(sizeof(file_desc)+sizeof(int))*meta_data.max_fd
FILE *fs;
HEADER meta_data;
file_desc *fd_arr;
int *free_list;

void load_vfs_structure()
{
        int status;
        int index;
     

        VFS_Root = insert(VFS_Root,meta_data.fs_name);
       
        for(index = 0; index < meta_data.used_fd ; index ++)
        {
                status = create_tree(VFS_Root,fd_arr[index].location);
                //printf("name : %s\n",fd_arr[index].name);
                //printf("Location : %s\n",fd_arr[index].location);

        }
        printf("\n");
}

void mount(char fs_name[20])
{
        fs = fopen(fs_name, "r+");
        if (fs==NULL) 
        {
                printf("MOUNT WAS UNSUCCESSFUL");
		exit(1);
               
        }
        else
        {
        	int index;
                printf("\nVFS File opened successfully through fopen()\n");
		printf("used_fd %d max_fd %d fs_size %d\n",  meta_data.used_fd, meta_data.max_fd,  meta_data.fs_size);

                fseek(fs, 0, SEEK_SET);
                fread(&meta_data, sizeof(HEADER), 1, fs);

		printf("After reading - used_fd %d max_fd %d fs_size %d\n",  meta_data.used_fd, meta_data.max_fd,  meta_data.fs_size);

                fd_arr = (file_desc*)malloc(meta_data.max_fd*sizeof(file_desc));
                free_list = malloc(meta_data.max_fd*sizeof(int));

                fseek(fs, sizeof(HEADER), SEEK_SET);
                fread(fd_arr, sizeof(file_desc), meta_data.max_fd, fs);
	
        	for(index = 0; index < meta_data.used_fd ; index ++)
        	{

                	printf(" name : %s\t",fd_arr[index].name);
	                printf("Location : %s\n",fd_arr[index].location); 
		}
                
		fseek(fs, sizeof(file_desc)*meta_data.max_fd, SEEK_SET);
                fread(free_list, sizeof(int), meta_data.max_fd, fs);
		
                load_vfs_structure(fs_name);
                //code for mounting hash table
                //code for mounting bst
        }
}

void create_vfs(char fs_name[20], int size)
{
        FILE *fp;
        fp = fopen(fs_name,"r");
        if(NULL==fp)
        {
                printf("FILE DOES NOT EXIST\n");
		//Fill the required meta_data information
		strcpy(meta_data.fs_name, fs_name);
		meta_data.used_fd = 0;
		meta_data.max_fd = size/BLOCK_SIZE;
		meta_data.fs_size=size;
		printf("used_fd %d max_fd %d fs_size %d\n",  meta_data.used_fd, meta_data.max_fd,  meta_data.fs_size);
                fd_arr = malloc(meta_data.max_fd*sizeof(file_desc));
		free_list = calloc(meta_data.max_fd,sizeof(int));
		int i;
       /*         for (i=0; i<meta_data.max_fd; i++)
                {
                        free_list[i]=0;
                }
*/
                fs = fopen(fs_name, "w+");
		if( NULL == fs )
		{
		    printf("COULD NOT OPEN/CREATE THE FILE TO WRITE");
		    exit(1);
		}
                fwrite(&meta_data, sizeof(HEADER), 1, fs);
                fwrite(fd_arr, sizeof(file_desc), meta_data.max_fd, fs);
                fwrite(free_list, sizeof(int), meta_data.max_fd, fs);

                void  *buffer = malloc(1024);
                for (i=0; i<meta_data.max_fd; i++)
                {
                        fwrite(buffer, 1024, 1, fs);
                }

                free(fd_arr);
                free(free_list);
                free(buffer);
                fclose(fs);
        }
        else
        {
                fclose(fp);
        }
        return;
}	



void unmount()
{
        int index;
        printf("UNMOUNT :");
        printf("\n");
        for(index = 0; index < meta_data.used_fd ; index ++)
        {
                //status = getName(VFS_Root,fd_arr[i].Location);
                printf(" name : %s\t",fd_arr[index].name);
                printf("Location : %s\n",fd_arr[index].location); 

        }
        printf("\n");


        fseek(fs, 0, SEEK_SET);
        fwrite(&meta_data, sizeof(HEADER), 1, fs);

        fseek(fs, sizeof(HEADER), SEEK_SET);
        fwrite(fd_arr, sizeof(file_desc), meta_data.max_fd, fs);

        fseek(fs, sizeof(file_desc)*meta_data.max_fd, SEEK_SET);
        fwrite(free_list, sizeof(int), meta_data.max_fd, fs);

        free(fd_arr);
        free(free_list);
        free(VFS_Root);
        fclose(fs);
}



/*void  create_file(char* f_path, char f_name[], char data[])
{
printf("CREATIION FILE\n");
        int size;
        size = strlen(data);
	printf("SIze of data = %d\n",size);
//        int num_blocks = size/BLOCK_SIZE;
int num_blocks = ceil((double)size/BLOCK_SIZE);	
        //int num_blocks;
	printf("NUM_BLOCKS : %d\n",num_blocks);
        int i, start=0;
	printf("MAX FD = %d\n", meta_data.max_fd);
        for (i=0; i<meta_data.max_fd; i++)
        {
        printf("FREE_LIST[%d] = %d\n",i,free_list[i]);
	
		if (free_list[i]==1)
		{
			start=i+1;
			printf("IF1\n");
		}
                if ((i-start)+1 == num_blocks) 
		{
			printf("IF2\n");
			break;
		}
        }
        int offset = OFFSET + start*BLOCK_SIZE;
        int start1=start;
        fseek(fs, offset, SEEK_SET);
        fwrite(data,  size, 1, fs);
	free_list[start1]=1;
	 printf("FREELIST[%d] = %d\n",start1,free_list[start1]);
       
     /* for (; start<start1+num_blocks;start++)
	{
         printf("START = %d\t",start);
	 free_list[start]=1;
	 printf("FREELIST = %d\n",free_list[start]);
	}
	*/
/*	printf("START BLOCK : %d\n",start1);

        file_desc fd;
        strcpy(fd.name, f_name);
	//fd.location =(char*) malloc(100*sizeof(char));
        strcpy(fd.location , f_path); 
       printf("FD.LOCATION : %s\n",fd.location);
       fd.size = size;
	
        fd.start_block = start1;
        fd.type = 0;
        fd_arr[meta_data.used_fd] = fd;
	meta_data.used_fd++;
	printf("FD ARRAY INDEX 0 : %s\n", fd_arr[0].location);
	printf("FD ARRAY INDEX 1 : %s\n", fd_arr[1].location);
	printf("FD ARRAY INDEX 2: %s\n", fd_arr[2].location);
}*/
