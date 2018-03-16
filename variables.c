#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "variables.h"
#include "environment.h"
#include "executer.h"

#define size 512

char* variables[size];
char* paths[size];
    char added_variables[100][100] = {{0}};
    char added_path[100][100] = {{0}};

int lines_num;
void Constructor()
{
    lines_num = get_lines_num();
    get_variables(variables);
    get_paths(paths);

    int k;
}
char* lookup_variable( char* key )
{
    int i;
    if(key!=NULL)
    {
        for (i = 0; i<lines_num; i++)
        {

            if (strcmp(key,variables[i]) == 0) //beware if it's null
            {
                return paths[i];
            }
        }
    }
    return getenv(key);
}
//int compare_string(char *first, char *second) {
//   while (*first == *second) {
//      if (*first == '\0' || *second == '\0')
//         break;
//
//      first++;
//      second++;
//   }
//
//   if (*first == '\0' && *second == '\0')
//      return 0;
//   else
//      return -1;
//}

void set_variable( char* key, char* value )
{
    int i;
    if(key!=NULL && value != NULL)
    {
        if(strcmp(key,"PATH") == 0)
            set_PATH(value);
        for (i = 0; i<lines_num; i++)
        {

            if (strcmp(key,variables[i]) == 0) //beware if it's null
            {
                strcpy(paths[i],value);
                return;
            }
        }
        strcpy(added_variables[i],key);
        strcpy(added_path[i],value);

            variables[i]=added_variables[i];
            paths[i]=added_path[i];
            lines_num++;

    }
    return;
}

void print_all_variables( void )
{
    // you should implement this function
}
