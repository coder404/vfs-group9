/* This file contains the functions to create VFS , mount and unmount of VFS */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/BinarySearchTreeFile.h"
#include"../include/HashTableFile.h"


/* Function to create the VFS */

int create_vfs(char fs_name[20], int size)
{
        FILE *fp;
        fp = fopen(fs_name,"rb");
      
        int status=1; 
        if(NULL==fp)  
        {
        	/* If the file does not exist it is created */
        	
        	/* set the header variables for the VFS */
    		strcpy(meta_data.fs_name, fs_name);
    		
    		/* #used fds is set to 0 at the start */
		meta_data.used_fd = 0;
		
		/* max fds is calculated based on the size of the filesystem and the block_size */
	//	meta_data.max_fd = size/BLOCK_SIZE;
		meta_data.max_fd = 100;
	//	printf("used_fd %d max_fd %d fs_size %d\n",  meta_data.used_fd, meta_data.max_fd,  meta_data.fs_size);
		
		meta_data.fs_size=size;
	//	printf("used_fd %d max_fd %d fs_size %d\n",  meta_data.used_fd, meta_data.max_fd,  meta_data.fs_size);
          
          	 /* the free list array is declared as a global variable in MainHeaderFile.h */
          	/* the fd array is allocated memory via malloc */
          	/* size of fd array = #max fd * size of struct file_desc */
                fd_arr = malloc(meta_data.max_fd*sizeof(file_desc));
                
                /* the free list array is allocated memeory and all the elements of the array is set to 0 */
                /* the free list array is declared as a global variable in MainHeaderFile.h */
		free_list = calloc(meta_data.max_fd,sizeof(int));
		
		int i;
		
		/* open the filesystem to write the header file, fd array and free list array */
                fs = fopen(fs_name, "wb+");
                
               	if( NULL == fs )
		{
		    /* If the file cannot be opened to write error status returned */
		   // exit(1);
		   status = 0;
		}
		
		/* Write the header in the VFS file */
                fwrite(&meta_data, sizeof(HEADER), 1, fs);
              
                /* Write the fd array in the VFS file */
                fwrite(fd_arr, sizeof(file_desc), 10, fs);
   
                /* Write the free list data in the VFS file */
                fwrite(free_list, sizeof(int), meta_data.max_fd, fs);
   
		/* Allocate the memory for the blocks and write each block into the vfs file */
		/*#blocks = max fd */
               void  *buffer;
               buffer = malloc(1024);
      
               for (i=0; i<10; i++)
                {
                   
                        fwrite(buffer, 1024,1, fs);
                        
                }
      		status =1;
                free(fd_arr);
                free(free_list);
                free(buffer);
                fclose(fs);
        }
        else
        {
                fclose(fp);
        }
        return status; 
}


/* Function to 

 the data structures - Nary tree, BST and hash tables on the memory */
int mount(char fs_name[20])
{
        fs = fopen(fs_name, "rb+");
      
        int status =1 ;
        if (fs==NULL) 
        {
             //   printf("MOUNT WAS UNSUCCESSFUL");
//		exit(1);
		/* If the vfs file can not be opened  status is set to 0 */
		return 
  		status =0 ;             
        }
        else
        {
        	
        	int index;
               /* Else if the VFS File is opened successfully then start the mounting */
               
		
		
		/* Read the header from the disk to the memory */
                fseek(fs, 0, SEEK_SET);
                
                fread(&meta_data, sizeof(HEADER), 1, fs);

		printf("After reading - used_fd %d max_fd %d fs_size %d\n",  meta_data.used_fd, meta_data.max_fd,  meta_data.fs_size);

		/* Allocate memory to the fd array and free list array */
                fd_arr = (file_desc*)malloc(meta_data.max_fd*sizeof(file_desc));
                free_list = malloc(meta_data.max_fd*sizeof(int));

		/* Set the file pointer to point to end of header */
		/* Read fd array data into the memory from the disk */
                fseek(fs, sizeof(HEADER), SEEK_SET);
                fread(fd_arr, sizeof(file_desc), meta_data.max_fd, fs);
                
                
            /* Set the file pointer to end of the fd array */
		/* Read free list array data into the memory from the disk*/
		fseek(fs, sizeof(file_desc)*meta_data.max_fd, SEEK_SET);
                fread(free_list, sizeof(int), meta_data.max_fd, fs);
		
		fclose(fs);
		/* Call the functions to create the data structures */
		
		/* Code for mounting Nary tree */
               load_vfs_structure();
                
                /* code for mounting hash table */
                
                loadHashTable();
               
                
                /* code for mounting bst */
                load_bst_structure();
        }
        return status;
}


