#include "executer.h"
#include "command.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
//char* path;
char exc_path[512] = "";
char exc_paths[100][100] = {{0}};
char new_program[512]="";
int len_PATH;
int execute(char* program, char** arg_list)
{
    if(strcmp(program,"echo")==0)
    {
        execvp(program,arg_list);
        perror("Execution_STATUS:");
        abort();
    }
    else if(strchr(program,'/') != NULL){
        if(*program!='/')
        {
            strcat(new_program,"/");
            strcat(new_program,program);
            program = new_program;
        }
        execv(program,arg_list);
        perror("Execution_STATUS:");
                abort();

    }
    int count = 0,inc = 0,err=0;
    char prog[512]= "";
    while(inc<len_PATH)
    {
        errno=0;

        strcat(prog,exc_paths[inc]);
        strcat(prog,program);

        err = execv(prog, arg_list);

        if (err != -1) //if error happend
            break;
        inc ++;
        memset(prog,0,sizeof prog);
    }
    perror("Execution_STATUS:");
    abort();
}
void set_PATH(char* value){
    len_PATH = 0;
    strcpy(exc_path,value) ;
    char* p_poi = exc_path;
    char* tok = strtok(p_poi,":");
    while(tok != NULL){
        strcpy(exc_paths[len_PATH],tok);
        if(*(tok + strlen(tok) - 1) != '/')
        {
            strcat(exc_paths[len_PATH],"/");
        }
        len_PATH++;
        tok = strtok(NULL,":");
    }
}
