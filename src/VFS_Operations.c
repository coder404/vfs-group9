/* This file contains the FILE operations - create/delete file/directory */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/BinarySearchTreeFile.h"
#include"../include/vfs_errorcodes.h"
#include"../include/vfs_successcodes.h"

#define FILE_ATTRIBUTE 0
#define DIR_ATTRIBUTE 1
#define PRINT_VFS() printf("VFS ROOT DATA %s %p\n",VFS_Root->data, &(VFS_Root->data))


char * copy_file(char *src_path, char *dest_path)
{
	node * src;
	node * dest;
	int src_start;
	int dest_start;
	int src_offset;
	int dest_offset;
	void *buffer = malloc(BLOCK_SIZE);
	
	printf("Src path : %s\n",src_path);	
	src = search_nary(VFS_Root,src_path);
	printf("SRC NODE : %s\n" , src->data);
	/* IF src is null return error */
	
	if(src == NULL )
	{
		printf("Src file missing \n");
		
		return ERR_VFS_COPYFILE_01;	
	}
			
	dest = search_nary(VFS_Root,dest_path);
	
	/* if dest is null create file */
	/* search nary for that node */
	
	
	if(src -> fd->attrib == DIR_ATTRIBUTE)
	{
		printf("Cannot copy dir to file \n");
		
		return ERR_VFS_COPYFILE_05;
		
	}
	src_start = src->fd->start_block;
	
	
	printf("Source start block is : %d\n", src_start);
	
	dest_start = dest->fd->start_block;
	
	printf("Dest start block is : %d\n", dest_start);
	
	src_offset = OFFSET + (src_start * BLOCK_SIZE);
	
	printf("Source offset is : %d\n", src_offset);
	
	dest_offset = OFFSET + (dest_start * BLOCK_SIZE);
	printf("dest offset is : %d\n", dest_offset);
	
	fseek(fs, src_offset , SEEK_SET);
	
	fread(buffer, BLOCK_SIZE, 1 ,fs);
	
	printf("\n The bytes read are [%s]\n",buffer);
	
	fseek(fs, dest_offset, SEEK_SET);
	
	
	fwrite(buffer, BLOCK_SIZE, 1, fs);
	fseek(fs, dest_offset , SEEK_SET);
	
	fread(buffer, BLOCK_SIZE, 1 ,fs);
	
	printf("\n The bytes read are [%s]\n",buffer);
	
	/* Update the FDs */
	
	dest->fd->size = src->fd->size;
	return SUC_VFS_COPYFILE_01;
}



char * make_dir(char *parent_path, char *dir_name)
{
	//printf("Creation of directory\n");
	printf("calling mkdir .. n");
	file_desc *fd_node;
	//printf("USED FD = %d\n",fd_no);
	
	node *temp , *p;
	//char **temp1;
	int i=0;
	
	temp = search_nary(VFS_Root,parent_path);
/*	if(temp == NULL)
	{
	
		
		create_dir_in_nary(VFS_Root,parent_path);	
		
	
	}*/
	
	if(temp == NULL)
	{
		strcpy(temp->data,VFS_Root->data);
		temp->fd = VFS_Root->fd;
	}
	else
		printf("TEMP B4 PATH IS %s\n",temp->fd->location);
		
	strcat(parent_path,"/");
	strcat(parent_path,dir_name);
	
		
	create_tree_in_nary(VFS_Root, parent_path, temp->data, temp->fd);
	
	printf("Inserted\n");
	
//	print_subtree_nary(VFS_Root);
	
	if(dir_name == NULL || parent_path == NULL)
		return ERR_VFS_MAKEDIR_01;
	//i++;
/*	while(parent_path[i] != '\0')
	{
	
		
			//return ERR_VFS_MAKEDIR_02;
	//If the characters are not valid then return ERR_VFS_MAKEDIR_02
	
	
	}*/
	
//	printf("Search for %s \n", parent_path);
	temp = search_nary(VFS_Root,parent_path);
	printf("TEMP AFTER PATH IS %s\n",temp->data);
	
//	file_desc * fd_node;
                                  
//        fd_node = add_fd(parent_path, dir_name,1);
	
	
//	insert_nodes_nary(temp,fd_node);
	
	/*if(temp == NULL){
	//fd_node = add_fd(parent_path, dir_name);
	create_tree_in_nary(VFS_Root, parent_path, dir_name, fd_node);

	}
	else if(temp != NULL)
	{f
	
	if(temp->parent != NULL)
//	printf("Parent of Temp : %s\n",temp->parent->data);
	
	if(temp->fd->attrib == FILE_ATTRIBUTE ) 
	{
//		printf("parent path is a file\n");
		return ERR_VFS_MAKEDIR_01;
	}
	
	
	if(temp->child != NULL)
	{
	//check if the node has this particular node existing
	
	p = temp->child;
//	printf("p ->data %s",p->data);
	while(p != NULL)
	{
		if(strcmp(p->data,dir_name) == 0)
		{
		// If the dir already exists return ERR_VFS_MAKEDIR_03
//			printf("dir already exists\n");
			return ERR_VFS_MAKEDIR_03;
		}
		
		else 
		{
			p = p->sibling;
		
		}
	}
		
	}
		fd_node = add_fd(parent_path, dir_name);
		VFS_Root = insert_nodes_nary(VFS_Root, fd_node->location, fd_node->name, fd_node);

//printf("MAKE DIR : increment used fd \n");	
//	meta_data.used_fd++;
	
	}*/
	return SUC_VFS_MAKEDIR_01;
}

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

			 if(strcmp(parent->fd->location,"/")==0)
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

        
              
	strcpy(fd_node->name, dir_name);
	strcpy(fd_node->location , str2); 
       
	fd_node->start_block = start;
       // fd_node->fd_id = meta_data.used_fd;
                printf("Increment fd_no %d ", Number_of_Files_Created);
       Number_of_Files_Created++;
     printf("to %d\n",Number_of_Files_Created);
              
        fd_node->fd_id = Number_of_Files_Created;
        
    
        fd_node->attrib = fd_att;
