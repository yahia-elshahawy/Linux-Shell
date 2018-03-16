Shell: main.o command.o file_processing.o variables.o command_parser.o environment.o executer.o
	gcc -o Shell main.o command.o file_processing.o variables.o command_parser.o environment.o executer.o

main.o: main.c command.h file_processing.h variables.h command_parser.h environment.h executer.h
	 gcc -c main.c

command.o: command.c command.h
	     gcc -c command.c

file_processing.o: file_processing.c file_processing.h
			gcc -c file_processing.c

variables.o: variables.c variables.h
		gcc -c variables.c

command_parser.o: command_parser.c command_parser.h
			gcc -c command_parser.c

environment.o: environment.c environment.h
		gcc -c environment.c

executer.o: executer.c executer.h
		gcc -c executer.c

clean: 
	rm *.o Shell
