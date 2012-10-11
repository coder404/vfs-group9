#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../include/MainHeaderFile.h"

node* insert(node *head, char* x)
{
        node *p, *newnode;
        newnode = (node*) malloc(160);
        newnode->child = NULL;
        newnode->sibling = NULL;
        strcpy(newnode->data,x);

        p = head;
	if ( head == NULL) 
        {
                head = newnode ;

                printf( "Inserted sib head here with data : %s \n\n",newnode->data);
        }

        else 
        {
                printf( "Inserted sib node here with data : %s \n\n",newnode->data);
                while(p->sibling!=NULL)
                        p=p->sibling;
                p->sibling=newnode;

        }
        return head;

}


node * insert_child(node * head, char *str1 )
{

        node *p, *newnode;
        newnode = (node*) malloc(sizeof(node));
        strcpy(newnode->data,str1);
        newnode->child = NULL;
        newnode->sibling = NULL;

        p = head;
        if ( head == NULL)  
        {
                head = newnode ;

                printf( "Inserted child head here with data : %s \n",newnode->data);
        }

        else
        {
                printf( "Inserted child node here with data : %s \n",newnode->data);
                while(p->child!=NULL)
                        p=p->child;
                p->child=newnode;

        }	
        return head;
}

int create_tree(node* head, char *path)
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
        
        
        if(strcmp(filename[0],meta_data.fs_name)!=0)
        {
                //    first token should be vfs_label


                return 0;
        }
        
        //loop i to no of tokens
        for(i=1;i<length_path;i++)
        {
                printf("\n********* i = %d *************\n",i);
                printf("p->data = %s\n",p->data);
                if(p->child==NULL)
                {
                        //insert p -> child with token
                        printf("Adding a child to : %s \n", p->data);
                        p= insert_child(p,filename[i]);
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
                                printf("Adding a sibling to : %s \n", p->data);
                                p= insert(p,filename[i]);
                                p=p->sibling;
                         
                        }

                }  
        }
	return 1;
}

void print_tree(node * head)
{
	node *p;
	p = head;
	if ( p != NULL )
	{
		
		print_tree ( p -> child );
		printf("\t %s",p->data);
	
		print_tree (p -> sibling );
	}

}