//        fd.attrib = fd.attrib | DIRECTORY;
        fd_node->size = 0;
        fd_node->start_block = start;
//        TREE_NODE *new = insert_child(temp, gettreenode(fd));// write based on narray
        
//        mark_modified(new->parent);//based on naary
//       printf("MARKED %s as %ld\n",new->fd.file_name,new->fd.size);

	return fd_node;
}


char * list_dir(char *dir_name,int flag , char *outputfile)
{
	node *temp;
	
	if(flag != 0 && flag != 1)
		return ERR_VFS_LISTDIR_02;
	//printf("Looking for %s\n", dir_name);
	//temp = search_nary(VFS_Root,dir_name);
        if (strcmp(temp->data , VFS_Root->data )==0)
        {
          //      printf("No such file or directory\n");
                return ERR_VFS_LISTDIR_01;
        }
        
        if (flag == 0)
        	{print_arr(temp,outputfile);}
        //print_dir_tree(temp,0);
        
        return SUC_VFS_LISTDIR_01;

}

char * delete_dir(char *dir_path)
{

// check for validity of dir name - return ERR_VFS_DELETEDIR_03 


 // search for the path - if not found return ERR_VFS_DELETEDIR_01
	node * temp;
	
temp = search_nary(VFS_Root,dir_path);

/*	if (strcmp(temp->data , VFS_Root->data )==0)
        {
            //    printf("No such file or directory\n");
                return ERR_VFS_DELETEDIR_01;
        }*/
        
        
        if(NULL == temp)
        	 return ERR_VFS_DELETEDIR_01;
	
	
	// printf("search done \n");
 //check if dir has a child - If yes return ERR_VFS_DELETEDIR_02
 	if(temp->child != NULL)
 	{
 	return ERR_VFS_DELETEDIR_02;
 	}
 	
// 	printf ("%s\n ----- \n",temp->data);
 //	printf("\nMAKE DIR : decrement used fd \n");
  	Number_of_Files_Deleted++;
 	
 	
 	//meta_data.used_fd--;
 	//meta_data.used_fd = meta_data.used_fd - (temp->no_children);
 	delete_node_from_nary(temp);
 	
 	
 //	printf("USED FD = %d\n",fd_no);
 

return SUC_VFS_DELETEDIR_01;

}

char * move_dir(char * src_dir_path , char * dest_dir_path)
{
//#define ERR_VFS_MOVEDIR_01 "CANNOT_FIND_SPECIFIED_SOURCEDIR"
//#define ERR_VFS_MOVEDIR_02 "CANNOT_FIND_SPECIFIED_DESTINATIONDIR"
//#define ERR_VFS_MOVEDIR_03 "SOURCE_PATH_MISSING"

//#define ERR_VFS_MOVEDIR_05 "DESTINATION_ALREADY_HAVE_SOURCE_DIR"

//#define ERR_VFS_MOVEDIR_04 "DESTINATION_PATH_MISSING"
if(dest_dir_path == NULL)
	return ERR_VFS_MOVEDIR_04;


	struct bst * temp;
	
//	printf("BST ROOT : %s\n",BST_Root->data );
	//temp=search_bst(BST_Root,dest_dir_path);
	
	//if(temp == NULL)
	//	return ERR_VFS_MOVEDIR_02;
	
	
	
	//temp=search_bst(BST_Root,src_dir_path);
	//if(temp == NULL)
	//	return ERR_VFS_MOVEDIR_01;	
	
	
	node *temp1;
	node *temp2;
	
	temp1 = search_nary(VFS_Root,src_dir_path);
	printf("SRC : %s\n",temp1->data);
	temp2 = search_nary(VFS_Root,dest_dir_path);
	printf("DEST : %s\n",temp2->data);
	char * status;
	
		
		
	status = move_nodes_dir(temp1,temp2);
	
	return status;	
	
}



