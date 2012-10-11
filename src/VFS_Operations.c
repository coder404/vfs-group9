#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include"../include/MainHeaderFile.h"

void  create_file(char* f_path, char f_name[], char data[])
{
	printf("CREATION OF FILE\n");
        int size;
        size = strlen(data);
	printf("SIze of data = %d\n",size);
	int num_blocks = ceil((double)size/BLOCK_SIZE);	
	printf("NUM_BLOCKS : %d\n",num_blocks);
        int i, start=0;
	printf("MAX FD = %d\n", meta_data.max_fd);
        for (i=0; i<meta_data.max_fd; i++)
        {
        printf("FREE_LIST[%d] = %d\n",i,free_list[i]);
	
		if (free_list[i]==1)
		{
			start=i+1;
			printf("IF1\n");
		}
                if ((i-start)+1 == num_blocks) 
		{
			printf("IF2\n");
			break;
		}
        }
        int offset = OFFSET + start*BLOCK_SIZE;
        int start1=start;
        fseek(fs, offset, SEEK_SET);
        fwrite(data,  size, 1, fs);
	free_list[start1]=1;
	 printf("FREELIST[%d] = %d\n",start1,free_list[start1]);
       
     /* for (; start<start1+num_blocks;start++)
	{
         printf("START = %d\t",start);
	 free_list[start]=1;
	 printf("FREELIST = %d\n",free_list[start]);
	}
	*/
	printf("START BLOCK : %d\n",start1);

        file_desc fd;
        strcpy(fd.name, f_name);
        strcpy(fd.location , f_path); 
       printf("FD.LOCATION : %s\n",fd.location);
       strcat(fd.location, "/");
       strcat(fd.location, f_name);
       printf("FD.LOCATION : %s\n",fd.location);
       fd.size = size;
	
        fd.start_block = start1;
        fd.type = 0;
        fd_arr[meta_data.used_fd] = fd;
	meta_data.used_fd++;
	printf("FD ARRAY INDEX 0 : %s\n", fd_arr[0].location);
	printf("FD ARRAY INDEX 1 : %s\n", fd_arr[1].location);
	printf("FD ARRAY INDEX 2: %s\n", fd_arr[2].location);
}

