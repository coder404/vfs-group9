/* This file contains functions to insert nodes, delete nodes and create the Nary tree */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../include/MainHeaderFile.h"
#include"../include/NaryTreeFile.h"
#include"../include/vfs_errorcodes.h"
#include"../include/vfs_successcodes.h"

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
        	printf("VFS Root node created \n");
        	printf("Inside while %s\n", newnode->data);
                head = newnode ;
                //strcpy(head->fd->name,x);

        }

        else 
        {
                while(p->sibling!=NULL)
                        p=p->sibling;
                newnode->parent = p->parent;
                p->sibling=newnode;
                p->parent->no_children++;
                printf("Inserted sibling at %s\n",p->data);
                 printf( "Inserted  node here with data : %s \n",newnode->fd->name);
                printf("Parent %s\n",newnode->parent->data);
               
		
	

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

            //   printf( "Inserted child head here with data : %s \n",newnode->data);
        }

        else
        {
                
                while(p->child!=NULL)
                        p=p->child;
                p->child=newnode;
                newnode->parent = p;
      //          p->no_children = p->no_children + 1;
                printf( "Inserted child node here with data : %s \n",newnode->fd->name);
                printf("Parent %s\n",newnode->parent->fd->name);
                	
	
	
        }	
        return head;
}

//node * insert_nodes_nary(node *head, char *path, char *name, file_desc *fd)
node * insert_nodes_nary(node *p , file_desc *fd)
{
	// node *p;
	 //node *q;
	
	 //q = head;
	 
	// char * temp_path ;
	// temp_path = malloc(100);
	 
	 // strcpy(temp_path, path);
	// strcat(temp_path, "/");
	 //strcat(temp_path,name);
//	 p = search_nary(q,path);   
int flag;  
	 

   	if(p->child==NULL)
                {

         		
                        insert_child_in_nary(p,fd->name,fd);
                        
                  //      p=p->child;
                   //      printf("%s\n",p->data);
                }
                else
                {
                
    //            	printf(" If the child node is not null then set pointer to point to child node\n");
                //	q = head;
                        p=p->child;
                       flag = 0;
                       	while(p->sibling!=NULL)
                       		p=p->sibling;
                       	 if(p->sibling==NULL && flag==0)
                        {
      //              		printf("If no match is found for the node name then create a sibling node \n");
                                insert_in_nary(p,fd->name,fd);
                             //   p=p->sibling;
                         
                        }
                   }
        //           printf("Head data : %s\n", head->data);
                                                               
       return p;                                 
}

node *  search_nary(node * head,char *path)
{
	node *p;
        int i;
        
        printf("Inside search function \n");
        node *temp;
        int flag = 0;
        char *str1 , *token;
    //    char **filename;
        char filename[20][20];
	
	p = head;
	str1 = (char*)malloc(100*sizeof(char));
printf("Memset start\n");
        memset(&filename, '\0', sizeof(char)*20*20);
//     filename = malloc(30*sizeof(char *));
        
       
        strcpy(str1,path);

        //takes the path, splits and stores in array filename
        token = strtok(str1,"/");
 printf("Memset end\n");
        i= 0;


        while(token!=NULL)
        {
        printf("%s\n",token);
                strcpy(filename[i],token);
                token = strtok(NULL,"/");
  //              printf("filename[%d][20] : %s\n",i,filename[i]);
                i++;
        }

        int length_path = i; 
        printf("length %d\n",length_path);
        i=0;
        
       
        
                  while(i<length_path)
        {
			/* If the first token of the path to the node to be searched for 
			   is the same as the child node then set the pointer to that (child) node */
   //     	printf("Inside while %s\n", p->data);     	
        	
        	flag = 0;
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
       				
       				printf(" p -> data : %s filename[%d] : %s\n", p->data, i, filename[i]);
       				
       				if(strcmp(p->data,filename[i])!=0)
       				{
       				printf(" NOT the same \n");
       				while(p->sibling!=NULL && flag != 1)
       				{				
	      			printf(" p -> data : %s filename[%d] : %s\n", p->data, i, filename[i]);
	      				if(strcmp(p->sibling->data,filename[i])!=0){
	      				printf(" p ->sibling -> data : %s filename[%d] : %s\n", p->sibling->data, i, filename[i]);
       					p=p->sibling;
       					}
       					else
       					{
       					printf("ELSE :  p -> sibling ->data : %s filename[%d] : %s\n", p->sibling->data, i, filename[i]);
          					temp=p;
          					p=p->sibling;
       						i=i+1;
       						flag = 1;
       						//break;
       					}
       			}
       			}
        
                }
                 else if(p->child == NULL)
                	i++;
                }
               
       
        }
        printf("p------> data = %s\n",p->data);
   //    if((strcmp(p-> data,"/")==0) && (length_path != 1)){
//		printf("path not 1\n");
		
//		return NULL;
//		}
	return p;
	//return filename;
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
        

       
      //  strcat(str1,"/");
       // strcat(str1,name);
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
        i=1;