char * listdir_recursive(char *dir_name, char *outputfile)
{
	node *temp;
	
//	printf("Looking for %s\n", dir_name);
	temp = search_nary(VFS_Root,dir_name);
        if (strcmp(temp->data , VFS_Root->data )==0)
        {
  //              printf("No such file or directory\n");
                return SUC_VFS_LISTDIR_01;
        }
        
        else
        	print_subtree_nary(temp);
        
    //    printf("\n");

 return SUC_VFS_LISTDIR_01;
}

char *create_file(char *f_path, char *f_name, char *data_file)
{
	node *temp;
//	char *full_path;
//	full_path = malloc(100);
	
//	strcpy(full_path , f_path);
//	strcat(full_path , "/");
//	strcat(full_path , f_name);
	
	//printf("FULL PATH %s\n", full_path);
	//temp = search_nary(VFS_Root,full_path);
//	printf("TEMP NODE IS : %s", temp->fd->name);
	
	
	/*if(strcmp(temp->fd->name,f_name) == 0 && temp->fd->attrib == FILE_ATTRIBUTE )
		return ERR_VFS_ADDFILE_03;
	
	else if (strcmp(temp->fd->location , f_path) !=0 )
		return ERR_VFS_ADDFILE_01;*/
		
	 fs = fopen(meta_data.fs_name, "rb+");
//	 if(strcmp(f_path,"/")!=0)
 //       {
  //          	strcat(f_path,"/");
    //    }
     //   strcat(f_path,f_name);
        
        // Add to check if node exists
        
        FILE *fp, *fp1;
        int start;
        
        char ch;
      
        int size;
      //  ch = malloc(100);
      
       fp = fopen(data_file,"rb");

	if(fp==NULL) {
      	return ERR_VFS_ADDFILE_01;
   	}
   	else {
      	fseek(fp,0,SEEK_END);
      	size=ftell(fp);
      	printf("the file's length is %1dB\n",size);
      	
   	}
    
     	fseek(fp,0,SEEK_SET);

 	void *buffer;
	buffer = malloc(size);
   	int num_blocks = ceil((double)size/BLOCK_SIZE);
		      
        start = check_free_list(num_blocks);
             printf("start : %d\n", start);
     	//int i = 0;
     if(1 != fread(buffer,size,1,fp))
    	{
        	//printf("\n fread() failed\n");
        	return ERR_VFS_ADDFILE_01;
       
    	}   
      // fread(buffer, 1 ,10,fp);
         fseek(fs,0,SEEK_SET);
        
     //   printf("\n The bytes read are [%s]\n",buffer);
       int offset ;
   //  start = 0 ;
     	 offset= OFFSET + start*BLOCK_SIZE;
     	 
     	 printf("Offset : %d\n", offset);
        fseek(fs, offset ,SEEK_SET);
     
     	fwrite(buffer, size, 1 , fs);
     	 fseek(fs, offset ,SEEK_SET);
     
     	void *buffer1;
     	buffer1 = malloc(1024);
    	fread(buffer1, size , 1, fs);
    	
    	printf("\n The bytes read are [%s]\n",buffer1);
     
    //    node *temp;
        file_desc *fd;
        
        temp = search_nary(VFS_Root,f_path);
     	fd = add_fd(temp, f_name , FILE_ATTRIBUTE, start);
     
     printf("Start block : %d\n", fd->start_block);
     
     	insert_nodes_nary(temp , fd);
     
     
       /*	fseek(fs,4000,SEEK_SET);
	fwrite(&buffer1, strlen(buffer1), 1 , fs);
	char  *buffer2;
        buffer2 = malloc(1024);
        printf("Fseek done for the 1st tym \n");
//	fseek(fs,0,SEEK_SET);	
	  fseek(fs,4000,SEEK_SET);
	if(5 != fread(buffer2,1,5,fs))
    	{
        printf("\n fread() failed\n");
       
   	}   
               
        printf("\n The bytes read are [%s]\n",buffer2);

 	/*start = 0;
        offset= 1550 + start*BLOCK_SIZE;
        printf("OFFSET : %d", offset);
        fseek(fs, offset ,SEEK_SET);   */    
        
        
   //   fwrite(buffer,1, size , fs);
    
      
        free_list[start]=1;
        
     
	 fclose(fp);

        printf("\n");
     
     //	fclose(fs);
return SUC_VFS_ADDFILE_01;	
}

/*void delete_file(char* f_path)
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
 		
 //	delete_node_from_nary(VFS_Root, f_path);
 /*	for(j=0;j<meta_data.used_fd;j++)
        	{
        		printf("%d : %s\n", j,fd_arr[j].location);
        	}*/
 //       delete_node(VFS_Root,f_path);
 	
//}

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
