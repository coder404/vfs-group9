#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"../include/MainHeaderFile.h"
#include"../include/BinarySearchTreeFile.h"
#include"../include/NaryTreeFile.h"

struct bst * search_bst(struct bst *r, char *n){
	
	struct bst *node;
	node = r;
        char firstalpha;
        char *loc_bst; 
	loc_bst = malloc(100);
	strcpy(loc_bst,n);
	firstalpha = *loc_bst;
	if(firstalpha == '/')
	 	memmove(loc_bst,loc_bst+1,strlen(loc_bst)); //to remove the '/' at the beginning

	
	while(node!=NULL){
	
		
		if((strcmp(node->data,loc_bst))>0 )
		{
			
			node = node->left_child;
		}
		else if((strcmp(node->data,loc_bst))<0)
		{
			
			node = node->right_child;
		
		}
		else if((strcmp(node->data,loc_bst))==0)
		{
			
			return node;
		}
	}

	return NULL;
}

void inorder ( struct bst * tree ) {
	if ( tree != NULL ) {
	
	inorder ( tree -> left_child );
	
	inorder ( tree -> right_child );
}
}

struct bst* insert_in_bst(struct bst *head, char* b){

	

	char firstalpha;
	firstalpha = *b;
	if(firstalpha == '/')
			memmove(b,b+1,strlen(b)); //to remove the '/' at the beginning

	struct bst *temp;
	struct bst *r;
	temp = (struct bst *)malloc(sizeof(struct bst));
	temp->right_child=NULL;
	temp->left_child=NULL;
	temp->parent=NULL;
	strcpy(temp->data,b);
	

	r = head;
				
	if(NULL == r){

		r=temp;

		
		return r;
	}
	else if(r!=NULL){
		if((r->left_child==NULL)){
		if((strcmp(r->data,temp->data))>0){

		r->left_child=temp;
		temp->parent = r;
	}
	}	
	else if((r->left_child!=NULL)&&((strcmp(r->data,temp->data))>0))
	{

		insert_in_bst(r->left_child,temp->data);
		}
	if((r->right_child==NULL)&&((strcmp(r->data,temp->data))<0)){
		r->right_child=temp;

		temp->parent = r;
	}
	else if((r->right_child!=NULL)&&((strcmp(r->data,temp->data))<0))
	{

		insert_in_bst(r->right_child,temp->data);
		}
}

return head;
}

void transplant_bst(struct bst *r, struct bst *u, struct bst *v){
	if((v->parent)==NULL)
		r = v;
	else if(u==(u->parent->left_child))
		u->parent->left_child = v;
	else u->parent->right_child = v;
	if(v!=NULL)
		v->parent = u->parent;
}

struct bst *tree_min_bst(struct bst *z){
	while((z->left_child)!=NULL)
		z = z->left_child;
	return z;
}

void delete_bst(struct bst *r, char* a){
	struct bst *x,*t;

	char firstalpha;
	firstalpha = *a;
	if(firstalpha == '/')
			memmove(a,a+1,strlen(a)); //to remove the '/' at the beginning

	t = search_bst(r,a);
	if(((t->left_child)==NULL)&&((t->right_child)==NULL)){
		if(t==t->parent->left_child)
			t->parent->left_child = NULL;
		else
			t->parent->right_child = NULL;
	}
	else if(t->left_child == NULL)
		transplant_bst(r,t,t->right_child);
	else if(t->right_child == NULL)
		transplant_bst(r,t,t->left_child);
	else{
		x=tree_min_bst(t->right_child);
		if(x->parent!=NULL){
			transplant_bst(r,x,x->right_child);
			x->right_child = t->right_child;
			x->right_child->parent = x;
		}
		transplant_bst(r,t,x);
		x->left_child = t->left_child;
		x->left_child->parent = x;
	}	
}


void makedir_bst(char *loc_bst)
{

	char *token;
	char bst_fname[20][20];
	int i;
	struct bst *temp;
	char firstalpha;
	firstalpha =*loc_bst;
	if(firstalpha == '/')
		memmove(loc_bst,loc_bst+1,strlen(loc_bst)); //to remove the '/' at the beginning

	token = strtok(loc_bst,"/");
	
        i= 0;
        while(token!=NULL)
        {
                strcpy(bst_fname[i],token);
                token = strtok(NULL,"/");
                i++;
        }

	char *str = malloc(1000);
        int length_path = i; 	
	i=0;
	strcpy(str , bst_fname[i]);


	while(i<length_path)
	{
		
		strcat(str,"/");
		
		temp = search_bst(BST_Root,str);
		if(temp == NULL)
			insert_in_bst(BST_Root,str);
		i++;
		strcat(str,bst_fname[i]);		

	}
}	


void reinsert_bst(node * head)
{
	node *p;
	p = head;
	if ( p != NULL )
	{
		insert_in_bst(BST_Root,p->fd->location);
		
		reinsert_bst( p -> child );
		
		reinsert_bst(p -> sibling);
	}

}