void load_vfs_structure()
{
        int status;
        int index = -1;
        fd_no = 0;
     
     printf("In loading of VFS\n");
	file_desc *fd;
	
	fd = (file_desc*)malloc(sizeof(file_desc));
	
        strcpy(fd->name,"/");
        
   //     printf("Copying root fd\n");
        
    //    fd->location = NULL;       
       	fd->attrib = 1;
        fd->fd_id = 0;
        fd->size = 0;
	
	Number_of_Files_Created = 0;
	Number_of_Files_Deleted = 0;
        VFS_Root = insert_in_nary(VFS_Root,"/",fd);
//        fd_no =  meta_data.used_fd;

printf("inserted root\n");
      
        for(index = 1; index <= meta_data.used_fd ; index ++)
        {
                     create_tree_in_nary(VFS_Root,fd_arr[index].location, fd_arr[index].name, fd_arr);
       //          printf("name of fd mounted in nary %d : %s\n",index, fd_arr[index].name);
                //check error with status value
                //printf("name : %s\n",fd_arr[index].name);
                //printf("Location : %s\n",fd_arr[index].location);

        }
    //    printf("\n");
}

void load_bst_structure()
{
	//printf("MOUNTING BST\n");
	int index;
	char *loc_bst; 
	loc_bst = malloc(100);
	
	for(index = 1; index <= meta_data.used_fd ; index ++)
        {
        
                printf("name of fd mounted in bst %d : %s\n",index, fd_arr[index].location);
          //   	printf("%s\n",loc_bst);
          
            strcpy(loc_bst,fd_arr[index].location);
          if(index != 0)
          {
          	strcat(loc_bst,"/");
          	strcat(loc_bst,fd_arr[index].name);  
          
          }
	else
		strcat(loc_bst,fd_arr[index].name);  
	
             
      
	memmove(loc_bst,loc_bst+1,strlen(loc_bst)); //to remove the '/' at the beginning
 //	printf("%s\n",loc_bst);
	BST_Root = insert_in_bst(BST_Root,loc_bst);
//	printf("\n");
	}

}

void loadHashTable() {

        int i;
        int size = meta_data.used_fd;        //denotes the number of files in the FileDescriptor array; 
        //change to max_fd laTER

        struct HashTable *Hash_Root=(struct HashTable *)malloc(sizeof(struct HashTable));
        createHashTable(Hash_Root);

        for(i = 1; i<size; i++)
        {
  //             printf("Mount Has : %s\n",fd_arr[i].name);
                hashInsert(Hash_Root, fd_arr[i].name);
        }

    //    printf("All the value from the file loaded into hash table successfully\n");
      //  return SUCCESS;
}




/* Function to unmount the Nary data structure - overwriting the fd array data in the vfs file */
int unmount()
{

// ???? CODE FOR CHECKING ERROR WHILE UNMOUNTING
//	printf("Unmount\n");
        int index;
	int status =1;
	//meta_data.used_fd = 5;
	printf("PRINTING THE TREE\n");
	print_subtree_nary(VFS_Root);
	printf("\n");
	printf("USED FD %d\n", meta_data.used_fd++);
	memset(fd_arr, '\0', meta_data.used_fd*sizeof(file_desc));
	for(index = 0; index <= meta_data.used_fd ; index ++)
        {
        
                printf("name : %s\n",fd_arr[index].name);
                printf("Location : %s\n",fd_arr[index].location);
	}
	
	// print_subtree_nary(VFS_Root);
	copy_tree_nary(VFS_Root);
	//meta_data.used_fd = fd_no+1;
	

meta_data.used_fd = Number_of_Files_Created - Number_of_Files_Deleted;

printf("USED FD : %d\n",meta_data.used_fd);
	for(index = 0; index <= meta_data.used_fd ; index ++)
        {
        
                printf("name : %s\n",fd_arr[index].name);
                printf("Location : %s\n",fd_arr[index].location);
                  printf("ID : %d\n",fd_arr[index].fd_id);
	}

//	printf("Copied into fd_arr\n");	
//	

	
	//traversal_nary(VFS_Root,0);
	//printf("Traversal done\n");
	
	/* Write the header file info into the vfs file */
        fseek(fs, 0, SEEK_SET);
        fwrite(&meta_data, sizeof(HEADER), 1, fs);

	

        fseek(fs, sizeof(HEADER), SEEK_SET);
        fwrite(fd_arr, sizeof(file_desc), meta_data.max_fd, fs);
        


	
	
        fseek(fs, sizeof(file_desc)*meta_data.max_fd, SEEK_SET);
        fwrite(free_list, sizeof(int), meta_data.max_fd, fs);

        free(fd_arr);
        free(free_list);
     //   free(VFS_Root);
        fclose(fs);
        
        return status;
}




int check_free_list(int num_blocks)
{
	int i;
	int start=0;
	
	for (i=0; i<meta_data.max_fd; i++)
        {
   //     printf("FREE_LIST[%d] = %d\n",i,free_list[i]);
	
		if (free_list[i]==1)
		{
			start=i+1;
			
		}
                if ((i-start)+1 == num_blocks) 
		{
			break;
		}
        }	
       return start;
}
