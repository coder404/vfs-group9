/* This file contains functions to insert nodes, delete nodes and create the Nary tree */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/vfs_errorcodes.h"

/* Function inserts a sibling node in the Nary tree data structure */
node* insert_in_nary(node *head, char* x,file_desc *fd_id)
{
        node *p, *newnode;
        newnode = (node*) malloc(160);
        newnode->child = NULL;
        newnode->sibling = NULL;
        newnode->parent = NULL;
        strcpy(newnode->data,x);
        newnode->fd = fd_id;
       
        p = head;
	if ( head == NULL) 
        {
        	
                head = newnode ;
            

        }

        else 
        {
                while(p->sibling!=NULL)
                        p=p->sibling;
                newnode->parent = p->parent;
                p->sibling=newnode;
                p->parent->no_children++;
                
	

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
        newnode->parent = NULL;
        newnode->fd = fd_id;
	newnode->no_children = 0;
        p = head;
        if ( head == NULL)  
        {
                head = newnode ;

            
        }

        else
        {
                
                while(p->child!=NULL)
                        p=p->child;
                p->child=newnode;
                newnode->parent = p;
     
               
	
        }	
        return head;
}

//node * insert_nodes_nary(node *head, char *path, char *name, file_desc *fd)
node * insert_nodes_nary(node *p , file_desc *fd)
{
	  
int flag;  
	 

   	if(p->child==NULL)
                {

         		
                        insert_child_in_nary(p,fd->name,fd);
                        
                  
                }
                else
                {
                
   
                        p=p->child;
                       flag = 0;
                       	while(p->sibling!=NULL)
                       		p=p->sibling;
                       	 if(p->sibling==NULL && flag==0)
                        {
     
                                insert_in_nary(p,fd->name,fd);
                            
                        }
                   }
       
                                                               
       return p;                                 
}

node *  search_nary(node * head,char *path)
{
	node *p;
        int i;
        
      
        node *temp;
        int flag = 0;
        char *str1 , *token;
 
        char filename[20][20];
	
	p = head;
	str1 = (char*)malloc(100*sizeof(char));

        memset(&filename, '\0', sizeof(char)*20*20);

        
       
        strcpy(str1,path);

      
        token = strtok(str1,"/");

        i= 0;


        while(token!=NULL)
        {
      
                strcpy(filename[i],token);
                token = strtok(NULL,"/");
 
                i++;
        }

        int length_path = i; 
     
        i=0;
        
       
        
                  while(i<length_path)
        {
			
        	flag = 0;
        		if(p->child != NULL && strcmp(p->child->data,filename[i])==0 )
        		{
        			
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
       				
       				
       				if(strcmp(p->data,filename[i])!=0)
       				{
       				
       				while(p->sibling!=NULL && flag != 1)
       				{				
	      			
	      				if(strcmp(p->sibling->data,filename[i])!=0){
	      				
       					p=p->sibling;
       					}
       					else
       					{
       					
          					temp=p;
          					p=p->sibling;
       						i=i+1;
       						flag = 1;
       						
       					}
       			}
       			}
        
                }
                 else if(p->child == NULL)
                	i++;
                }
               
       
        }
       
   
	return p;
	
    }


node * create_tree_in_nary(node *head, char *path,int fd_attr)
{

        char *str1 , *token;
        node *p;
        int i;
        char filename[20][20];
        file_desc *fd_temp;
        fd_temp = NULL;

	str1 = (char*)malloc(100*sizeof(char));

        memset(&filename, '\0', sizeof(char)*20*20);
        strcpy(str1,path);
        

        p=head;

   
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
        i=1;


      
        for(i=0;i<length_path;i++)
        {
             
                
                if(p->child==NULL){
                
                
                        //insert p -> child with token
                     
                        file_desc * fd_node;
                    
                       
                        
                       
                        
            
                       fd_node = add_fd(p, filename[i],fd_attr,-1);
                        
                 
                        
               
                        p= insert_child_in_nary(p,filename[i],fd_node);
                        
                
                        
                        p=p->child;
                      
                }
                else 
                {
                        p=p->child;
                        flag = 0;
                        do
                        {

                            
                       
         			
                                if(strcmp(filename[i],p->data)==0)
                                {
                                       
                                        flag=1;
                                        
                                }
                                else if(p->sibling != NULL)
                                {
     
                                        flag=0;
                                        p=p->sibling;
                                }
                        }while(flag!=1 && (!strcmp(filename[i],p->data)));

                        if(p->sibling==NULL && flag==0)
                        {
                         
                                 
                                file_desc * fd_node;
                       
                      fd_node = add_fd(p->parent, filename[i],fd_attr,-1);
                         
                        p= insert_in_nary(p,filename[i],fd_node);
             
                                p=p->sibling;
                         
                        }
			
                }
                                	 
  			 
                       
               
        }
	return head;
}

