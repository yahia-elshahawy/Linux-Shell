#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include "command.h"
#include "environment.h"
#include "command_parser.h"
#include "file_processing.h"
#include "variables.h"
#include "executer.h"
#define size 512
//colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

char reader[512];
void handle_finish()
{
    open_log_file();
    FILE* fp_log = get_log_file();
    if(fp_log != NULL)
    {fprintf(fp_log,"Child Process Terminated\n");
    close_log_file();}
}
void print_Welcoming(){
printf(""ANSI_COLOR_BLUE);
printf("____    __    ____  _______  __        ______   ______   .___  ___.  _______    .___________.  ______        \n");
printf("\\   \\  /  \\  /   / |   ____||  |      /      | /  __  \\  |   \\/   | |   ____|   |           | /  __  \\       \n");
printf(" \\   \\/    \\/   /  |  |__   |  |     |  ,----'|  |  |  | |  \\  /  | |  |__      `---|  |----`|  |  |  |      \n");
printf("  \\            /   |   __|  |  |     |  |     |  |  |  | |  |\\/|  | |   __|         |  |     |  |  |  |      \n");
printf("   \\    /\\    /    |  |____ |  `----.|  `----.|  `--'  | |  |  |  | |  |____        |  |     |  `--'  |      \n");
printf("    \\__/  \\__/     |_______||_______| \\______| \\______/  |__|  |__| |_______|       |__|      \\______/       \n");
printf("\n");
printf(" _______  __          _______. __    __       ___       __    __       ___   ____    __    ____ ____    ____  __     _______.\n");
printf("|   ____||  |        /       ||  |  |  |     /   \\     |  |  |  |     /   \\  \\   \\  /  \\  /   / \\   \\  /   / (_ )   /       |\n");
printf("|  |__   |  |       |   (----`|  |__|  |    /  ^  \\    |  |__|  |    /  ^  \\  \\   \\/    \\/   /   \\   \\/   /   |/   |   (----`\n");
printf("|   __|  |  |        \\   \\    |   __   |   /  /_\\  \\   |   __   |   /  /_\\  \\  \\            /     \\_    _/          \\   \\    \n");
printf("|  |____ |  `----.----)   |   |  |  |  |  /  _____  \\  |  |  |  |  /  _____  \\  \\    /\\    /        |  |        .----)   |   \n");
printf("|_______||_______|_______/    |__|  |__| /__/     \\__\\ |__|  |__| /__/     \\__\\  \\__/  \\__/         |__|        |_______/    \n");
printf("\n");
printf(" __  .__   __. .___________. _______ .______          ___       ______ .___________. __  ____    ____  _______               \n");
printf("|  | |  \\ |  | |           ||   ____||   _  \\        /   \\     /      ||           ||  | \\   \\  /   / |   ____|              \n");
printf("|  | |   \\|  | `---|  |----`|  |__   |  |_)  |      /  ^  \\   |  ,----'`---|  |----`|  |  \\   \\/   /  |  |__                 \n");
printf("|  | |  . `  |     |  |     |   __|  |      /      /  /_\\  \\  |  |         |  |     |  |   \\      /   |   __|                \n");
printf("|  | |  |\\   |     |  |     |  |____ |  |\\  \\----./  _____  \\ |  `----.    |  |     |  |    \\    /    |  |____               \n");
printf("|__| |__| \\__|     |__|     |_______|| _| `._____/__/     \\__\\ \\______|    |__|     |__|     \\__/     |_______|              \n");
printf("\n");
printf("     _______. __    __   _______  __       __      ___  ___                                                  \n");
printf("    /       ||  |  |  | |   ____||  |     |  |     \\  \\ \\  \\                                                 \n");
printf("   |   (----`|  |__|  | |  |__   |  |     |  |      \\  \\ \\  \\                                                \n");
printf("    \\   \\    |   __   | |   __|  |  |     |  |       >  > >  >                                               \n");
printf(".----)   |   |  |  |  | |  |____ |  `----.|  `----. /  / /  /                                                \n");
printf("|_______/    |__|  |__| |_______||_______||_______|/__/ /__/                                                 \n");
printf(""ANSI_COLOR_RESET);
}
int main(int argc, char *argv[])
{

    // any other early configuration should be here
    setup_environment();
    Constructor();//set variable tables
    print_Welcoming();

    int read_from_file = 0,from_file = 0;
    FILE* fp;

    if (argc > 2) //if arguments ! ./executable path
    {
        printf("" ANSI_COLOR_RED);
        printf("ERROR: arguments is too many\n");
        printf("" ANSI_COLOR_RESET);
        return 0;
    }
    else
    {
            if( argc > 1 )
            {
                printf("" ANSI_COLOR_YELLOW);
                printf("Read File \n");
                printf("" ANSI_COLOR_RESET);
                read_from_file = 1;
            }
            else
            {
                printf("" ANSI_COLOR_YELLOW);
                printf("Shell Commands \n");
                printf("" ANSI_COLOR_RESET);
                read_from_file = 0;
            }
    }

    cd(""); // let shell starts from home

    if(read_from_file)
    {
        open_commands_batch_file(argv[1]);
        fp = get_commands_batch_file();
        if (fp == NULL)
        {
            printf("" ANSI_COLOR_RED);
            printf("ERROR:No Such batch file\n");
            printf("" ANSI_COLOR_RESET);
            exit(0);
        }
        printf("" ANSI_COLOR_YELLOW);
        printf("from_file Success \n");
        printf("" ANSI_COLOR_RESET);
        from_file = 1;
    }
    else
    {

        from_file = 0;
        printf("" ANSI_COLOR_YELLOW);
        printf("shell loop Entered\n");
        printf("" ANSI_COLOR_RESET);
    }
    char buffer[512];
    char* line;
    FILE* fp_history;

    while(1)
    {
        open_history_file();
        fp_history = get_history_file();
        if(from_file)
        {
            line = fgets(buffer, sizeof buffer, (FILE*) fp);
            if(line != NULL )  //read next instruction from file
            {
                if(line[0] == '\n' || line[0] == '\r')
                    continue;
                //printf("%s", buffer);
                printf("" ANSI_COLOR_MAGENTA);
                printf("\n >>Command: %s \n",line);
                printf("" ANSI_COLOR_RESET);
                if (fp_history != NULL)
                {
                    fprintf(fp_history,"%s",line);
                    close_history_file();
                }
                parse_command(line);
            }

            else             // if end of file {from_file = false; continue;}
            {
                from_file = 0;
                close_commands_batch_file();
                continue;
            }

        }
        else
        {

            //read next instruction from console
            printf("" ANSI_COLOR_GREEN);
            char cwd[512];
            if (getcwd(cwd, sizeof(cwd)) != NULL){
            printf("%s: %s: Shell>>",getenv("USER"),cwd);
            }
            printf("" ANSI_COLOR_CYAN);
            line = fgets(buffer, sizeof buffer, stdin);
            printf("" ANSI_COLOR_RESET);
            if(line != NULL )
            {
                if(line[0] == '\n' || line[0] == '\r')
                    continue;
                if (fp_history != NULL)
                {
                    fprintf(fp_history,"%s",line);
                    close_history_file();
                }

                parse_command(line);
            }else{ //ctrl-D entered
                exit(0);
            }
        }
        errno = 0;
        int comm_len=0;
        comm_len = get_command_length(); //get instruction length after cleaning

        char* comm[comm_len+1];
        comm[comm_len] = '\0';
        get_clean_command(comm);
        if(strcmp(comm[0],"cd") == 0 )
        {
            if(comm_len > 2)
                {
                    printf("" ANSI_COLOR_RED);
                    printf("ERROR : Wrong number of arguments\n");
                    printf("" ANSI_COLOR_RESET);
                }
            else
            {
                if(get_indicator() == 1 || comm_len==1)
                    cd("");
                else
                    cd(comm[1]);
            }

        }
        else if(strcmp(comm[0],"exit") == 0 && comm_len == 1)
        {
            printf("" ANSI_COLOR_MAGENTA);
            perror("Status:");
            exit(0);
        }else if(strcmp(comm[0],"history") == 0 && comm_len == 1)
        {
            printf("" ANSI_COLOR_MAGENTA);
            perror("Status:");
            printf("" ANSI_COLOR_RESET);
            print_history();
            continue;
        }
        else if(get_indicator() == 0) //comment
        {
            printf("" ANSI_COLOR_MAGENTA);
            printf("Status: Ignored comment\n");
            printf("" ANSI_COLOR_RESET);
            continue;
        }
        else if (get_indicator() == -1) //empty
        {
            continue;
        }
        else if (get_indicator() == 3) //set variable
        {
            printf("" ANSI_COLOR_MAGENTA);
            printf("Status: DONE\n");
            printf("" ANSI_COLOR_RESET);
            continue;
        }
        else
        {
            pid_t child_pid;
            signal(SIGCHLD,handle_finish);
            child_pid =fork();
            if(child_pid==0)
            {
                execute(comm[0], comm);
                //abort();
            }
            else
            {
                if(get_indicator() != 4) //if not background command
                {
                    waitpid(child_pid, NULL, 0);///////////
                }
            }
        }
    }

    return 0;
}
