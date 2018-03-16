#include "command_parser.h"
#include "variables.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#define numOfStrings 50
#define ANSI_COLOR_RESET   "\x1b[0m"

char *token;
int indicator,i = 0;
char *parsCommand[numOfStrings];
void RemoveTabs(char* source)
{
    char* i = source;
    char* j = source;
    while(*j != '\0')
    {
        *i = *j++;
        if(*i != '\t')
            i++;
    }
    *i = '\0';
}
int Count_Occurences(char* source)
{
    int count = 0;
    char *pch=strchr(source,'"');
    while (pch!=NULL)
    {
        count++;
        pch=strchr(pch+1,'"');
    }
    if (count % 2 == 0)
        return count / 2;
    return 0;
}
void handle_Home_sign(){
char* word;
char  new_command[100][100]={{0}};
char* nC;
int k;
int index = 0;
nC = new_command[index];
for(k = 0;k<i;k++){
    word = parsCommand[k];
    if(strchr(word,'~') == NULL){
        continue;
    }else{
    while(*word != '\0'){
        if(*word == '~'){
            word++;
            if(*word == '/' || *word == '\0'){
                strcat(new_command[index],lookup_variable("HOME"));
                nC += strlen(lookup_variable("HOME"));
            }else{
                *nC = '~';
                nC++;
                *nC = *word;
                nC++;
                word++;
            }
        }else{
        *nC = *word;
        word++;
        nC++;
        }
    }
    parsCommand[k] = new_command[index];
    index++;
    nC = new_command[index];
    }
}
}
void handle_dollars()////////////////////////////handle echo c$1123
{
    int k;
    int index=0,count=0,k_tok = 0;
    char *word;
    char *value; //value of the value from lookup
    int ech_flag = 0;
    char tok[50][512] = {{0}};
    char vari[50] = "";
    char *v=vari;
    for(k = 0; k < i ; k++)
    {
        word = parsCommand[k];
        if(strchr(word,'$')==NULL && strcmp(word,"echo")!=0) //statement don't contain a $ && not echo
        {
            strcat(tok[k_tok],parsCommand[k]);
            k_tok++;
            continue;
        }
        if (strcmp(word,"$")==0)
        {
            strcat(tok[k_tok],parsCommand[k]);
            k_tok++;

            continue;
        }
        else if(strcmp(word,"echo") == 0)
        {
            strcat(tok[k_tok],parsCommand[k]);
            k_tok++;

            ech_flag=1;
            continue;

        }
        while(*word != '\0')
        {
            if(*word == '$')
            {
                word++;
//
                if(!((*word>= 'a' && *word <= 'z') || (*word>= 'A' && *word <= 'Z') || (*word == '_')))//if first char is valid add to *v
                {
                    *v = *word;
                    word++;//inc pointers
                    v++;//inc pointers
                    count++;//inc size of var
                    continue;
                }
                while(isalnum(*word) || *word == '_')//rest of the word is valid
                {
                    *v = *word;
                    word++;//inc pointers
                    v++;//inc pointers
                    count++;//inc size of var
                    if(*word == '\0')
                        break;
                }
                *v = '\0';
                value = lookup_variable(vari);
                if (value == NULL)
                {
                    strcat(tok[k_tok],"");
                    index+=count+1;
                }
                else if(ech_flag == 0 && (strchr(value,' ') || strchr(value,'\t')))
                {
                    RemoveTabs(value);
                    char* splitted = strtok(value, " ");
                    while( splitted != NULL )
                    {
                        strcat(tok[k_tok],splitted);
                        splitted = strtok(NULL, " ");
                        if(splitted != NULL)
                            k_tok++;
                    }
                }
                else
                {
                    strcat(tok[k_tok],value);
                    index += strlen(value);
                }
            }
            else
            {
                tok[k_tok][index] = *word;
                index++;
                word++;
            }
            memset(vari, 0, sizeof vari);//reinitialize
            v = vari;
        }
        k_tok++;

    }
    i=k_tok;
    for(k=0; k<k_tok; k++)
    {
        parsCommand[k] = tok[k];
    }
}
int check_empty(char* source)
{
    int count = 1;
    char *pch=source;
    while (*pch!='\0')
    {
        if(*pch != ' ')
        {
            count--;
            break;
        }
        pch++;
    }
    return count;
}
void handle_var_set()
{
    char *tok;
    char vari[50] = "";
    char valu[50] = "";
    //int l=0,m=0;
    char *v=vari;
    char *al=valu;
    int cond1= (strcmp(parsCommand[0],"export") == 0 && i == 2 && strchr(parsCommand[1],'=') != NULL);
    int cond2= (i == 1 && strchr(parsCommand[0],'=') != NULL);
    if(cond1 || cond2)
    {
        if(cond1)
            tok = parsCommand[1];
        else
            tok = parsCommand[0];

        if(*tok == '=' || !((*tok>= 'a' && *tok <= 'z') || (*tok>= 'A' && *tok <= 'Z') || (*tok == '_'))) //check first char no left hand or wrong case
        {
            printf("Wrong variable name.\n");
            indicator = 3;
            return;
        }
        while(*tok != '=')
        {
            if(isalnum(*tok) || *tok == '_')
            {
                *v = *tok;
                tok++;
                v++;

            }
            else
            {
                printf("Wrong variable name.\n");
                indicator = 3;
                return;
            }

        }
        tok++;
        while(*tok != '\0')
        {
//
            *al = *tok;
            tok++;
            al++;
//
        }
        set_variable(vari,valu);

        indicator = 3;//set variable
    }
}
void handle_bgd()
{
    char* point;
    if(indicator != 3)//if not variable set
    {
        point = parsCommand[i-1]; //point to the last token in the instruction

        char last = *(point+strlen(point)-1);//check last char if it was &
        if(last == '&')
        {
            *(point+strlen(point)-1) = '\0';// make & null ////////////////////////////////
            if(strcmp(point,"")==0) //check if & was a already a removed token (became null)
            {
                i--;
            }
            indicator = 4; //background command
        }
    }

}

