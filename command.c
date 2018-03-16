#include "command.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "variables.h"
const char * act_path;
int i;
void cd( char* path )
{
    errno = 0;
    // you should implement this function
    if (strcmp(path,"")==0)
    {
        chdir(lookup_variable("HOME"));
        perror("Status2");
    }
    else if (path[0] == '~')
    {
        char user[512] = "";
        char *p = strtok(path, "~");  // split
        //printf("%s",p);
        if(p!=NULL)
            {
            if(p[0] != '/'){
            strcat(user,"/home/");

            }
            else
            {
                strcat(user,lookup_variable("HOME"));
            //strcat
            }
            strcat(user,p);
            //printf("%s \n",user);
            chdir(user);
            }
        else
            chdir(lookup_variable("HOME"));

        perror("Status4");
    }
    else
    {
        chdir(path);
        perror("Status3");
    }
}
