#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/* Function to display the shell prompt */
void prompt_display(void);

/* Function to execute a command */
void execute_command(char *command);

int main(int argc, char *argv[]);
void process_interactive(void);
void process_script(char *script_filename);

#endif
