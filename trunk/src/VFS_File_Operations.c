#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/HashTableFile.h"
#include"../include/BinarySearchTreeFile.h"
#include"../include/vfs_errorcodes.h"


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
	
	if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","copyfile_FAILURE",ERR_VFS_COPYFILE_05);
		return outputmsg;
	}
	
	

	if(strlen(src_path)== 0 || strlen(dest_path) == 0)
	{
		sprintf(outputmsg,"%s %s","copyfile_FAILURE",ERR_VFS_COPYFILE_00);
		return outputmsg;
	}
	
	
	temp1 = search_bst(BST_Root,src_path);
	
	if(temp1 == NULL)
	{
		sprintf(outputmsg,"%s %s","copyfile_FAILURE",ERR_VFS_COPYFILE_01);
		return outputmsg;
	}

	temp2 = search_bst(BST_Root,dest_path);	
	if(temp2 == NULL)
	{
		sprintf(outputmsg,"%s %s","copyfile_FAILURE",ERR_VFS_COPYFILE_02);
		return outputmsg;
	}
	
	
	src = search_nary(VFS_Root,src_path);
	
		
	dest = search_nary(VFS_Root,dest_path);
	
	/* search nary for that node */
	
	
	if(src -> fd->attrib == DIR_ATTRIBUTE)
	{
		
		sprintf(outputmsg,"%s %s","copyfile_FAILURE",ERR_VFS_COPYFILE_03);
		return outputmsg;
	}

	src_start = src->fd->start_block;
	
	
	
	dest_start = dest->fd->start_block;
	
	
	
	src_offset = OFFSET + (src_start * BLOCK_SIZE);
	
	
	
	dest_offset = OFFSET + (dest_start * BLOCK_SIZE);
	
	fseek(fs, src_offset , SEEK_SET);
	
	fread(buffer, BLOCK_SIZE, 1 ,fs);
	
	
	
	fseek(fs, dest_offset, SEEK_SET);
	
	
	fwrite(buffer, BLOCK_SIZE, 1, fs);
	fseek(fs, dest_offset , SEEK_SET);
	
	fread(buffer, BLOCK_SIZE, 1 ,fs);
	
	
	
	/* Update the FDs */
	
	dest->fd->size = src->fd->size;

	sprintf(outputmsg,"%s","copyfile_SUCCESS");
	return outputmsg;
}