//           strcpy(str1,"/");

        
  /*      if(strcmp(filename[0],meta_data.fs_name)!=0)
        {
                //    first token should be vfs_label


                return 0;
        }
       */
       
        /* if(length_path == 0)
        {
  //      printf("Inserting child for data %s\n", name);
        insert_nodes_nary(VFS_Root, fd->location, name, fd );	
        i++;
        }
        //loop i to no of tokens
        else
        {*/
        
     // strcpy(str2,parent);
      
        for(i=0;i<length_path;i++)
        {
              printf("\n********* i = %d *************\n",i);
                printf("p->data = %s\n",p->data);
                
                
                if(p->child==NULL){
                
                
                        //insert p -> child with token
                      printf("Adding a child to : %s \n", p->data);
                        file_desc * fd_node;
                    
                       
                        
                       
                        
            /*            if(strcmp(p->data,VFS_Root->data)!=0){
                        	 strcpy(str2,p->fd->location);
                        	strcat(str2,"/");
                        
				strcat(str2,p->data);
                      }*/
                       // fd_node = add_fd(str2, filename[i],1);
                       
                        fd_node = add_fd(p, filename[i],fd_attr,-1);
                        
                          printf("PARENT TO FD %s \n",fd_node->location);
                        
                //        printf("CREATE NODE %s\n",fd_node->name);
                        p= insert_child_in_nary(p,filename[i],fd_node);
                        
                 //        if(strcmp(p->data,VFS_Root->data)!=0)
                   //     	strcat(str2,"/");
                        
			//strcat(str2,filename[i]);
			
			    
                        
                        p=p->child;
                       /*if(strcmp(name,filename[i])!=0)
                        p= insert_child_in_nary(p,filename[i],fd_temp);
                        else  if(strcmp(name,filename[i])==0)
                        p= insert_child_in_nary(p,name,fd);
                      p=p->child;*/
                       
                }
                else 
                {
                        p=p->child;
                        flag = 0;
                        do
                        {

            //                   printf("filename[%d] = %s \n",i,filename[i]);
 //                       
         			printf("p->data = %s\n",p->data);
                                if(strcmp(filename[i],p->data)==0)
                                {
                                        //p=p->child;
   //                                     printf("p->child = %s\n",p->data); 
                                        flag=1;
                                        
                                }
                                else if(p->sibling != NULL)
                                {
     //                                   printf("In Else IF : %s\n" , p->data);
                                        flag=0;
                                        p=p->sibling;
                                }
                        }while(flag!=1 && (!strcmp(filename[i],p->data)));

                        if(p->sibling==NULL && flag==0)
                        {
       //                         printf("Adding a sibling to : %s \n", p->data);
                             /*  if(strcmp(name,filename[i])==0) 
                                p= insert_in_nary(p,name,fd);
                                 if(strcmp(name,filename[i])!=0)
                                 p= insert_in_nary(p,filename[i],fd);*/
                                     printf("Adding a sibling to : %s \n", p->data);
                                 
                                file_desc * fd_node;
                       // printf("STR2 IS **  %s \n",str2);
                      fd_node = add_fd(p->parent, filename[i],fd_attr,-1);
                         printf("PARENT TO FD %s \n",fd_node->location);
                        p= insert_in_nary(p,filename[i],fd_node);
              /*          if(strcmp(p->data,VFS_Root->data)!=0)
                        	strcat(str2,"/");
			strcat(str2,filename[i]);*/
                
                                p=p->sibling;
                         
                        }
			
                }
                                	 
  			 
                       
                /*        if(strcmp(p->data,VFS_Root->data)!=0)
               {
                       strcat(str2,"/");
                        strcat(str2,filename[i]);
                        printf("PARENT is now %s\n",str2);
               }
               else{
               		strcat(str2,filename[i]);                        
                        
                     printf("PARENT is ELSE now %s\n",str2);
                  }   
                	//memmove(parent,parent+1,strlen(parent)); 

                  */      
  
       // }
        }
	return head;
}

void delete_node_from_nary(node *p)
{
       
       node * temp;
       temp = p->parent->child;
       
       
       if(strcmp(p->parent->child->data, p->data) == 0)
       {
       printf("Names same delete\n"); 
       		if(p->sibling == NULL)
       			p->parent->child = NULL;
       		else{
       			p->parent->child = p->sibling;
       			//p->sibling = NULL;
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
       			//p->sibling = NULL;
       		}
       		
       
       }
       //no sibling 
       printf("delete nary nodes\n");
//       return;  
       
         
        /*	if(p->sibling != NULL){
        	
        //	printf("parent node of p %s : \n",p->parent->data);
        	
     			p->parent->child = p->sibling;
       }
     		  else   		  
      		 {
      		 printf("DELETE NODE  p %s : \n",p->data);
//       		p->parent->child = NULL;
			p = NULL;

       		}
       	*/
//       	free(p);
        
//        print_subtree_nary(VFS_Root);
        
     /*   else if(strcmp(p->data,filename[length_path-1])!=0)
        {
        printf("NODE DOES NOT EXIST\n");
        }*/
}