void delete_node_from_nary(node *p)
{
       
       node * temp;
       temp = p->parent->child;
       
       
       if(strcmp(p->parent->child->data, p->data) == 0)
       {
       
       		if(p->sibling == NULL){
       			p->parent->child = NULL;
       			}
       		else{
       		
       			p->parent->child = p->sibling;
       		
       		}
       }
       
       else if(strcmp(p->parent->child->data, p->data) != 0)
       {
       		while(strcmp(temp->sibling->data, p->data) != 0 && temp->sibling != NULL)
       		{
       			temp = temp->sibling;
       		
       		}	
       		if (p->sibling == NULL)
       			temp->sibling = NULL;
       		
       		else{
       			temp->sibling =  p->sibling;
       			
       		}
       		
       
       }
      
}

void copy_tree_nary(node * head)
{
	node *p;
	p = head;
	
	if ( p	 != NULL )
	{
		
		copy_into_fdarray(p->fd);
		
		copy_tree_nary( p -> child );
		
		copy_tree_nary(p -> sibling );
	}
	return;

}

void copy_into_fdarray(file_desc *fd)
{


	fd_arr[fd_no] = *fd;
	fd_no ++;

	return;
	
	
	
}
void search_nary_node(node * head, char *f_name)
{
	node *p;
	p = head;
	if ( p != NULL )
	{
		compare_node_names(p , f_name);
	
		search_nary_node( p -> child, f_name );
		
		
		search_nary_node(p -> sibling, f_name );
	}

}

void compare_node_names(node *p , char *f_name)
{

	if(strcmp(p->data,f_name) == 0 ) 
	{

	
	
	}

}

char * print_arr(node *p, FILE *fp_dir)
{


	
	if(p->child != NULL)
	{
	
		p=p->child;
		while(p != NULL)
		{
			
			fputs(p->data,fp_dir);
			fputs("\n",fp_dir);
			p=p->sibling;
		}
	
	}	
	
}

void print_subtree_nary(node * head, FILE *fp_dir)
{
	node *p;
	p = head;
	if ( p != NULL )
	{
		
		fputs(p->data,fp_dir);
		fputs("\n",fp_dir);
		
		print_subtree_nary( p -> child , fp_dir);
	
		
		print_subtree_nary(p -> sibling , fp_dir);
	}

}

void print_subtree_nary_test(node * head)
{
	node *p;
	p = head;
	if ( p != NULL )
	{
		
		
		print_subtree_nary_test( p -> child );
		
		print_subtree_nary_test(p -> sibling);
	}

}

void change_fd(node *p){

	
	strcpy(p->fd->location, p->parent->fd->location);
	strcat(p->fd->location, p->data);
	strcat(p->fd->location,"/");

}

node * change_fds_movedir(node *temp)
{
	node *p;
	p = temp;
	if ( p != NULL)
	{
		
		change_fd(p);
		
		change_fds_movedir( p -> child );
		
		change_fds_movedir(p -> sibling);
	}

}


char* move_nodes_dir(node * src,node * dest)
{


	node *temp1;
	node *temp2;
	
	temp1 = src;
	temp2 = dest;
	

	char *str;
	str = malloc(100);
	strcpy(str, temp2->fd->location);
	strcat(str, temp1->data);
	strcat(str,"/");
	
	
	
	print_subtree_nary_test(temp1);
	strcpy(temp1->fd->location , str);
			
	delete_node_from_nary(src);
	temp1->parent = dest;
	temp1->sibling = NULL;	
	
	print_subtree_nary_test(temp1);
	
	print_subtree_nary_test(VFS_Root);	
	
	change_fds_movedir(temp1);
	
	print_subtree_nary_test(temp1);

	int flag = 0;

	if(dest->child == NULL)
	{
		
		
		dest->child = temp1;	
	
	}
	
	else if(dest->child != NULL)
	{
		temp2 = temp2->child;
		while(temp2->sibling != NULL){
		
	
			temp2 = temp2->sibling;
		}
		
		if(flag!=1){
		temp2->sibling = temp1;
			
		}
		
	}	
	
	
	return;


}
