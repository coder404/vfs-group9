#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../include/MainHeaderFile.h"

int main(int argc, char **argv)
{
	int choice;
	char fs_name[20];
	char file_path[1000];
	int fs_size;
	char file_name[20];
	int type;
	char data[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
	
	do
	{
		printf("FILESYSTEM MENU\n");
		printf("1. Create a filesystem.\n");
		printf("2. Mount a filesystem.\n");
		printf("3. Unmount a filesystem.\n");
		printf("4. Create a file/directory.\n");
		printf("0. Exit the filesystem.\n");
		printf("Enter your choice : ");

		scanf("%d",&choice);
		switch(choice)
		{
			case 1: 
				printf("\nEnter the name of the filesystem to be created : ");
				scanf("%s",fs_name); // Add code to check if the filename is valid
				printf("\nEnter the size of the filesystem : ");
				scanf("%d",&fs_size);
			        create_vfs(fs_name, fs_size);
			        printf("\n");
			        break;
			case 2:
				printf("\nEnter the name of the filesystem to be mounted : ");
				scanf("%s",fs_name); // Add code to check if the filename is valid
				mount(fs_name);        	
				printf("\n");
	       			break;
	       		case 3:
	       			printf("\nUnmounting the filesystem...");
	       			unmount();
	       			printf("\n");
	       			break;
	       		case 4:
	       			printf("\nEnter the path where the file/directory needs to be created : ");
	       			scanf("%s",file_path);
				printf("\nEnter the name of the file/directory : ");
				scanf("%s",file_name);    			
		       		printf("\nIs this a file or directory ? Enter '0' for file and '1' for directory : ");
				scanf("%d",&type);
				switch(type)
		       		{
		       			case 0 :
		       				create_file(file_path,file_name,data);
		       				break;
		       			case 1 :
		       			//	create_dir();
		       				break;
		       			default:
		       				printf("Enter a correct choice. Enter 'f' for file and 'd' for directory : ");
		       				break;
		       		}	
		       	default:
		       		break;
		}
	}while(choice!=0);
//       create_file("vfs-group9/home/first/","hello2",data);
       // create_file("vfs-group9/home/second","hello3",data);
//        printf("%s %d %d %d\n", meta_data.fs_name, meta_data.fs_size, meta_data.max_fd, meta_data.used_fd);
        
  //      printf("%s %d %d %d\n", meta_data.fs_name, meta_data.fs_size, meta_data.max_fd, meta_data.used_fd);
        return 0;
}

