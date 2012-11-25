#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/BinarySearchTreeFile.h"
#include"../include/vfs_errorcodes.h"
#include"../include/vfs_successcodes.h"


//file_desc * add_fd(char *parent_path, char *dir_name , int fd_att)
file_desc * add_fd(node *parent, char *dir_name , int fd_att, int start)
{
int i;

	if(fd_att == DIR_ATTRIBUTE)
	{
	for (i=0; i<meta_data.max_fd; i++)
        {
   //     printf("FREE_LIST[%d] = %d\n",i,free_list[i]);
	
		if (free_list[i]==1)
		{
			start=i+1;
			
			
		}
                
        }	
	if( start == meta_data.max_fd)
	{
		//If the free list is not free return ERR_VFS_MAKEDIR_01 
//			printf("Insufficient space\n");
			return NULL ;
	}
	}
	/*if(strcmp(temp->name,VFS_Root) == 0)
	{
		
		printf("Create the path i.e each directory fd in nary \n");
	//If temp is VFS_Root then the path does not exist and should be created
	}*/	
	 
	 // create the node here
	 
	file_desc * fd_node;
	fd_node = (file_desc*)malloc(sizeof(file_desc));
	printf("PARENT PATH %s\n",parent->fd->location);
//	memmove(parent_path,parent_path+1,strlen(parent_path));    
//	printf("PARENT PATH %s\n",parent_path);  
	char  *str2;

	str2 = (char*)malloc(100*sizeof(char));
///////////////////////
strcpy(str2,parent->fd->location);
if(str2[strlen(str2) - 1] != '/')
//	if(strcmp(parent_path,VFS_Root->data) != 0)
	{
	strcat(str2,"/");
	strcat(str2,dir_name);
	strcat(str2,"/");
	}
	
	else{
		strcat(str2,dir_name);	
		strcat(str2,"/");
		}

printf("1 - STR 2 : %s\n",str2);

////////////////////////

/*			 if(strcmp(parent->fd->location,"/")==0)
			 {
			 strcpy(str2,parent->fd->location);
			// strcat(str2,parent->data);
			
		//	 strcat(str2,"/");
        		strcat(str2,dir_name);  
        		 printf("1 - STR 2 : %s\n",str2);
			 }
			 
                        else  if((strcmp(parent->fd->location,"/")!=0) && (strcmp(parent->data,VFS_Root->data)!=0)){
                        	 strcpy(str2,parent->fd->location);
                        	 
                        	strcat(str2,"/");
                        //	 strcat(str2,parent->data);
                        //	 	strcat(str2,"/");
        			strcat(str2,dir_name);  
                        printf("2 - STR 2 : %s\n",str2);
				
                      }
                      
                      else if(strcmp(parent->data,VFS_Root->data)==0) {
                      	strcpy(str2,"/");
                      	strcat(str2,dir_name);  
                      	printf("3 - STR 2 : %s\n",str2);
                      	}
*/
        
              
	strcpy(fd_node->name, dir_name);
	strcpy(fd_node->location , str2); 
       
	fd_node->start_block = start;
       // fd_node->fd_id = meta_data.used_fd;
                printf("Increment fd_no %d ", Number_of_fds_Created);
       Number_of_fds_Created++;
     printf("to %d\n",Number_of_fds_Created);
              
        fd_node->fd_id = Number_of_fds_Created;
        
    
        fd_node->attrib = fd_att;
//        fd.attrib = fd.attrib | DIRECTORY;
        fd_node->size = 0;
        fd_node->start_block = start;
//        TREE_NODE *new = insert_child(temp, gettreenode(fd));// write based on narray
        
//        mark_modified(new->parent);//based on naary
//       printf("MARKED %s as %ld\n",new->fd.file_name,new->fd.size);

	return fd_node;
}


