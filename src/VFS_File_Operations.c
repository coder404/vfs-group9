#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/BinarySearchTreeFile.h"
#include"../include/vfs_errorcodes.h"
#include"../include/vfs_successcodes.h"

char * copy_file(char *src_path, char *dest_path)
{
	node * src;
	node * dest;
	int src_start;
	int dest_start;
	int src_offset;
	int dest_offset;
	char *buffer = malloc(BLOCK_SIZE);
	struct bst * temp1;
	struct bst * temp2;
	
	temp1 = search_bst(BST_Root,src_path);
	
	if(temp1 == NULL)
		return ERR_VFS_COPYFILE_01;
	temp2 = search_bst(BST_Root,dest_path);	
	if(temp2 == NULL)
		return ERR_VFS_COPYFILE_02;	
	
	
	printf("Src path : %s\n",src_path);	
	src = search_nary(VFS_Root,src_path);
	printf("SRC NODE : %s\n" , src->data);
	/* IF src is null return error */
		
	dest = search_nary(VFS_Root,dest_path);
	
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

char *create_file(char *f_path, char *f_name, char *data_file)
{

	printf("in create");
	FILE *fp;
	node *temp;
	int size;
	struct bst *temp_bst;
	char *local_fpath;
	local_fpath = malloc(100);
	strcpy(local_fpath,f_path);
	printf("LOCAL PATH %s\n\n",local_fpath);
	//printf("f_path[strlen(f_path)-1 : %s\n", f_path[strlen(f_path)-1]);
	if(f_path[strlen(f_path) - 1] != '/')
//	if(strcmp(parent_path,VFS_Root->data) != 0)
	{
	
	strcat(local_fpath,"/");
	strcat(local_fpath,f_name);
	}
	
	else
		strcat(local_fpath,f_name);

//	strcpy(local_fpath,f_path);

	//if(f_path[strlen(f_path)] != "/")
	//strcat(local_fpath,"/");
//	strcat(local_fpath,f_name);
	
	printf("LOCAL PATH %s\n\n",local_fpath);
	temp_bst = search_bst(BST_Root,local_fpath);
	
	
       fp = fopen(data_file,"rb");
	
      	fseek(fp,0,SEEK_END);
      	size=ftell(fp);
	fclose(fp);

	if(size>=1024)
      	return ERR_VFS_ADDFILE_06;

	if(strlen(f_path) == 0)
		return ERR_VFS_ADDFILE_00;
	else if(strlen(f_name) == 0)
		return ERR_VFS_ADDFILE_00;
	else if(strlen(data_file) == 0)
		return ERR_VFS_ADDFILE_00;

	else if(temp_bst != NULL)
		return ERR_VFS_ADDFILE_03; 	  

	//else if((meta_data.used_fd) == (meta_data.max_fd))
	//	return ERR_VFS_ADDFILE_04;

	else if(strpbrk(f_name,INVALID_CHARACTER) != NULL)
		return  ERR_VFS_ADDFILE_02;

//cannot write to file????
	else {
	 fs = fopen(meta_data.fs_name, "rb+");
        
        // Add to check if node exists
        
        FILE *fp,*fp1;
	fp = fopen(data_file,"rb");
        int start;
        
        char ch;
                	  
     	fseek(fp,0,SEEK_SET);

 	void *buffer;
	buffer = malloc(size);
   	int num_blocks = ceil((double)size/BLOCK_SIZE);
		      
        start = check_free_list(num_blocks);
             printf("start : %d\n", start);
        if((Number_of_fds_Created - Number_of_fds_Deleted) == meta_data.max_fd)
		return ERR_VFS_ADDFILE_04;

     if(1 != fread(buffer,size,1,fp))
    	{
        	//printf("\n fread() failed\n");
        //	return ERR_VFS_ADDFILE_01;
       
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
     
     	char *buffer1;
     	buffer1 = malloc(1024);
    	fread(buffer1, size , 1, fs);
    	
    	printf("\n The bytes read are [%s]\n",buffer1);
     
    //    node *temp;
        file_desc *fd;
        temp_bst = search_bst(BST_Root,f_path);
        
        if(temp_bst == NULL){
        create_tree_in_nary(VFS_Root, f_path,DIR_ATTRIBUTE);
        }
        temp = search_nary(VFS_Root,f_path);
        
     	fd = add_fd(temp, f_name , FILE_ATTRIBUTE, start);
     
     printf("Start block : %d\n", fd->start_block);
     
     	insert_nodes_nary(temp , fd);

	//char *name_bst1 = malloc(100);
	//strcpy(name_bst1,f_path);
	//strcat(name_bst1,"/");
	//strcat(name_bst1,f_name);
	memmove(local_fpath,local_fpath+1,strlen(local_fpath)); //to remove the '/' at the beginning
        insert_in_bst(BST_Root, local_fpath);
       
printf("BST_Root is:%s\n",BST_Root->data);

	free_list[start]=1;
             
	 fclose(fp);
        printf("\n");     
	return SUC_VFS_ADDFILE_01;	
	}
	
}

char* list_file(char *f_path,char *hd_path){

	FILE *fp1, *fp2;
	node *new;
	int file_size;
	int file_block;
	int file_os;
	char c;
	int i;
	char* file_type;
	
	file_type = strchr(f_path,'.');

	struct bst *temp;
	temp = search_bst(BST_Root,f_path);
	printf("data of temp is:%s\n",temp->data);
	inorder (BST_Root);

	if(*(file_type+1)!='t')
		return ERR_VFS_LISTFILE_02 ;

	else if(strlen(hd_path) == 0)
		return ERR_VFS_LISTFILE_00;
	
	else if(strlen(f_path) == 0)
		return ERR_VFS_LISTFILE_00;
	
	else if((temp->data) == NULL)
		return  ERR_VFS_LISTFILE_01;
	

	else{

		new = search_nary(VFS_Root,f_path);  
		file_size = new->fd->size;
		file_block = new->fd->start_block;
		file_os = OFFSET + (file_block*BLOCK_SIZE);
				
		void *buffer  = malloc(1024);
		fp2 = fopen(hd_path,"w");	
		
		fp1 = fopen(meta_data.fs_name,"r"); 
		fseek(fp1,file_os,SEEK_SET);
			fread(buffer,1024,1,fp1);
	
		for(i=0;i<1024;i++){
			c=*((char *)(buffer+i*sizeof(char)));
			putc(c,fp2);
		}		
		
		fclose(fp1);
		fclose(fp2);
		return SUC_VFS_LISTFILE_01;
	}
}

// To update the contents of file specified in VFS to the data in file in harddisk

char* update_file(char* f_path, char* hd_path){              //p1:VFS file path & p2:hard disk file path

	FILE *fp1,*fp2;
	void *buffer = malloc(1024);
	node *r;

	node *new;
	int file_size;
	int file_block;
	int file_os;
	char c;
	int size;

	r = search_nary(VFS_Root,f_path);

	fp2 = fopen(hd_path,"r");
	fseek(fp2,0,SEEK_END);
	size = ftell(fp2);
	fclose(fp2);

	if(size>=1024)
		return ERR_VFS_UPDATEFILE_03;
	
	else if(strlen(hd_path) == 0)
		return ERR_VFS_UPDATEFILE_00;
	
	else if(strlen(f_path) == 0)
		return ERR_VFS_UPDATEFILE_00;

	else if(r == NULL)
		return ERR_VFS_UPDATEFILE_01;

	else{

	new = search_nary(VFS_Root,f_path);  
	file_size = new->fd->size;
	file_block = new->fd->start_block;
	file_os = OFFSET + (file_block*BLOCK_SIZE);   //offset for file specified in f_path
		
	fp2 = fopen(hd_path,"r");	
	fread(buffer,1024,1,fp2);
	fclose(fp2);

	fp1 = fopen(meta_data.fs_name,"rb+");     //open vfs file
	fseek(fp1,file_os,SEEK_SET);	   //access file 
	fwrite(buffer,1024,1,fp1);            

	fclose(fp1);
	return SUC_VFS_UPDATEFILE_01;
	}

}

//Remove a file from VFS

char* remove_file(char *f_path)
{       

        node *temp;
	struct bst * temp2;
	temp2 = search_bst(BST_Root, f_path);
	temp = search_nary(VFS_Root, f_path);

        if (temp2 == NULL)
                 return ERR_VFS_REMOVEFILE_01;
      
	else if (temp == VFS_Root)
                return ERR_VFS_REMOVEFILE_01;
        
	else{

		delete_node_from_nary(temp);
		Number_of_fds_Deleted++;
		delete_bst(BST_Root,f_path);
		return SUC_VFS_REMOVEFILE_01;
	}
}

// export contents from file in vfs 
char* export_file(char *f_path,char *hd_path){


	FILE *fp1, *fp2;
	node *new;
	int file_size;
	int file_block;
	int file_os;
	char c;
	int i;
	char* file_type;
	
	struct bst *temp;
	temp = search_bst(BST_Root,f_path);
	new = search_nary(VFS_Root,f_path);  

	if(strlen(hd_path) == 0)
		return ERR_VFS_LISTFILE_00;
	
	else if(strlen(f_path) == 0)
		return ERR_VFS_LISTFILE_00;
	
	else if((temp->data) == NULL)
		return  ERR_VFS_LISTFILE_01;
	
	else if((new->fd->attrib) == DIR_ATTRIBUTE) 
		return ERR_VFS_EXPORTFILE_03;
	
	else{

		file_size = new->fd->size;
		file_block = new->fd->start_block;
		file_os = OFFSET + (file_block*BLOCK_SIZE);
				
		void *buffer  = malloc(1024);
		fp2 = fopen(hd_path,"w");	
		
		fp1 = fopen(meta_data.fs_name,"r"); 
		fseek(fp1,file_os,SEEK_SET);
			fread(buffer,1024,1,fp1);
	
		for(i=0;i<1024;i++){
			c=*((char *)(buffer+i*sizeof(char)));
			putc(c,fp2);
		}		
		
		fclose(fp1);
		fclose(fp2);
		return SUC_VFS_LISTFILE_01;
	}
}

char * move_file(char *src_path, char *dest_path)
{
	node * src;
	node * dest;
	int src_start;
	int dest_start;
	int src_offset;
	int dest_offset;
	char *buffer = malloc(BLOCK_SIZE);
	struct bst * temp1;
	struct bst * temp2;
	
	if(mountstate != 1)
		return ERR_VFS_MOVEFILE_06;
	if(strlen(src_path) == 0 || strlen(dest_path) == 0)
		return ERR_VFS_MOVEFILE_00;
	temp1 = search_bst(BST_Root,src_path);
	
	if(temp1 == NULL)
		return ERR_VFS_MOVEFILE_01;
	temp2 = search_bst(BST_Root,dest_path);	
	if(temp2 == NULL)
		return ERR_VFS_MOVEFILE_02;	
	
	
	printf("Src path : %s\n",src_path);	
	src = search_nary(VFS_Root,src_path);
	printf("SRC NODE : %s\n" , src->data);
	/* IF src is null return error */
		
	dest = search_nary(VFS_Root,dest_path);
	
	/* search nary for that node */
	
	
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
	delete_node_from_nary(src);
	printf("Deleted!\n");
	print_subtree_nary_test(VFS_Root);
	Number_of_fds_Deleted++;
	return SUC_VFS_MOVEFILE_01;
}
