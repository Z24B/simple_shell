#include "shell.h"

int main(void)
{
    char *buffer = malloc(BUFFER_SIZE);
    if (!buffer)
    {
        perror("Unable to allocate memory");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        prompt();
        read_input(buffer);
        execute_command(buffer);
    }

    free(buffer);
    return 0;
}

void prompt(void)
{
    if (isatty(STDIN_FILENO))
        write(STDOUT_FILENO, "#prompt$ ", 9);
}

void read_input(char *buffer)
{
    ssize_t bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE - 1);
    if (bytes_read == -1)
    {
        perror("Error reading input");
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';
    if (bytes_read == 0)
    {
        write(STDOUT_FILENO, "\n", 1);
        exit(EXIT_SUCCESS);
    }
    buffer[strcspn(buffer, "\n")] = '\0';
}

void execute_command(char *command)
{
    pid_t pid = fork();
    if (pid == -1)
    {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    }
    if (pid == 0)
    {
        char *argv[2];
        argv[0] = command;
        argv[1] = NULL;
        if (execve(command, argv, NULL) == -1)
        {
            perror(command);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        wait(NULL);
    }
}
