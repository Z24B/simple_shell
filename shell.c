#include "shell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_INPUT_SIZE 1024

/**
 * prompt_display - display shell prompt
 * Return: void
 */
void prompt_display(void)
{
	printf("$ ");
	fflush(stdout);
}

/**
 * execute_command - execute user command
 * @command: given command
 * Return: void
 */
void execute_command(char *command)
{
	pid_t pid = fork();
	int status;

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		/* Child Process */
		execlp(command, command, (char *)NULL);

		/* If execlp fails, print an error message using perror */
		fprintf(stderr, "%s: %s: command not found\n", __FILE__, command);
		exit(EXIT_FAILURE);
	}
	else
	{
		/* Parent Process - wait for child process to complete */
		waitpid(pid, &status, 0);

		if (WIFEXITED(status))
		{
			/* Child process exited normally */
			printf("Child process exited with status %d\n", WEXITSTATUS(status));
		}
		else if (WIFSIGNALED(status))
		{
			/* Child process terminated by a signal */
			printf("Child process terminated by signal %d\n", WTERMSIG(status));
		}
	}
}

/**
 * process_interactive - process commands
 * Return: void
 */
void process_interactive(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		prompt_display();
		if (fgets(input, MAX_INPUT_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}
		input[strcspn(input, "\n")] = '\0';
		execute_command(input);
	}
}

/**
 * process_script - process commands from script
 * @script_filename: parameter
 * Return: void
 */
void process_script(char *script_filename)
{
	FILE *file;
	char line[MAX_INPUT_SIZE];

	file = fopen(script_filename, "r");

	if (file == NULL)
	{
		perror("fopen");
		exit(EXIT_FAILURE);
	}
	while (fgets(line, sizeof(line), file) != NULL)
	{
		line[strcspn(line, "\n")] = '\0';
		execute_command(line);
	}
	fclose(file);
}

/**
 * main - begin shell process
 * @argc: argument
 * @argv: argument
 * Return: void
 */
int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		process_interactive();
	}
	else if (argc == 2)
	{
		process_script(argv[1]);
	}
	else
	{
		fprintf(stderr, "Usage: %s [script]\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	return (0);
}
