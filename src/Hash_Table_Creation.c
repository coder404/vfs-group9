#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include"../include/MainHeaderFile.h"
#include"../include/HashTableFile.h"


int insertIntoLinkedList(struct LinkedListNode **head,char *data) {

        struct LinkedListNode *temp=NULL;
        struct LinkedListNode *node=NULL;

        node = (struct LinkedListNode *) malloc (sizeof(struct LinkedListNode));
        
        node->key = data;
        node->next = NULL;
        
        temp = *head;
        //printf("%c",temp->key);
		/* if(temp==NULL || strcmp(temp->key,data)>0)
		{
			*head=node;
			(*head)->next=temp;
			printf("inserted \n");
		}
        else { 
                while(temp != NULL) 
                {
                 
                if((strcmp(temp->key,data) <= 0)&&((temp->next==NULL || strcmp(temp->next->key,data)>0) ))
               
                {
                         node->next=temp->next;
                         temp->next=node;
                         printf("inserted1 \n");
                         return 1;
                }
                
                
					temp=temp->next;
				}
				return 0;
		} */ 
			
			
    if(temp->next == NULL)  {
                temp->next = node;
                return 1;
        }
        else if(strcmp(temp->next->key,node->key) > 0) {
                node->next = temp->next;
                temp->next = node;
                return 1;
        }
        else {
                while(strcmp(temp->next->key,node->key) < 0 && temp->next->next != NULL) {
                        temp=temp->next;
                }
                if(temp->next->next == NULL && strcmp(temp->next->key,node->key) < 0) {
                        temp->next->next = node;
                        return 1;
                }
                else {
                        node->next = temp->next;
                        temp->next = node;
                        return 1;
                }
                return 0;
        }

        
        
   // return 0;    
        
}

 int deleteFromLinkedList(struct LinkedListNode **head, char *filename) {
        
        struct LinkedListNode *temp;

        temp = *head;
        
		
		if(temp->next == NULL)  {
                return 0;
        }
        else {
                while(strcmp(temp->next->key,filename) != 0 && temp->next->next != NULL) {
                        temp=temp->next;
                }
                if(strcmp(temp->next->key,filename) == 0) {
                        temp->next = temp->next->next;
                       
                        return 1;
                }
                else {
//                        printf("%s :", temp->key);
                        return 0;
                }
        }
		
		
	}
	
	

        


int searchLinkedList(struct LinkedListNode **head, char *fileName) {
        struct LinkedListNode *temp;

        temp = *head;
        /* if(temp == NULL)  {
                return 0;
        }
        else {
                while(temp != NULL) {
					if(strcmp(temp->key,fileName)==0)
					{
						printf("file found");
						return 1;
					}
					else
					{
                        temp=temp->next;
					}
					
				}
				return 0;
			} */
			if(temp->next == NULL)  {
                return 0;
        }
        else {
                while(strcmp(temp->next->key,fileName) != 0 && temp->next->next != NULL) {
                        temp=temp->next;
                }
                if(strcmp(temp->next->key,fileName) == 0) {
                        return 1;
                }
                else {
                        return 0;
                }
        }
	}
					
                
       



void createHashTable(struct HashTable *hash) {

        int i;
        
        for(i = 0; i < MAXBUCKETS; i++) {
                hash->buckets[i] = (struct LinkedListNode*) malloc(sizeof(struct LinkedListNode));
               
                hash->buckets[i]->key = 65+i;
                // printf("%c", hash->buckets[i]->key);
                hash->buckets[i]->next = NULL;
        }
}

int calcHash(char *fileName) {
        
        int keyVal = toascii(toupper(*fileName))-65;
        
        
        return keyVal;
}

int hashInsert(struct HashTable *hash, char *fileName) {

        int insertFlag = 0;
        int keyVal;
        

        keyVal = calcHash(fileName);
        
  //      printf("%d",keyVal);
        
        insertFlag = insertIntoLinkedList(&(hash->buckets[keyVal]), fileName);
        
        

        if(insertFlag == 1) {
    //            printf("New record inserted successfully \n");          
                return SUCCESS;
        }
        else {  
      //          printf("New record could not be inserted successfully \n");
                return RECORD_NOT_INSERTED ;
        }
}

int hashDelete(struct HashTable *hash, char *fileName) {
        int keyVal, deleteFlag = 0;

        keyVal = calcHash(fileName);
        //printf("%d to be deleted\n",keyVal);
        deleteFlag = deleteFromLinkedList(&(hash->buckets[keyVal]), fileName);

        if(deleteFlag == 1)
        {
          //      printf("Record %s deleted\n",fileName);         
                return SUCCESS;
        }
        else
        {       
            //    printf("Given record %s not found to be deleted \n",fileName);
                return RECORD_NOT_DELETED;
        }
}

void hashSearch(struct HashTable *hash, char *fileName) {
        int keyVal, searchFlag = 0;

        keyVal = calcHash(fileName);
        searchFlag = searchLinkedList(&(hash->buckets[keyVal]), fileName);

        if(searchFlag == 0) {
              //  printf("Seach key %s not present\n", fileName);
        }
        else {
                //printf("Seach key %s found successfully\n", fileName);
        }
}

/*int loadHashTable(char *fileName[], struct HashTable *hash) {

        int i;
        int size = meta_data.used_fd;        //denotes the number of files in the FileDescriptor array; 
        //change to max_fd laTER

                       
        createHashTable(hash);

        for(i = 0; i<size; i++)
        {
               // hashInsert(hash, fileName[i]);
                hashInsert(hash, fileName[i]);
        }

        printf("All the value from the file loaded into hash table successfully\n");
        return SUCCESS;
}*/

