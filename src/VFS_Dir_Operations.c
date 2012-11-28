/* This file contains the DIRECTORY operations 
	- makedir
	- deletedir
	- listdir
	- movedir
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/BinarySearchTreeFile.h"
#include"../include/vfs_errorcodes.h"

/* Function to create a directory in the filesystem */
char * make_dir(char *parent_path, char *dir_name)
{
	node *temp_nary;
	struct bst * temp_bst;
	int i=0;
	if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","makedir_FAILURE",ERR_VFS_MAKEDIR_05);
		return outputmsg;
	}
	
//	printf("MK DIR : %s  %s \n",parent_path,dir_name);
	if(parent_path[0] == '\0' || dir_name[0] == '\0')
	{
		sprintf(outputmsg,"%s %s","makedir_FAILURE",ERR_VFS_MAKEDIR_00);
		return outputmsg;
	}
	
	if(strpbrk(dir_name,INVALID_CHARACTER) != NULL)
	{
		sprintf(outputmsg,"%s %s","makedir_FAILURE",ERR_VFS_MAKEDIR_02);
		return outputmsg;
		
	}
	
	temp_nary = search_nary(VFS_Root,parent_path);
	
	if(parent_path[strlen(parent_path) - 1] != '/')
	{
		strcat(parent_path,"/");
		strcat(parent_path,dir_name);
		strcat(parent_path,"/");
	}
	
	else
	{
		strcat(parent_path,dir_name);	
		strcat(parent_path,"/");
	}
	
	temp_bst = search_bst(BST_Root,parent_path);
	
	if(temp_bst != NULL)
	{
		sprintf(outputmsg,"%s %s","makedir_FAILURE",ERR_VFS_MAKEDIR_03);
		return outputmsg;
	}

	if((Number_of_fds_Created - Number_of_fds_Deleted) == meta_data.max_fd)
	{
		sprintf(outputmsg,"%s %s","makedir_FAILURE",ERR_VFS_MAKEDIR_01);
		return outputmsg;
	}
	
	/* Create the new directory in the Nary tree */
	create_tree_in_nary(VFS_Root, parent_path,DIR_ATTRIBUTE);
	
	//printf("Inserted\n");
	
	/* Inserting the directory path in BST */
	char *loc_bst; 
	loc_bst = malloc(100);
      	
     	strcpy(loc_bst , parent_path);
	memmove(loc_bst,loc_bst+1,strlen(loc_bst)); //to remove the '/' at the beginning
	
	BST_Root = insert_in_bst(BST_Root, loc_bst);
	
	/* Testing whether the insert has happened successfully in the Nary tree */
	temp_nary = search_nary(VFS_Root,parent_path);
	//printf("Search done!!\n");
	if(strcmp(temp_nary->data,dir_name)==0)
	{
		//printf("TEMP AFTER PATH IS %s\n",temp_nary->data);
		sprintf(outputmsg,"%s","makedir_SUCCESS");
		return outputmsg;
	
	}

}

/* Function to list a directory contents depending on whether the listing is recursive
 	or not in the filesystem */
char * list_dir(char *dir_name,int flag , char *outputfile)
{
	node *temp;
	FILE *fp_dir;
	struct bst *r ;
	char *temp_dir;
	
	if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","listdir_FAILURE",ERR_VFS_LISTDIR_03);
		return outputmsg;	
 	}
	if(dir_name[0] == '\0' || (isdigit(flag) != 0) || outputfile[0]=='\0')
	{
		sprintf(outputmsg,"%s %s","listdir_FAILURE",ERR_VFS_LISTDIR_00);
		return outputmsg;
	}
	
	if(flag != 0 )
	{
		if(flag != 1)
		{
			sprintf(outputmsg,"%s %s","listdir_FAILURE",ERR_VFS_LISTDIR_02);
			return outputmsg;
		}	
	}
	
	fp_dir = fopen(outputfile,"a+");
	if(fp_dir == NULL)
	{
		sprintf(outputmsg,"%s %s","listdir_FAILURE",ERR_VFS_LISTDIR_04);
		return outputmsg;
	}
	//printf("Searching in BST...\n");
	if(dir_name[strlen(dir_name) - 1] != '/')
	{
		strcat(dir_name,"/");
	}

	//r = (struct bst *)malloc(10*sizeof(struct bst));
	
	//printf("BST ROOT : %s\n",BST_Root->data);
	
	r = search_bst(BST_Root, dir_name);
	
	if(r->data == NULL)
	{
		sprintf(outputmsg,"%s %s","listdir_FAILURE",ERR_VFS_LISTDIR_01);
		return outputmsg;
	}
  /*      if (strcmp(temp->data , VFS_Root->data )==0)
        {
          //      printf("No such file or directory\n");
                return ERR_VFS_LISTDIR_01;
        }
        */
        
	temp_dir = malloc(100);
	strcpy(temp_dir, "Listing of directories of : ");
	
	//printf("temp_dir : %s \n", temp_dir);
	strcat(temp_dir,dir_name);
	
	temp = search_nary(VFS_Root,dir_name);
	

	fputs("\n****************************\n",fp_dir);
        if (flag == 0)
        	print_arr(temp,fp_dir);
        //print_dir_tree(temp,0);
        
        if(flag == 1)
        	print_subtree_nary(temp,fp_dir);
        
        fputs("\n****************************\n",fp_dir);
	fclose(fp_dir);
        
        sprintf(outputmsg,"%s","listdir_SUCCESS");
	return outputmsg;

}

