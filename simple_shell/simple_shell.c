#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include "utils.h"

void command_loop();
char **parse(char *input);
void run_command(char **input);
void run_proc(char **input);

#define ESCAPE_SEQUENCES " \t\r\n\a\b\v\f"

int main(int argc, char *argv[]){
	command_loop();
	return 0;
}

// Get input from the user
void command_loop(){
	char *input = NULL;
	char **input_parsed = NULL;
	size_t holder = 24;
	char *proc = "proc";
	char *exit_prompt = "exit\n";
	// Prompt user for command until user enters exit
	do {
		printf(">> ");
		getline(&input, &holder, stdin);
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
		free(input_parsed);
	} while(input != exit_prompt);
}

// Parse the user input string
char **parse(char *input){
	char *token;
	int token_hold = 24;
	char **tokens = malloc(token_hold * sizeof(char*));
	int position = 0;
	token = strtok(input, ESCAPE_SEQUENCES);
	// Loop through user input breaking string into tokens
	do {
		tokens[position] = token;
		position++;
		// Reallocate space if needed
		if(position >= token_hold){
			token_hold += 24;
			tokens = realloc(tokens, token_hold * sizeof(char*));
		}
		token = strtok(NULL, ESCAPE_SEQUENCES);
	} while(token != NULL);
	return tokens;
}

// Run command of the parsed input
void run_command(char **input){
	char **command = input;
	int status;
	pid_t c_pid;
	// Create child process and check if successful
	c_pid = fork();
	if(c_pid == 0){
		execvp(command[0], command);
		fprintf(stderr, "Error: Execvp Failed");
		exit(1);
	}
	else if(c_pid < 0){
		fprintf(stderr, "Error: Fork Failed");
		exit(1);
	}
	else{
		waitpid(c_pid, &status, WUNTRACED);
	}
}

// Displays proc files
void run_proc(char **input){
	// Checks that a file within /proc is specified 
	if(input[1] != NULL){
		char* file = input[1];
		char loc[] = "/proc/";
		strcat(loc, file);
		// Checks that it is accessible
		if(access(loc, F_OK) != -1){
			FILE *f = fopen(loc, "r");
			char display;
			display = fgetc(f);
			// Prints out contents until end of file
			while(display != EOF){
				printf("%c", display);
				display = fgetc(f);
			}
			fclose(f);
			printf("\n");
		}
		else{
			fprintf(stderr, "Error: could not access file");
		}
	}
	else{
		fprintf(stderr, "Error: additional information needed");
	}
}