void copy_tree_nary(node * head)
{
	node *p;
	p = head;
	
	if ( p	 != NULL )
	{
		//printf("Copying into fd %d\n" , fd_no);
		copy_into_fdarray(p->fd);
		
		copy_tree_nary( p -> child );
		//printf("\t %s",p->data);
		
		copy_tree_nary(p -> sibling );
	}
	return;

}

void copy_into_fdarray(file_desc *fd)
{
//printf("fd_no is %d\n",fd_no);
printf("Copying into fd_arr[%d] is %d\n",fd_no ,fd->attrib);
	fd_arr[fd_no] = *fd;
	fd_no ++;
//	printf("fd_no is %d\n",fd_no);
	//fd_no = fd->fd_id;
	return;
	
	//strcpy(fd_arr[fd->fd_id].name,fd->name);
	//strcpy(fd_arr[fd->fd_id].location,fd->location);
	
}
void search_nary_node(node * head, char *f_name)
{
	node *p;
	p = head;
	if ( p != NULL )
	{
		compare_node_names(p , f_name);
		//printf("\t %s",p->fd->name);
		search_nary_node( p -> child, f_name );
		//printf("\t %s",p->data);
		
		search_nary_node(p -> sibling, f_name );
	}

}

void compare_node_names(node *p , char *f_name)
{

	if(strcmp(p->data,f_name) == 0 ) 
	{
//		print_arr(p);
	
	
	}

}

char * print_arr(node *p, FILE *fp_dir)
{

//	FILE *fp;
	
//	fp = fopen(outputfile,"a");

	
	if(p->child != NULL)
	{
	
		p=p->child;
		while(p != NULL)
		{
			//printf("%s ---- \n", p->data);
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
		//copy_into_fdarray(p->fd);
		fputs(p->data,fp_dir);
		fputs("\n",fp_dir);
		
		print_subtree_nary( p -> child , fp_dir);
		//printf("\t %s",p->data);
		
		print_subtree_nary(p -> sibling , fp_dir);
	}

}

void print_subtree_nary_test(node * head)
{
	node *p;
	p = head;
	if ( p != NULL )
	{
		//copy_into_fdarray(p->fd);
		printf("\t\t%s",p->fd->location);
		
		print_subtree_nary_test( p -> child );
		//printf("\t %s",p->data);
		
		print_subtree_nary_test(p -> sibling);
	}

}

void change_fd(node *p){

	
	strcpy(p->fd->location, p->parent->fd->location);
	strcat(p->fd->location, p->data);
	strcat(p->fd->location,"/");
	printf("Location\t %s\n",p->fd->location);
}

node * change_fds_movedir(node *temp)
{
	node *p;
	p = temp;
	if ( p != NULL)
	{
		//copy_into_fdarray(p->fd);
		//printf("\t\t%s",p->fd->location);
		//if(p != temp)
		change_fd(p);
		
		change_fds_movedir( p -> child );
		//printf("\t %s",p->data);
		
		change_fds_movedir(p -> sibling);
	}

}


char * move_nodes_dir(node * src,node * dest)
{


	node *temp1;
	node *temp2;
	
	temp1 = src;
	temp2 = dest;
	
//	print_subtree_nary_test(temp1);
	
	//Number_of_fds_Deleted++;
//	print_subtree_nary_test(VFS_Root);
//	printf("\nPrint print\n");
//	print_subtree_nary_test(temp1);

	char *str;
	str = malloc(100);
	strcpy(str, temp2->fd->location);
	strcat(str, temp1->data);
	strcat(str,"/");
	node *chk_path;
	printf("STR : %s\n", str);
	chk_path = search_nary(VFS_Root,str);
	printf("check path : %s\n", chk_path->data);
	if(strcmp(chk_path->data,temp1->data)==0)
		return ERR_VFS_MOVEDIR_05;

	printf("Before changing fds\n");
	
	print_subtree_nary_test(temp1);
	strcpy(temp1->fd->location , str);
	
	if(dest->parent == src)
		return ERR_VFS_MOVEDIR_06;
				
		
	delete_node_from_nary(src);
	temp1->parent = dest;
	temp1->sibling = NULL;	
	printf("After deleting\n");
	print_subtree_nary_test(temp1);
	printf("\nPrinting entire tree...\n");
	print_subtree_nary_test(VFS_Root);	
	printf("\n");
	change_fds_movedir(temp1);
	printf("\nAfter changing fds\n");
	print_subtree_nary_test(temp1);
//	print_subtree_nary_test(temp1);
	int flag = 0;
	printf("\n");
	if(dest->child == NULL)
	{
		printf("ndest child is NULL\n");
		
		dest->child = temp1;	
	
	}
	
	else if(dest->child != NULL)
	{
		temp2 = temp2->child;
		while(temp2->sibling != NULL){
		printf("temp2->data : %s temp1->data : %s \n",temp2->data, temp1->data);
	
			temp2 = temp2->sibling;
		}
		
		if(flag!=1){
		temp2->sibling = temp1;
			
		}
		
	}	
	
	
	return SUC_VFS_MOVEDIR_01;


}
