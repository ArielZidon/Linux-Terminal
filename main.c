#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

#define lenght 100


int printDir()
{
    DIR *dir;
    struct dirent *sd;
    dir = opendir(".");
    if(dir==NULL)
    {
        printf("error!!");
        return 1;
    }
    while((sd=readdir(dir))!=NULL)
    {
         if (sd->d_name[0] != '.')
        {
            printf(">>%s\n", sd->d_name);
        }
    }
    closedir(dir);
}

int updateLoc(char *loc)
{
    if (getcwd(loc, lenght) == NULL)
    {
        printf("Error\n");
        return 1;
    }
}

int main()
{
    char command[lenght];
    char loc[lenght];

    while(strcmp(command, "EXIT"))
    {
        updateLoc(loc);
        printf("%s>",loc);
        gets(command);

        if(strncmp(command,"ECHO ",5)==0)
        {
            for(int i = 5;i<lenght && command[i]!='\0';i++)
            {
                printf("%c",command[i]);
            }
            printf("\n");
        }
        else if(strncmp(command,"DIR",3)==0)
        {
            printDir();
        }
        else if (strncmp(command, "CD ", 3) == 0)
        {
            if (chdir(&(command[3])) != 0)
            {
                printf("Error, there is no lib with this name.\n");
                return 1;
            }

        }
        else if(strncmp(command,"COPY ",5)==0)
        {
            char src[lenght];
            char des[lenght];
            int i=5,j1=0;
            while(command[i] != ' '){

                    src[j1++]=command[i++];
            }

            src[j1]='\0';
            j1 = 0;
            while(command[++i] != '\0'){
                    des[j1++]=command[i];
            }
            des[j1]='\0';
            FILE *fileSrc=NULL;
            FILE *fileDest=NULL;
            fileSrc = fopen(src,"r");
            fileDest = fopen(des,"w+");
            if(fileSrc==NULL || fileDest==NULL)
            {
                printf("error!!\n");
                return -1;
            }
            char temp =' ';
            while(fscanf(fileSrc,"%c",&temp)!=EOF)
            {
                fprintf(fileDest,"%c",temp);
            } 
            fclose(fileSrc);
            fclose(fileDest);
        }
        else if(strncmp(command,"DELETE ",7)==0)
        {
            unlink(&(command[7]));
        }
        else
        {
            // system(command);
            int check = fork();
            if(check<0){
                printf("Error :(\n");
                return 1;
            }
            if (check==0){
                char str1[lenght]="/bin/";
                strcat(str1,command);
                execlp(str1,command,NULL);
            }
            wait();
        }
    }
}