/* Function to delete a directory in the filesystem */
char * delete_dir(char *dir_path)
{

// check for validity of dir name - return ERR_VFS_DELETEDIR_03 


 // search for the path - if not found return ERR_VFS_DELETEDIR_01
 	node * temp;
 	struct bst *r ;
 	if(mountstate != 1)
 	{
 		sprintf(outputmsg,"%s %s","deletedir_FAILURE",ERR_VFS_DELETEDIR_04);
		return outputmsg;
 	}
 	if(dir_path[strlen(dir_path) - 1] != '/')
	{
	strcat(dir_path,"/");
	}
	
	
	if(dir_path[0] == '\0')
	{
		sprintf(outputmsg,"%s %s","deletedir_FAILURE",ERR_VFS_DELETEDIR_00);
		return outputmsg;
	}
	
	r = search_bst(BST_Root, dir_path);
	
	if(NULL == r)
	{
		sprintf(outputmsg,"%s %s","deletedir_FAILURE",ERR_VFS_DELETEDIR_01);
		return outputmsg;
	}
	
	temp = search_nary(VFS_Root,dir_path);

 	//check if dir has a child - If yes return ERR_VFS_DELETEDIR_02
 	if(temp->child != NULL)
 	{
 		sprintf(outputmsg,"%s %s","deletedir_FAILURE",ERR_VFS_DELETEDIR_02);
		return outputmsg;
 	}

  	Number_of_fds_Deleted++;

 	delete_node_from_nary(temp);
 	delete_bst(BST_Root, dir_path);
 	
 	r = search_bst(BST_Root, dir_path);
	
	if(NULL == r)
	{

	sprintf(outputmsg,"%s","deletedir_SUCCESS");
	return outputmsg;
	}

}

/* Function to move a directory from the source path to a destination path in the filesystem */
char * move_dir(char * src_dir_path , char * dest_dir_path)
{
	struct bst * temp;
	struct bst * temp_b;
	
	
	node *temp1;
	node *temp2;
	
	if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","movedir_FAILURE",ERR_VFS_MOVEDIR_08);
		return outputmsg;
	}
	if(src_dir_path[strlen(src_dir_path) - 1] != '/')
	{
		strcat(src_dir_path,"/");
	}

	if(dest_dir_path[strlen(dest_dir_path) - 1] != '/')
	{
		strcat(dest_dir_path,"/");
	}


	if(strlen(src_dir_path) ==  0 || strlen(dest_dir_path) == 0)
	{
		sprintf(outputmsg,"%s %s","movedir_FAILURE",ERR_VFS_MOVEDIR_00);
		return outputmsg;
	}

	///printf("BST ROOT : %s\n",BST_Root->data );
	temp=search_bst(BST_Root,dest_dir_path);
	
	if(temp == NULL)
	{
		sprintf(outputmsg,"%s %s","movedir_FAILURE",ERR_VFS_MOVEDIR_02);
		return outputmsg;
	}
	
	
	temp_b=search_bst(BST_Root,src_dir_path);
	//CHECK!!!!! AND UNCOMMENT!
	
	if(temp_b == NULL)
	{
		sprintf(outputmsg,"%s %s","movedir_FAILURE",ERR_VFS_MOVEDIR_01);
		return outputmsg;
	}
	
		
	temp1 = search_nary(VFS_Root,src_dir_path);
//	printf("SRC : %s\n",temp1->data);

	
	if(temp1->fd->attrib == FILE_ATTRIBUTE)
	{
		sprintf(outputmsg,"%s %s","movedir_FAILURE",ERR_VFS_MOVEDIR_04);
		return outputmsg;
	}

	temp2 = search_nary(VFS_Root,dest_dir_path);
	//printf("DEST : %s\n",temp2->data);
	
	if(temp2->fd->attrib == FILE_ATTRIBUTE)
	{
		sprintf(outputmsg,"%s %s","movedir_FAILURE",ERR_VFS_MOVEDIR_07);
		return outputmsg;
	}
	if(temp2->parent == temp1)
	{
		sprintf(outputmsg,"%s %s","movedir_FAILURE",ERR_VFS_MOVEDIR_06);
		return outputmsg;
	}				
	char *str;
	str = malloc(100);
	strcpy(str, temp2->fd->location);
	strcat(str, temp1->data);
	strcat(str,"/");
	//inorder(BST_Root);
	node * temp11;
	temp11 = search_nary(VFS_Root,str);
	printf("temp11-> data %s\n",temp11->data);
	if(strcmp(temp11->data,temp1->data)==0)
	{
		sprintf(outputmsg,"%s %s","movedir_FAILURE",ERR_VFS_MOVEDIR_05);
		return outputmsg;
	}
	move_nodes_dir(temp1,temp2);
	
	sprintf(outputmsg,"%s","movedir_SUCCESS");
	return outputmsg;
	
}