void parse_command( char* command )
{
    char *p = strchr(command, '\n');  // finds first, if any, \n
    if (p != NULL) *p = '\0'; //check last element it not null then it equals /n so we set it to NULL
    i = 0;
    if(strlen(command)>511)
    {
        printf("ERROR");
        return;
    }
    else
    {
        if(command[0] == '#')
        {
            parsCommand[i] = command;
            i++;
            indicator = 0; //comment
        }


        else if (strstr(command, "#") != NULL)
        {
            // contains // but not in the beginning
            char *p = strtok(command, "#");
            parse_command(p);
        }
        else if (strstr(command,"\"") != NULL)
        {
            char q_command[50][100] = {{0}};
            int j=0;
            int count = 0;
            char* start = command;
            while(*start != '\0')
            {
                if(((*start == ' ') || (*start == '\t')) && ((count % 2) == 0))
                {
                    while(*start == ' ' || *start == '\t')
                    {
                        start++;
                        if(*start == '\0')
                            break;
                    }
                }
                else if (*start == '"')
                {
                    count++;
                    start++;
                    while(*start != '"')
                    {
                        q_command[i][j]=  *start;
                        j++;
                        start++;

                        if(*start == '\0')
                            break;
                    }
                    j = 0;
                    i++;
                    if(*start == '"')
                    {
                        count++;
                        start++;
                    }
                }
                else
                {
                    while(*start != ' ' && *start != '\t' && *start != '\0')//////////////y="ls -l"
                    {
                        if(*start == '"')
                        {
                            count++;
                            start++;
                            while(*start != '"')
                            {
                                q_command[i][j]=  *start;
                                j++;
                                start++;

                                if(*start == '\0')
                                    break;
                            }
                            if(*start == '"')
                            {
                                count++;
                                start++;
                            }
                            continue;
                        }
                        ////////
                        q_command[i][j]=  *start;
                        j++;
                        start++;
                        if(*start == '\0')
                            break;
                    }
                    j = 0;
                    i++;
                }
            }
            int k;
            for(k = 0; k < i; k++)
            {
                parsCommand[k]=q_command[k];
                //printf("comm: %s \n",parsCommand[k]);

            }
            handle_dollars();
            indicator = 2;
            handle_var_set();
            handle_bgd();
            handle_Home_sign();
        }
        else
        {
            /* get the first token */
            RemoveTabs(command); /////////////////////////
            if(strlen(command) == 0 || check_empty(command)) //handle tabs or spaces only lines
            {
                indicator = -1;
                parsCommand[i] = "";
                i++;
                return;
            }

            token = strtok(command, " ");

            /* walk through other tokens */
            while( token != NULL )
            {
                if(strcmp(token,"") != 0)
                {
                    parsCommand[i] = token;
                    i++;
                }
                token = strtok(NULL, " ");
            }
            handle_dollars();
            indicator = 2; //normal command
            handle_var_set();
            handle_bgd();
            handle_Home_sign();
        }
    }
}
int get_indicator()
{
    return indicator;
}
int get_command_length()
{
    return i;
}
void get_clean_command(char** a)
{
    int j ;
    for(j = 0; j<i ; j++)
    {
        a[j] = parsCommand[j];

    }
printf(">>>>>>>>>>Done Parsing<<<<<<<<<<<<< \n");
}

