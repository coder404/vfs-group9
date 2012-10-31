/* This file contains the FILE operations - create/delete file/directory */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/BinarySearchTreeFile.h"

#define PRINT_VFS() printf("VFS ROOT DATA %s %p\n",VFS_Root->data, &(VFS_Root->data))

void  create_file(char* f_path, char f_name[], char data[])
{



printf("\nCREATION OF FILE\n");
	int flag=0;
		int i;
	
	 if(strcmp(f_path,"/")!=0)
        {
            	strcat(f_path,"/");
        }
        strcat(f_path,f_name);
/*	for(i = 0; i<=meta_data.used_fd ; i++)
	{
		if(strcmp(fd_arr[i].location,f_path)==0)
		{
			flag =1;
			
		}
	}
*/
printf("Create file  1 BST Root : %s\n",BST_Root->data);

	char *ser_bst; 
	ser_bst = malloc(100);
	strcpy(ser_bst,f_path);
	memmove(ser_bst,ser_bst+1,strlen(ser_bst)); //to remove the '/' at the beginning
	//struct bst *temp;
	int temp;
	//temp=(struct bst *)malloc(sizeof(struct bst));

	printf("Create file BST Root : %s\n",BST_Root->data);
	
	temp=search_bst(BST_Root,ser_bst);
	
	printf("Create file BST Root : %s\n",BST_Root->data);
	
//	free(ser_bst);
	if(temp!=1)
	{
	printf("\ntemp is null\n");
	
        int size,start;
        size = strlen(data);
	
	int num_blocks = ceil((double)size/BLOCK_SIZE);
		      
        start = check_free_list(num_blocks);
           
        int offset = OFFSET + start*BLOCK_SIZE;
        fseek(fs, offset, SEEK_SET);
        fwrite(data,  size, 1, fs);
	free_list[start]=1;
	
	file_desc *fd_node;
	fd_node = (file_desc*)malloc(10*sizeof(file_desc));
       // strcpy(fd_node.name, f_name);
        strcpy(fd_node->name, f_name);
       printf("file name copied\n");
        
     //   printf("fd location : %s\n",f_path);
       // strcpy(fd_node.location , f_path); 
        strcpy(fd_node->location , f_path); 
    //    fd_node.size = size;
        fd_node->size = size;
	//PRINT_VFS();
	
	//fd_node.start_block = start;
	fd_node->start_block = start;
    //      strcpy(fd_node.type,"file");
          strcpy(fd_node->type,"file");
          fd_node->fd_id = meta_data.used_fd;
          
          printf("FD ID : %d\n\n",fd_node->fd_id);
       // printf("Call insert_nodes_nary - %s , %d\n",fd_node.location, meta_data.used_fd);
	//printf("Used fd %d\n",meta_data.used_fd);
	
	printf("Insert nodes\n");
	VFS_Root = insert_nodes_nary(VFS_Root, fd_node->location, fd_node->name, fd_node);
	 printf("Node creation in BST\n");
	 
	char *loc_bst; 
	loc_bst = malloc(100);
	strcpy(loc_bst,fd_node->location);
	memmove(loc_bst,loc_bst+1,strlen(loc_bst)); //to remove the '/' at the beginning
	BST_Root = insert_in_bst(BST_Root,loc_bst);
	meta_data.used_fd++;
//	printf("BST ROOT %s\n", BST_Root->data);
        
//	fd_arr[meta_data.used_fd] = fd_node;
//	meta_data.used_fd++;
	}

/*	for(i = 0; i<meta_data.used_fd ; i++)
	{
		printf("FD[%d] : %s\n", i,fd_arr[i].location);
	}
	*/

	//print_tree_nary(VFS_Root);
	//PRINT_VFS();
	
	//To update FDs
	//update_fd(f_name,f_path,size,start,0); 
	//int status;
	//status = create_tree(VFS_Root,fd_arr[meta_data.used_fd-1].location);
//	printf("AFTER adding a file\n");
//	print_tree(VFS_Root);
}


void delete_file(char* f_path)
{
	int j,index;
	for(j=0;j<meta_data.used_fd;j++)
        	{
        		if(strcmp(fd_arr[j].location,f_path)==0)
 			{	
 				free_list[fd_arr[j].start_block]=0;  
 				index = j;
 				set_fd_values_null(fd_arr[j]);
 				//memset(&fd_arr[j], 0, sizeof(file_desc));
 				
 			}
 		}
 		
 	delete_node_from_nary(VFS_Root, f_path);
 /*	for(j=0;j<meta_data.used_fd;j++)
        	{
        		printf("%d : %s\n", j,fd_arr[j].location);
        	}*/
 //       delete_node(VFS_Root,f_path);
 	
}


void set_fd_values_null(file_desc fd)
{
//	fd.name = NULL;
//	fd.location = NULL;
}
	





/*int add_fd(char f_name[], char *f_path, int size, int start, int type)
{
//	printf("\nADD FD\n");
	file_desc fd;
        strcpy(fd.name, f_name);
        strcpy(fd.location , f_path); 
  //     printf("FD.LOCATION : %s\n",fd.location);
       fd.size = size;
	
        fd.start_block = start;
        fd.type = type;
//        printf("\nused fd %d\n",meta_data.used_fd);
        int i,index,flag =0 ;
        for (i=0;i<meta_data.used_fd;i++)
        {
        
  //      	printf("\n\nfd_arr[%d]: %s\n",i,fd_arr[i].name);
        	if(fd_arr[i].name == '\0')
        	{
    //    		printf("Adding here...\n");
        		fd_arr[i] = fd;
        		flag = 1;
        	}
        }
        
        if(flag == 0 )
        {
      //  printf("flag is zero");
        	fd_arr[meta_data.used_fd] = fd;
		meta_data.used_fd++;
	}
	return 0;
	
}
void update_fd(char f_name[],char *f_path,int size,int start,int type)
{
	char *token,*str1;
	int i,length,j;	
        char filename[20][20];
	memset(&filename, '\0', sizeof(char)*20*20);
	
	str1 = (char*)malloc(100*sizeof(char));
  
        strcpy(str1,f_path);
   	strcat(str1,"/");
   	strcat(str1,f_name);
        token = strtok(str1,"/");

        i= 0;
        while(token!=NULL)
        {
                strcpy(filename[i],token);
                token = strtok(NULL,"/");
                i++;
        }
        length = i;
               
        if(strcmp(fd_arr[0].name,filename[0])!=0)
        {
        	
        	strcpy(fd_arr[0].name,filename[0]);
//        	printf("fd_arr[0] : %s\n",fd_arr[0].name);
        	meta_data.used_fd = 1;
        }
        
        i=1;
        int flag=0;
        while(i < length)
        {
  //      	printf("\n Inside While \n");
        	strcat(str1,"/");
        	for(j=0;j<meta_data.used_fd;j++)
        	{
        		if(strcmp(fd_arr[j].name,filename[i])==0)
 			{
 				strcat(str1,filename[i]);
 				printf("%s",str1);
 				 if(strcmp(fd_arr[j].location,str1)!=0)
 				 {
 				 	add_fd(filename[i],str1,size,start,type);
 				 }
 				flag = 1;
 				break;			
 				
 			}
 			
        	}
        	if(flag != 1)
        	{      		
 			
 				strcat(str1,filename[i]);
        			add_fd(filename[i],str1,size,start,type);
    //    			printf("ADDED FD\n");
        			
        	}
        	i++;
        	flag = 0;
          }     

}
*/
