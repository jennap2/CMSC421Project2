#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "utils.h"

char *command_loop(void);
char **parse(char *input);
void run_command(char **input);
void run_proc(char **input);

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
	char *proc = "proc";
	char *exit_prompt = "exit\n";
	// Prompt user for command until user enters exit
	do {
		printf(">> ");
		getline(&input, &buff, stdin);
		// If user enters exit deallocate and exit
		if(strcmp(input, exit_prompt) == 0){
			free(input);
			exit(0);
		}
		// Parse user input, if parsed input is a proc command call proc function
		input_parsed = parse(input);
		if(strcmp(input_parsed[0], proc) == 0){
			run_proc(input_parsed);
		}
		else{
			run_command(input_parsed);
		}
		// Deallocate parsed input
		for(int i = 0; i < pos; i++){
			free(input_parsed[i]);
		}
		free(input_parsed);
	} while(input != exit_prompt);
	return input;
}

// Parse the user input string
char **parse(char *input){
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
	// Create child process
	child_pid = fork();
	if(child_pid == 0){
		execvp(command[0], command);
		printf(stderr, "Error: Execvp Failed");
		exit(1);
	}
	else if(child_pid < 0){
		printf(stderr, "Error: Fork Failed");
		exit(1);
	}
	else{
		do{
			waitpid(child_pid, &status, WUNTRACED);
		}while(!WIFSIGNALED(status) && !WIFEXITED(status));
	}
}

// Displays proc files
void run_proc(char **input){
	// Checks that a file within /proc is specified 
	if(input[1] != NULL){
		char* file = input[1];
		char begin[24] = "/proc/";
		strcat(begin, file);
		// Checks that it is accessible
		if(access(begin, F_OK) == 0){
			FILE *f = fopen(begin, "r");
			char display = " ";
			// Prints out contents
			while(display != EOF){
				display = fgetc(f);
				printf("%c", display);
			}
			fclose(f);
			printf("%s"," \n");
		}
		else{
			printf("%s", "Error: could not open file");
		}
	}
	else{
		printf("Error: additional information needed");
	}
}
