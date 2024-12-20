#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void prompt(void);
void read_input(char *buffer);
void execute_command(char *command);

#endif /* SHELL_H */
