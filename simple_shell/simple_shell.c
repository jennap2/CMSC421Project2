#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "utils.h"

char *command_loop(void);
char **parse(char *input, int*);

int main(int argc, char *argv[]){
	command_loop();
	return 0;
}

// Get input from the user
char *command_loop(void){
	char *input = NULL;
	char **input_parsed = NULL;
	size_t buff = 4;
	int pos = 0;
	do {
		printf(">> ");
		getline(&input, &buff, stdin);
		if(strcmp(input, "exit") == 0){
			free(input);
			exit(0);
		}
		input_parsed = parse(input, &pos);
		for(int i = 0; i < pos; i++){
			free(input_parsed[i]);
		}
		free(input_parsed);
	} while(input != "exit");
	return input;
}

// Parse the user input string
char **parse(char *input, int *pos){
}
