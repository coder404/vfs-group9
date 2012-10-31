/* This file contains functions to insert nodes, delete nodes and create the Nary tree */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"

/* Function inserts a sibling node in the Nary tree data structure */
node* insert_in_nary(node *head, char* x,file_desc *fd_id)
{
        node *p, *newnode;
        newnode = (node*) malloc(160);
        newnode->child = NULL;
        newnode->sibling = NULL;
        strcpy(newnode->data,x);
        newnode->fd = fd_id;
        //newnode->fd = fd_id;

        p = head;
	if ( head == NULL) 
        {
        	printf("VFS Root node created \n");
        	printf("Inside while %s\n", newnode->data);
                head = newnode ;
                //strcpy(head->fd->name,x);

        }

        else 
        {
                while(p->sibling!=NULL)
                        p=p->sibling;
                p->sibling=newnode;
                printf("Inserted sibling at %s\n",p->data);

        }
        return head;

}

/* Function inserts a child node in the Nary tree data structure */
node * insert_child_in_nary(node * head, char *str1,file_desc *fd_id )
{

        node *p, *newnode;
        newnode = (node*) malloc(sizeof(node));
        strcpy(newnode->data,str1);
        newnode->child = NULL;
        newnode->sibling = NULL;
        newnode->fd = fd_id;

        p = head;
        if ( head == NULL)  
        {
                head = newnode ;

            //   printf( "Inserted child head here with data : %s \n",newnode->data);
        }

        else
        {
                
                while(p->child!=NULL)
                        p=p->child;
                p->child=newnode;
                printf( "Inserted child node here with data : %s \n",newnode->data);

        }	
        return head;
}

node * insert_nodes_nary(node *head, char *path, char *name, file_desc *fd)
{
	 node *p;
	 node *q;
	 printf("path : %s\n",path);
	 q = head;
	 p = search_nary(q,path);   
	 int flag;  
	 
	 printf("Insert_Nodes_NARY Inserting at %s\n",p->data);
   	if(p->child==NULL)
                {
                        printf("If the child node is null then insert a child node here\n");
         		
                        insert_child_in_nary(p,name,fd);
                  //      p=p->child;
                         printf("%s\n",p->data);
                }
                else
                {
                
                	printf(" If the child node is not null then set pointer to point to child node\n");
                	q = head;
                        p=p->child;
                        flag = 0;
                       	while(p->sibling!=NULL)
                       		p=p->sibling;
                       	 if(p->sibling==NULL && flag==0)
                        {
                    		printf("If no match is found for the node name then create a sibling node \n");
                                insert_in_nary(p,name,fd);
                             //   p=p->sibling;
                         
                        }
                   }
                   printf("Head data : %s\n", head->data);
                                                               
       return head;                                 
}

node * search_nary(node * head,char *path)
{
	node *p;
        int i;
        
        node *temp;
        int flag;
        char *str1 , *token;
        
        char filename[20][20];
	
	p = head;
	str1 = (char*)malloc(100*sizeof(char));

        memset(&filename, '\0', sizeof(char)*20*20);
        strcpy(str1,path);
        
printf("Inside while %s\n", p->data);
        //takes the path, splits and stores in array filename
        token = strtok(str1,"/");
//	 strcpy(str_path,str1);
     //   memmove(str1,str1+1,strlen(str1)); //to remove the '/' at the beginning
        i= 0;
         printf("Search function\n");
        while(token!=NULL)
        {
                strcpy(filename[i],token);
                token = strtok(NULL,"/");
                printf("filename[%d] : %s\n",i,filename[i]);
                i++;
        }

        int length_path = i; 
        printf("length %d\n",length_path);
        i=0;
        
       
        
                  while(i<length_path-1)
        {
			/* If the first token of the path to the node to be searched for 
			   is the same as the child node then set the pointer to that (child) node */
        	printf("Inside while %s\n", p->data);
        		if(p->child != NULL && strcmp(p->child->data,filename[i])==0 )
        		{
        			printf("Search : p->child->data : %s = filename[%d] : %s \n",p->child->data, i, filename[i]);
        			temp = p;
        			p=p->child;
        			
        			i++;
        		}
       			else 
       			{
       			
       			/* Else loop through the child nodes and compare with the 
       			   the current token till a match is found */
       			   
       			if(p->child!=NULL)
       			{
       				p=p->child;
       				
       				while(p->sibling!=NULL)
				{
	      				if(strcmp(p->sibling->data,filename[i])!=0){
       					p=p->sibling;
       					}
       					else
       					{
          					temp=p;
       						i=i+1;
       						//break;
       					}
       			}
        
                }
                }
                if(p->child == NULL)
                	i++;
        
        }
		
                    return p;
    }


