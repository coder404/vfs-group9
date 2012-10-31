#include<stdio.h>
#include<stdlib.h>

void main()
{

char *token;
char str1[] = "/home/data";


 token = strtok(str1,"/");

int i= 0;
        while(token!=NULL)
        {
               printf("%s\n",token);
                token = strtok(NULL,"/");
                i++;
        }

}
