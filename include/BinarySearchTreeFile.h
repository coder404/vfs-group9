#ifndef BINARYSEARCHTREEFILE_H
#define BINARYSEARCHTREEFILE_H

#include "NaryTreeFile.h"
struct bst{
	char data[100]; //stores the absolute path of the file/folder
	//file_desc fd;
	struct bst *left_child;
	struct bst *right_child;
	struct bst *parent;
	char name[50];
};

struct bst *BST_Root;

struct bst * search_bst(struct bst *r, char n[1000]);
struct bst* insert_in_bst(struct bst *r, char b[1000]);
void transplant_bst(struct bst *r, struct bst *u, struct bst *v);
struct bst *tree_min_bst(struct bst *z);
void delete_bst(struct bst *r, char a[1000]);
void makedir_bst(char *loc_bst);
void reinsert_bst(node * head);

#endif
