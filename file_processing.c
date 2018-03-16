#include "file_processing.h"
#include "variables.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
	history file section
*/
FILE* fp_batch;
FILE* fp_history;
FILE* fp_log;

void open_history_file()
{
char PATH[512];
strcpy(PATH,lookup_variable("PROJECT"));
strcat(PATH,"/history.txt");
fp_history=fopen(PATH, "a");
if (fp_history != NULL)
    fprintf(fp_history, "Command>> ");
	// you should implement this function
}

FILE* get_history_file()
{
	// you should implement this function
	return fp_history;
}

void close_history_file()
{
	// you should implement this function
    fclose(fp_history);
}
void print_history(){
char buffer[512]="";
char PATH[512]="";

char *line;
strcpy(PATH,lookup_variable("PROJECT"));
strcat(PATH,"/history.txt");
fp_history=fopen(PATH, "r");
printf("HISTORY:\n");
if (fp_history != NULL)
{
    line = fgets(buffer, sizeof buffer, (FILE*)fp_history);
    while(line != NULL){
        printf("%s",line);
        line = fgets(buffer, sizeof buffer, (FILE*)fp_history);
    }
    fclose(fp_history);
}
}

/*
	log file section
*/
void open_log_file()
{
	// you should implement this function
	char PATH[512];
strcpy(PATH,lookup_variable("PROJECT"));
strcat(PATH,"/log.txt");
fp_log=fopen(PATH, "a");
if (fp_log != NULL)
    fprintf(fp_log, "Command>> ");
}

FILE* get_log_file()
{
	// you should implement this function
	return fp_log;
}

void close_log_file()
{
	// you should implement this function
	fclose(fp_log);

}


/*
	CommandsBatch file section
*/
void open_commands_batch_file(char * path)
{
fp_batch = fopen(path, "r");
// you should implement this function
}

FILE* get_commands_batch_file()
{
	// you should implement this function
	return fp_batch;
}

void close_commands_batch_file()
{
	// you should implement this function
    printf("file closed \n");
	fclose(fp_batch);

}
