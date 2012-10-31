#ifndef NARYTREEFILE_H
#define NARYTREEFILE_H

typedef struct node
{
        struct node * child;
        struct node * sibling;
      //  int fd;
      	file_desc *fd;
        char data[20];
}node;

node* VFS_Root;

//node* insert_in_nary(node *head, char* x);
//node* insert_in_nary(node *head, char *path,int fd);
node* insert_in_nary(node *head, char *path,file_desc *fd);
//node * insert_child_in_nary(node * head, char *str1 );
//node * insert_child_in_nary(node *head, char *path,int fd );
node * insert_child_in_nary(node *head, char *path,file_desc *fd );
//void delete_node_from_nary(node *head, char *path,file_desc *fd);
void delete_node_from_nary(node *head, char *path);
//int create_tree_in_nary(node* head, file_desc fd);
//int create_tree_in_nary(node* head, char *path);
node * create_tree_in_nary(node *head, char *path, char *name, file_desc *fd);
//node * insert_nodes_nary(node *head, char *path, char *name, int fd);
node * insert_nodes_nary(node *head, char *path, char *name,file_desc *fd);
void print_tree_nary(node * head);
node * search_nary(node * head,char *path);
void traversal_nary(node * head,int i);
void copy_into_fdarray(file_desc *fd);
#endif
