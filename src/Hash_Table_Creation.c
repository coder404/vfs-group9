#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include"../include/MainHeaderFile.h"
#include"../include/HashTableFile.h"

int calculate_mapping(char *filename) {
        
        int hash_key = toascii(toupper(*filename))-65;
        
        
        return hash_key;
}


struct hash_table * hashtable_create(struct hash_table *table) {

        int i;
        
        for(i = 0; i < 26; i++) {
                table->buckets[i] = (struct ll_node*) malloc(sizeof(struct ll_node));
               
                table->buckets[i]->data = 65+i;
                table->buckets[i]->link = NULL;
                table->buckets[i]->path = NULL;
        }
	
        return table;
}


int insert_in_hashtable(struct hash_table *table, char *filename,char *fpath) {
	

        struct ll_node **head=NULL;
		struct ll_node *temp=NULL;
        struct ll_node *node=NULL;
        int hash_key;
        hash_key = calculate_mapping(filename);

		
		head=&(table->buckets[hash_key]);
        node = (struct ll_node *) malloc (sizeof(struct ll_node));
        
        node->data = filename;
        node->link = NULL;
        node->path=fpath;
        temp = *head;
      
			
    if(temp->link == NULL)  {
                temp->link = node;
                        
                return 1;
        }
        else if(strcmp(temp->link->data,node->data) > 0) {
                node->link = temp->link;
                temp->link = node;
                        
                return 1;
        }
        else {
                while(strcmp(temp->link->data,node->data) < 0 && temp->link->link != NULL) {
                        temp=temp->link;
                }
                if(temp->link->link == NULL && strcmp(temp->link->data,node->data) < 0) {
                        temp->link->link = node;
                                
						return 1;
                }
                else {
                        node->link = temp->link;
                        temp->link = node;
                        
						return 1;
                }
               
                return 0;
        }


}

int delete_from_hashtable(struct hash_table *table, char *filename,char *fpath) {
        
        struct ll_node *temp;
        struct ll_node **head;
        int hash_key;

        hash_key = calculate_mapping(filename);
      
       

       
        head=&(table->buckets[hash_key]);

        temp = *head;
        
		
		if(temp->link == NULL)  {
            
                return 4;
        }
        else {
                while(strcmp(temp->link->path,fpath)!=0 && temp!=NULL)
                {
             
                temp=temp->link;
                }
                if(strcmp(temp->link->path,fpath)==0) 
                {
              
                temp->link = temp->link->link;
                    
                return 1;
                }
                else{
                     
                        return 0;
                }
        }
                             
}

int search_from_hashtable(struct hash_table *table, char *filename,char *filepath) {
        
        struct ll_node *temp;
        struct ll_node **head;
		FILE *fp;
		fp=fopen(filepath,"w");
        int hash_key;
        hash_key = calculate_mapping(filename);
        head = &(table->buckets[hash_key]);

	
	
        temp = *head;
        
			if(temp->link == NULL)  {
				fputs("File not found",fp);
		
                return 0;
        }
        else {
                while(strcmp(temp->link->data,filename) != 0 && temp->link->link != NULL) {
        
                        temp=temp->link;
                }
                while( temp->link != NULL) {
                      
                      
		
			temp=temp->link;
			if(strcmp(temp->data,filename) == 0)
			{      
			        char *s=temp->path;
			        fputs(s,fp);
				
		        }
		
		
                }
                
				return 1;

        }
       
              
				return 0;
        fclose(fp);
	}
					

