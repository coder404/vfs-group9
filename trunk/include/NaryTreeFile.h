#ifndef NARYTREEFILE_H
#define NARYTREEFILE_H

typedef struct node
{
        struct node * child;
        struct node * sibling;
        struct node * parent;
        int no_children;
      //  int fd;
      	file_desc *fd;
        char data[20];
}node;

node* VFS_Root;
int fd_no;

#define FILE_ATTRIBUTE 0
#define DIR_ATTRIBUTE 1
#define INVALID_CHARACTER "/"
#define PRINT_VFS() printf("VFS ROOT DATA %s %p\n",VFS_Root->data, &(VFS_Root->data))
node * load_vfs_structure();
file_desc * add_fd(node *parent, char *dir_name , int fd_att, int start);
//node* insert_in_nary(node *head, char* x);
//node* insert_in_nary(node *head, char *path,int fd);
node* insert_in_nary(node *head, char *path,file_desc *fd);
//node * insert_child_in_nary(node * head, char *str1 );
//node * insert_child_in_nary(node *head, char *path,int fd );
node * insert_child_in_nary(node *head, char *path,file_desc *fd );
//void delete_node_from_nary(node *head, char *path,file_desc *fd);
void delete_node_from_nary(node *p);
//int create_tree_in_nary(node* head, file_desc fd);
//int create_tree_in_nary(node* head, char *path);
node * create_tree_in_nary(node *head, char *path,int fd_attr);
//node * insert_nodes_nary(node *head, char *path, char *name, int fd);
//node * insert_nodes_nary(node *head, char *path, char *name,file_desc *fd);
node * insert_nodes_nary(node *p , file_desc *fd);
void copy_tree_nary(node * head);
node* search_nary(node * head,char *path);
void traversal_nary(node * head,int i);
void copy_into_fdarray(file_desc *fd);
void compare_node_names(node *p , char *f_name);
char * print_arr(node *p, FILE *fp_dir);
void print_subtree_nary(node * head , FILE *fp_dir);
char * move_nodes_dir(node * src,node * dest);
void print_subtree_nary_test(node * head);
char* list_file(char *f_path,char *hd_path);
char* remove_file(char *f_path);
char* update_file(char* f_path, char* hd_path);
#endif
