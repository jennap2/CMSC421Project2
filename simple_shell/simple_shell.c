#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "utils.h"

char *command_loop(void);
char **parse(char **input);
void run_command(char **input);

#define ESCAPE_SEQUENCES " \t\r\n\a"

int main(int argc, char *argv[]){
	command_loop();
	return 0;
}

// Get input from the user
char *command_loop(void){
	char *input = NULL;
	char **input_parsed = NULL;
	size_t buff = 24;
	int pos = 0;
	do {
		printf(">> ");
		getline(&input, &buff, stdin);
		if(strcmp(input, "exit\n") == 0){
			free(input);
			exit(0);
		}
		input_parsed = parse(input);
		run_command(input_parsed);
		for(int i = 0; i < pos; i++){
			free(input_parsed[i]);
		}
		free(input_parsed);
	} while(input != "exit\n");
	return input;
}

// Parse the user input string
char **parse(char **input){
	int token_buff = 24;
	char **tokens = malloc(token_buff * sizeof(char*));
	char *token;
	int pos = 0;
	token = strtok(input, ESCAPE_SEQUENCES);
	do {
		tokens[pos] = token;
		pos++;
		if(pos  >= token_buff){
			token_buff += 24;
			tokens = realloc(tokens, token_buff * sizeof(char*));
		}
		token = strtok(NULL, ESCAPE_SEQUENCES);
	} while(token != NULL);
	return tokens;
}

// Run command of the parsed input
void run_command(char **input){
	char **command = input;
	int status;
	pid_t child_pid;
	child_pid = fork();
	if(child_pid == 0){
		execvp(command[0], command);
		exit(1);
	}
	else if(child_pid < 0){
		fprintf(stderr, "Error: Fork Failed");
		exit(1);
	}
	else{
		do{
			waitpid(child_pid, &status, WUNTRACED);
		}while(!WIFSIGNALED(status) && !WIFEXITED(status));
	}
}