char *create_file(char *f_path, char *f_name, char *data_file)
{

	
	FILE *fp;
	node *temp;
	int size;
	struct bst *temp_bst;
	char *local_fpath;
	
	if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","addfile_FAILURE",ERR_VFS_ADDFILE_07);
		return outputmsg;
	}
	
	local_fpath = malloc(100);
	strcpy(local_fpath,f_path);
	
	if(f_path[strlen(f_path) - 1] != '/')
	{
	
	strcat(local_fpath,"/");
	strcat(local_fpath,f_name);
	}
	
	else
		strcat(local_fpath,f_name);


	
	temp_bst = search_bst(BST_Root,local_fpath);
	
	if(strlen(f_path) == 0)
	{
		sprintf(outputmsg,"%s %s","addfile_FAILURE",ERR_VFS_ADDFILE_00);
		return outputmsg;
	}

	if(strlen(f_name) == 0)
	{
		sprintf(outputmsg,"%s %s","addfile_FAILURE",ERR_VFS_ADDFILE_00);
		return outputmsg;
	}

	if(strlen(data_file) == 0)
	{
		sprintf(outputmsg,"%s %s","addfile_FAILURE",ERR_VFS_ADDFILE_00);
		return outputmsg;
	}

	if(temp_bst != NULL)
	{
		sprintf(outputmsg,"%s %s","addfile_FAILURE",ERR_VFS_ADDFILE_03);
		return outputmsg;
	}

	
	if(strpbrk(f_name,INVALID_CHARACTER) != NULL)
	{
		sprintf(outputmsg,"%s %s","addfile_FAILURE",ERR_VFS_ADDFILE_02);
		return outputmsg;
	}


       fp = fopen(data_file,"rb");
	
      	fseek(fp,0,SEEK_END);
      	size=ftell(fp);
	fclose(fp);

	if(size>=1024)
	{
		sprintf(outputmsg,"%s %s","addfile_FAILURE",ERR_VFS_ADDFILE_06);
		return outputmsg;
	}


	else {
	
	
	inorder(BST_Root);
	
	 fs = fopen(meta_data.fs_name, "rb+");
        
      
        
        FILE *fp,*fp1;
	fp = fopen(data_file,"rb");
        int start;
        
        char ch;
                	  
     	fseek(fp,0,SEEK_SET);

 	void *buffer;
	buffer = malloc(size);
   	int num_blocks = ceil((double)size/BLOCK_SIZE);
		      
        start = check_free_list(num_blocks);
            
        if((Number_of_fds_Created - Number_of_fds_Deleted) == meta_data.max_fd)
		return ERR_VFS_ADDFILE_04;

     if(1 != fread(buffer,size,1,fp))
    	{
        	
    	}   
    
         fseek(fs,0,SEEK_SET);
        
   
       int offset ;
 
     	 offset= OFFSET + start*BLOCK_SIZE;
     	 
     	 
        fseek(fs, offset ,SEEK_SET);
     
     	fwrite(buffer, size, 1 , fs);
     	 fseek(fs, offset ,SEEK_SET);
     
     	char *buffer1;
     	buffer1 = malloc(1024);
    	fread(buffer1, size , 1, fs);
    	
    	
     
   
        file_desc *fd;
        
        temp_bst = search_bst(BST_Root,f_path);
        
        if(temp_bst == NULL){
        create_tree_in_nary(VFS_Root, f_path,DIR_ATTRIBUTE);
	makedir_bst(f_path);
        }
        temp = search_nary(VFS_Root,f_path);
        
     	fd = add_fd(temp, f_name , FILE_ATTRIBUTE, start);
     
    
     	insert_nodes_nary(temp , fd);
		free_list[start]=1;
	
	memmove(local_fpath,local_fpath+1,strlen(local_fpath)); //to remove the '/' at the beginning
	
        insert_in_bst(BST_Root, local_fpath);
       
	
	insert_in_hashtable(hash_root,f_name,local_fpath);
	
	 fclose(fp);
      
	sprintf(outputmsg,"%s","addfile_SUCCESS");
	return outputmsg;
    	
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
	if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","listfile_FAILURE",ERR_VFS_LISTFILE_04);
		return outputmsg;
	}
	file_type = strchr(f_path,'.');

	struct bst *temp;
	temp = search_bst(BST_Root,f_path);
	
	inorder (BST_Root);

	if(*(file_type+1)!='t')
	{
		sprintf(outputmsg,"%s %s","listfile_FAILURE",ERR_VFS_LISTFILE_02);
		return outputmsg;
	}

	else if(strlen(hd_path) == 0)
	{
		sprintf(outputmsg,"%s %s","listfile_FAILURE",ERR_VFS_LISTFILE_00);
		return outputmsg;
	}
	
	else if(strlen(f_path) == 0)
	{
		sprintf(outputmsg,"%s %s","listfile_FAILURE",ERR_VFS_LISTFILE_00);
		return outputmsg;
	}
		
	else if((temp->data) == NULL)
	{
		sprintf(outputmsg,"%s %s","listfile_FAILURE",ERR_VFS_LISTFILE_01);
		return outputmsg;
	}
	
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
		sprintf(outputmsg,"%s","listfile_SUCCESS");
		return outputmsg;

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

if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","updatefile_FAILURE",ERR_VFS_UPDATEFILE_04);
		return outputmsg;
	}
	r = search_nary(VFS_Root,f_path);

	fp2 = fopen(hd_path,"r");
	fseek(fp2,0,SEEK_END);
	size = ftell(fp2);
	fclose(fp2);

	if(size>=1024)
	{
		sprintf(outputmsg,"%s %s","updatefile_FAILURE",ERR_VFS_UPDATEFILE_03);
		return outputmsg;
	}

	else if(strlen(hd_path) == 0)
	{
		sprintf(outputmsg,"%s %s","updatefile_FAILURE",ERR_VFS_UPDATEFILE_00);
		return outputmsg;
	}
	
	else if(strlen(f_path) == 0)
	{
		sprintf(outputmsg,"%s %s","updatefile_FAILURE",ERR_VFS_UPDATEFILE_00);
		return outputmsg;
	}

	else if(r == NULL)
	{
		sprintf(outputmsg,"%s %s","updatefile_FAILURE",ERR_VFS_UPDATEFILE_01);
		return outputmsg;
	}

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
	sprintf(outputmsg,"%s","updatefile_SUCCESS");
	return outputmsg;

	}

}

//Remove a file from VFS

