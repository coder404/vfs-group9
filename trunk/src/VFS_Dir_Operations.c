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


char * make_dir(char *parent_path, char *dir_name)
{
	//printf("Creation of directory\n");
	printf("calling mkdir .. n");
	file_desc *fd_node;
	//printf("USED FD = %d\n",fd_no);
	
	node *temp , *p;
	//char **temp1;
	int i=0;
	if(mountstate != 1)
 		return ERR_VFS_MAKEDIR_05;
	
	printf("MK DIR : %s  %s \n",parent_path,dir_name);
	if(parent_path[0] == '\0' || dir_name[0] == '\0')
		return ERR_VFS_MAKEDIR_00;
	
	if(strpbrk(dir_name,INVALID_CHARACTER) != NULL)
		return ERR_VFS_MAKEDIR_02;
	temp = search_nary(VFS_Root,parent_path);
	
	if(parent_path[strlen(parent_path) - 1] != '/')
//	if(strcmp(parent_path,VFS_Root->data) != 0)
	{
	strcat(parent_path,"/");
	strcat(parent_path,dir_name);
	}
	
	else
		strcat(parent_path,dir_name);	

	if((Number_of_fds_Created - Number_of_fds_Deleted) == meta_data.max_fd)
		return ERR_VFS_MAKEDIR_01;
	create_tree_in_nary(VFS_Root, parent_path, temp->data, temp->fd);
	
	printf("Inserted\n");
	
	char *loc_bst; 
	loc_bst = malloc(100);
      	
     	 strcpy(loc_bst , parent_path);
	memmove(loc_bst,loc_bst+1,strlen(loc_bst)); //to remove the '/' at the beginning
	
	BST_Root = insert_in_bst(BST_Root, loc_bst);
	
	printf("MKDIR : BST_ROOT : %s\n" , BST_Root -> data);
	
	temp = search_nary(VFS_Root,parent_path);
	printf("Search done!!\n");
	if(strcmp(temp->data,dir_name)==0)
	{
	printf("TEMP AFTER PATH IS %s\n",temp->data);
	
	return SUC_VFS_MAKEDIR_01;
	}
}


char * list_dir(char *dir_name,int flag , char *outputfile)
{
	node *temp;
	
	FILE *fp_dir;
	
	if(mountstate != 1)
 		return ERR_VFS_LISTDIR_03;
	if(dir_name[0] == '\0' || (isdigit(flag) != 0) || outputfile[0]=='\0')
		return ERR_VFS_LISTDIR_00;
		
	
	if(flag != 0 )
		if(flag != 1)
			return ERR_VFS_LISTDIR_02;
	
	
	fp_dir = fopen(outputfile,"a+");
	if(fp_dir == NULL)
		return ERR_VFS_LISTDIR_04;
	printf("Searching in BST...\n");
	struct bst *r ;
	//r = (struct bst *)malloc(10*sizeof(struct bst));
	
	printf("BST ROOT : %s\n",BST_Root->data);
	r = search_bst(BST_Root, dir_name);
	
	if(r->data == NULL)
		return ERR_VFS_LISTDIR_01;
	
  /*      if (strcmp(temp->data , VFS_Root->data )==0)
        {
          //      printf("No such file or directory\n");
                return ERR_VFS_LISTDIR_01;
        }
        */
        char *temp_dir;
	temp_dir = malloc(100);
	strcpy(temp_dir, "Listing of directories of : ");
	
	printf("temp_dir : %s \n", temp_dir);
	strcat(temp_dir,dir_name);
	
	temp = search_nary(VFS_Root,dir_name);
	
	//fputs(temp_dir,fp_dir);
	fputs("\n****************************\n",fp_dir);
        if (flag == 0)
        	print_arr(temp,fp_dir);
        //print_dir_tree(temp,0);
        
        if(flag == 1)
        	print_subtree_nary(temp,fp_dir);
        
        fputs("\n****************************\n",fp_dir);
	fclose(fp_dir);
        
        return SUC_VFS_LISTDIR_01;

}

char * delete_dir(char *dir_path)
{

// check for validity of dir name - return ERR_VFS_DELETEDIR_03 


 // search for the path - if not found return ERR_VFS_DELETEDIR_01
 	
 	if(mountstate != 1)
 		return ERR_VFS_DELETEDIR_04;
	node * temp;
	
	if(dir_path[0] == '\0')
		return ERR_VFS_DELETEDIR_00;
	
	struct bst *r ;
	//r = (struct bst *)malloc(10*sizeof(struct bst));
	
	printf("BST ROOT : %s\n",BST_Root->data);
	r = search_bst(BST_Root, dir_path);
	
	if(NULL == r)
	return ERR_VFS_DELETEDIR_01;
	
	temp = search_nary(VFS_Root,dir_path);

/*	if (strcmp(temp->data , VFS_Root->data )==0)
        {
            //    printf("No such file or directory\n");
                return ERR_VFS_DELETEDIR_01;
        }*/
        
        
     //   if(NULL == temp)
       // 	 return ERR_VFS_DELETEDIR_01;
	
	
	// printf("search done \n");
 //check if dir has a child - If yes return ERR_VFS_DELETEDIR_02
 	if(temp->child != NULL)
 	{
 	return ERR_VFS_DELETEDIR_02;
 	}
 	
// 	printf ("%s\n ----- \n",temp->data);
 //	printf("\nMAKE DIR : decrement used fd \n");
  	Number_of_fds_Deleted++;
 	
 	
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

if(mountstate != 1)
 		return ERR_VFS_MOVEDIR_08;

	if(strlen(src_dir_path) ==  0 || strlen(dest_dir_path) == 0)
		return ERR_VFS_MOVEDIR_00;



	struct bst * temp;
	
	printf("BST ROOT : %s\n",BST_Root->data );
	temp=search_bst(BST_Root,dest_dir_path);
	
	if(temp == NULL)
	return ERR_VFS_MOVEDIR_02;
	
	struct bst * temp_b;
	
	temp_b=search_bst(BST_Root,src_dir_path);
	//CHECK!!!!! AND UNCOMMENT!
	
	if(temp_b == NULL)
		return ERR_VFS_MOVEDIR_01;	
	
	
	node *temp1;
	node *temp2;
	
	temp1 = search_nary(VFS_Root,src_dir_path);
	printf("SRC : %s\n",temp1->data);

	
	if(temp1->fd->attrib == FILE_ATTRIBUTE)
		return ERR_VFS_MOVEDIR_04;
	

	temp2 = search_nary(VFS_Root,dest_dir_path);
	printf("DEST : %s\n",temp2->data);
	
	if(temp2->fd->attrib == FILE_ATTRIBUTE)
		return ERR_VFS_MOVEDIR_07;
	char * status;
	
		
		
	status = move_nodes_dir(temp1,temp2);
	
	return status;	
	
}


