#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/BinarySearchTreeFile.h"
#include"../include/vfs_errorcodes.h"




file_desc * add_fd(node *parent, char *dir_name , int fd_att, int start)
{
int i;

if((Number_of_fds_Created - Number_of_fds_Deleted) == meta_data.max_fd)
	{
		sprintf(outputmsg,"%s","FILESYSTEM FULL");
		return outputmsg;
	}

	if(fd_att == DIR_ATTRIBUTE)
	{
	for (i=0; i<meta_data.max_fd; i++)
        {
  
	
		if (free_list[i]==1)
		{
			start=i+1;
			
			
		}
                
        }	
	if( start == meta_data.max_fd)
	{
	
	sprintf(outputmsg,"%s","FILESYSTEM FULL");
		return outputmsg;

	}
	}
	
	 
	file_desc * fd_node;
	fd_node = (file_desc*)malloc(sizeof(file_desc));
	memset(fd_node, '\0', sizeof(file_desc));
	

	char  *str2;

	str2 = (char*)malloc(100*sizeof(char));

strcpy(str2,parent->fd->location);
if(str2[strlen(str2) - 1] != '/' && fd_att == DIR_ATTRIBUTE)

	{
	strcat(str2,"/");
	strcat(str2,dir_name);
	strcat(str2,"/");
	}
	
	else if(fd_att == DIR_ATTRIBUTE){
		strcat(str2,dir_name);	
		strcat(str2,"/");
		}
	else if(fd_att == FILE_ATTRIBUTE){
		strcat(str2,dir_name);
		}	

              
	strcpy(fd_node->name, dir_name);
	strcpy(fd_node->location , str2); 
       
	fd_node->start_block = start;
      
               
       Number_of_fds_Created++;
    
              
        fd_node->fd_id = Number_of_fds_Created;
        
    
        fd_node->attrib = fd_att;

        fd_node->size = 0;
        fd_node->start_block = start;

	return fd_node;
}