char* remove_file(char *f_path)
{       

        node *temp;
	struct bst * temp2;
	int i; 
        char *token,*str1;
        char filename[20][20];
      
       if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","removefile_FAILURE",ERR_VFS_REMOVEFILE_02);
		return outputmsg;
	}
        strcpy(str1,f_path);
		token = strtok(str1,"/");

        i= 0;
        
		temp2 = search_bst(BST_Root, f_path);
		temp = search_nary(VFS_Root, f_path);
	
        while(token!=NULL)
        {
                strcpy(filename[i],token);
                token = strtok(NULL,"/");
                i++;
        }

        if (temp2 == NULL)
	{
		sprintf(outputmsg,"%s %s","removefile_FAILURE",ERR_VFS_REMOVEFILE_01);
		return outputmsg;
	}     
 
	else if (temp == VFS_Root)
	{
		sprintf(outputmsg,"%s %s","removefile_FAILURE",ERR_VFS_REMOVEFILE_01);
		return outputmsg;
	}     
        
	else{

		delete_node_from_nary(temp);
		Number_of_fds_Deleted++;
		delete_bst(BST_Root,f_path);
		
		delete_from_hashtable(hash_root,filename[i-1],f_path);

		sprintf(outputmsg,"%s","removefile_SUCCESS");
		return outputmsg;

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
	if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","exportfile_FAILURE",ERR_VFS_EXPORTFILE_04);
		return outputmsg;
	}
	temp = search_bst(BST_Root,f_path);
	new = search_nary(VFS_Root,f_path);  

	if(strlen(hd_path) == 0)
	{
		sprintf(outputmsg,"%s %s","exportfile_FAILURE",ERR_VFS_EXPORTFILE_00);
		return outputmsg;
	}     
	
	else if(strlen(f_path) == 0)
	{
		sprintf(outputmsg,"%s %s","exportfile_FAILURE",ERR_VFS_EXPORTFILE_00);
		return outputmsg;
	}     
	
	else if((temp->data) == NULL)
	{
		sprintf(outputmsg,"%s %s","exportfile_FAILURE",ERR_VFS_EXPORTFILE_01);
		return outputmsg;
	}     
	
	else if((new->fd->attrib) == DIR_ATTRIBUTE) 
	{
		sprintf(outputmsg,"%s %s","exportfile_FAILURE",ERR_VFS_EXPORTFILE_03);
		return outputmsg;
	}     
	
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
		sprintf(outputmsg,"%s","exportfile_SUCCESS");
		return outputmsg;

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
	{
		sprintf(outputmsg,"%s %s","movefile_FAILURE",ERR_VFS_MOVEFILE_06);
		return outputmsg;
	}     
	
	if(strlen(src_path) == 0 || strlen(dest_path) == 0)
	{
		sprintf(outputmsg,"%s %s","movefile_FAILURE",ERR_VFS_MOVEFILE_00);
		return outputmsg;
	}     

	temp1 = search_bst(BST_Root,src_path);
	
	if(temp1 == NULL)
	{
		sprintf(outputmsg,"%s %s","movefile_FAILURE",ERR_VFS_MOVEFILE_01);
		return outputmsg;
	}     

	temp2 = search_bst(BST_Root,dest_path);	
	if(temp2 == NULL)
	{
		sprintf(outputmsg,"%s %s","movefile_FAILURE",ERR_VFS_MOVEFILE_02);
		return outputmsg;
	}     
	
		
	src = search_nary(VFS_Root,src_path);
	
	
	dest = search_nary(VFS_Root,dest_path);
	
	/* search nary for that node */
	
	
	src_start = src->fd->start_block;
	
	
	
	
	dest_start = dest->fd->start_block;
	
	
	
	src_offset = OFFSET + (src_start * BLOCK_SIZE);
	
	
	dest_offset = OFFSET + (dest_start * BLOCK_SIZE);
	
	fseek(fs, src_offset , SEEK_SET);
	
	fread(buffer, BLOCK_SIZE, 1 ,fs);
	
	
	fseek(fs, dest_offset, SEEK_SET);
	
	
	fwrite(buffer, BLOCK_SIZE, 1, fs);
	fseek(fs, dest_offset , SEEK_SET);
	
	fread(buffer, BLOCK_SIZE, 1 ,fs);
	
	
	
	/* Update the FDs */
	
	
	delete_from_hashtable(hash_root, src->data,src_path);
	insert_in_hashtable(hash_root, src->data,dest_path);

	dest->fd->size = src->fd->size;
	delete_node_from_nary(src);
	delete_bst(BST_Root,src_path);
	
	print_subtree_nary_test(VFS_Root);
	Number_of_fds_Deleted++;

	
	sprintf(outputmsg,"%s","movefilefile_SUCCESS");
	return outputmsg;

}


char *search_file(struct hash_table *hash_root,char *filename,char *filepath)
{
int i,j;
i=strlen(filename);
j=strlen(filepath);
if(mountstate != 1)
	{
		sprintf(outputmsg,"%s %s","searchfile_FAILURE",ERR_VFS_SEARCHFILE_02);
		return outputmsg;
	}   
if(i==0)
{
	sprintf(outputmsg,"%s %s","searchfile_FAILURE",ERR_VFS_SEARCHFILE_00);
	return outputmsg;
}

else if(j==0)
{
	sprintf(outputmsg,"%s %s","searchfile_FAILURE",ERR_VFS_SEARCHFILE_00);
	return outputmsg;
}
else
{
search_from_hashtable(hash_root,filename,filepath);//this function directly generates an output file
}
	sprintf(outputmsg,"%s","searchfile_SUCCESS");
	return outputmsg;

}

