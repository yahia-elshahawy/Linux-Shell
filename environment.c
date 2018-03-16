#include "environment.h"
#include "executer.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define size 512
int lines_num = 0;
char reader[size];
char var[100][100]= {""};
char path[100][100]= {""};
char *token;

char *liner[512];
int lin=0;

int get_lines_num()
{
    return lines_num;
}

void setup_environment( void )
{
    int i;
    char * vari[] = {"PATH","HOME","PROJECT"};

    for (i = 0; i<(sizeof vari)/8 - 1; i++)
    {
        strcpy(var[i],vari[i]);
        strcpy(path[i], getenv(vari[i]));
        lines_num++;
    }
    strcpy(var[i],vari[i]);
    strcpy(path[i], getenv("PWD"));
    lines_num++;
    i++;
    set_PATH(path[0]);
}

void get_variables(char ** v)
{
    int j ;
    for(j = 0; j<lines_num ; j++)
    {
        v[j] = var[j];//don't use &var[j]
    }
}
void get_paths(char ** p)
{
    int k ;
    for(k = 0; k<lines_num ; k++)
    {
        p[k] = path[k]; //don't use &
    }
}

