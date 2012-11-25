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

	
      	fseek(fp,0,SEEK_END);
      	size=ftell(fp);
      	printf("the file's length is %1dB\n",size);
      	
   	
    
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
        
        temp = search_nary(VFS_Root,f_path);
     	fd = add_fd(temp, f_name , FILE_ATTRIBUTE, start);
     
     printf("Start block : %d\n", fd->start_block);
     
     	insert_nodes_nary(temp , fd);
      
        free_list[start]=1;
        
     
	 fclose(fp);

        printf("\n");
     
     //	fclose(fs);
return SUC_VFS_ADDFILE_01;	
}

char* list_file(char *f_path,char *hd_path){

//printf("in list_file");

	FILE *fp1, *fp2;
	node *new;
	int file_size;
	int file_block;
	int file_os;
	char c;
	int i;
	char* file_type;
	
	file_type = strchr(f_path,'.');

	node *temp;
	temp = search_nary(VFS_Root,f_path);

	if(*(file_type+1)!='t')
		return ERR_VFS_LISTFILE_02 ;

	else if(strlen(hd_path) == 0)
		return ERR_VFS_LISTFILE_00;
	
	else if(strlen(f_path) == 0)
		return ERR_VFS_LISTFILE_00;
	
	else if(temp==NULL)
		return  ERR_VFS_LISTFILE_01;
	
//ERR_VFS_LISTFILE_02 "OUTPUT_FILE_PATH_NOT_FOUND" how?

	else{

		new = search_nary(VFS_Root,f_path);  
		file_size = new->fd->size;
		file_block = new->fd->start_block;
		file_os = OFFSET + (file_block*BLOCK_SIZE);
			
		//strcat(hd_path,"//ListFile.txt");
	
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

	r = search_nary(VFS_Root,f_path);

	if(strlen(hd_path) == 0)
		return ERR_VFS_LISTFILE_00;
	
	else if(strlen(f_path) == 0)
		return ERR_VFS_LISTFILE_00;

	else if(r == NULL)
		return ERR_VFS_UPDATEFILE_01;

//ERR_VFS_UPDATEFILE_04 "VFS not mounted"
//ERR_VFS_UPDATEFILE_03 "EXTERNAL_FILE_TOO_LARGE"
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
	temp = search_nary(VFS_Root, f_path);

        if (temp == NULL)
                 return ERR_VFS_REMOVEFILE_01;
      
	else if (temp == VFS_Root)
                return ERR_VFS_REMOVEFILE_01;
        
	else{

		delete_node_from_nary(temp);
		return SUC_VFS_REMOVEFILE_01;
	
}
}