node * create_tree_in_nary(node *head, char *path, char *name, file_desc *fd)
{

        char *str1 , *token;
        node *p;
        int i;
        char filename[20][20];

	str1 = (char*)malloc(100*sizeof(char));

        memset(&filename, '\0', sizeof(char)*20*20);
        strcpy(str1,path);
        p=head;

        //takes the path, splits and stores in array filename
        token = strtok(str1,"/");

        i= 0;
        while(token!=NULL)
        {
                strcpy(filename[i],token);
                token = strtok(NULL,"/");
                i++;
        }

        int length_path = i; //length_path has the number of tokens in path

        i=0;
        int flag=0;

        p=head;
        
        
  /*      if(strcmp(filename[0],meta_data.fs_name)!=0)
        {
                //    first token should be vfs_label


                return 0;
        }
       */
        i=1;
         if(length_path == 1)
        {
        printf("Inserting child for data %s\n", filename[0]);
        insert_nodes_nary(VFS_Root, fd->location, name, fd );	
        i++;
        }
        //loop i to no of tokens
        else
        {
        for(i=0;i<length_path;i++)
        {
                printf("\n********* i = %d *************\n",i);
                printf("p->data = %s\n",p->data);
                if(p->child==NULL)
                {
                        //insert p -> child with token
                        printf("Adding a child to : %s \n", p->data);
                        p= insert_child_in_nary(p,name,fd);
                        p=p->child;
                }
                else
                {
                        p=p->child;
                        flag = 0;
                        do
                        {

                               printf("filename[%d] = %s \n",i,filename[i]);
                                printf("p->data = %s\n",p->data);
                                if(strcmp(filename[i],p->data)==0)
                                {
                                        //p=p->child;
                                        printf("p->child = %s\n",p->data); 
                                        flag=1;
                                        
                                }
                                else if(p->sibling != NULL)
                                {
                                        printf("In Else IF : %s\n" , p->data);
                                        flag=0;
                                        p=p->sibling;
                                }
                        }while(flag!=1 && (!strcmp(filename[i],p->data)));

                        if(p->sibling==NULL && flag==0)
                        {
                     //           printf("Adding a sibling to : %s \n", p->data);
                                p= insert_in_nary(p,name,fd);
                                p=p->sibling;
                         
                        }

                }  
        }
        }
	return head;
}

void delete_node_from_nary(node *head, char *path)
{
        char *str1 , *token;
        node *p;
        int i;
        char filename[20][20];
	node *temp;
	str1 = (char*)malloc(100*sizeof(char));

        memset(&filename, '\0', sizeof(char)*20*20);
        strcpy(str1,path);
        p=head;

        //takes the path, splits and stores in array filename
        token = strtok(str1,"/");

        i= 0;
        while(token!=NULL)
        {
                strcpy(filename[i],token);
                token = strtok(NULL,"/");
                i++;
        }
        

        int length_path = i; //length_path has the number of tokens in path

     
        int flag=0;

        p=head;
       
        i=1;
        while(i<length_path)
        {
        
        	
        		if(p->child != NULL && strcmp(p->child->data,filename[i])==0 )
        		{
        			
        			temp = p;
        			p=p->child;
        			
        			i++;
        		}
       			else 
       			{
       			if(p->child!=NULL)
       			{
       				p=p->child;
       				
       				while(p->sibling!=NULL)
				{
	      				if(strcmp(p->sibling->data,filename[i])!=0){
       					p=p->sibling;
       					}
       					else
       					{
          					temp=p;
       						i=i+1;
       						//break;
       					}
       			}
        
                }
                }
        
        }
         
        if(strcmp(p->data,filename[length_path-1])==0)
        {
         
        	if(p->sibling != NULL)
      {
           	        	temp->child = p->sibling;
       }
       else
       {
       		temp->child = NULL;
       }
       
        }
     /*   else if(strcmp(p->data,filename[length_path-1])!=0)
        {
        printf("NODE DOES NOT EXIST\n");
        }*/
}

void print_tree_nary(node * head)
{
	node *p;
	p = head;
	if ( p != NULL )
	{
		copy_into_fdarray(p->fd);
		//printf("\t %s",p->fd->name);
		print_tree_nary( p -> child );
		//printf("\t %s",p->data);
		
		print_tree_nary(p -> sibling );
	}

}

void copy_into_fdarray(file_desc *fd)
{
	if(strcmp(fd->name,"/") == 0)
	{
		printf("Root node\n");
	}
	else 
	{
	
	fd_arr[fd->fd_id] = *fd;
	//strcpy(fd_arr[fd->fd_id].name,fd->name);
	//strcpy(fd_arr[fd->fd_id].location,fd->location);
	
	
	
	
	}
	//return;


}

