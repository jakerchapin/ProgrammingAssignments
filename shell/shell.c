/* This was done in Spring 2016 */
/* The purpose of this project was to make our own shell */

/* Jacob Chapin */
/* OS Programming assignment 1 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "shell.h"

int main()
{
	int shell = 1; //Make the shell
	int swell = 1; //Make it swell
	char shellinput[MAX_COMMAND_LINE_LENGTH];  // Variable to hold shell input
  
	while (shell == swell) // While the shell is swell
	{
		// Display our prompt
		printf("%s ", SHELL_PROMPT);
		// Wait for a command   [reading from stdin]
		fgets(shellinput, MAX_COMMAND_LINE_LENGTH, stdin);
		// Removing trailing \n from command
		shellinput[strlen(shellinput)-1] = '\0';
		// By default, the printf command prints to stdout
		if (strcmp(shellinput, "exit") == 0)   // exit the swell shell
		{
			return 0;
		}
		else
		{
			/* Execute command */
			takeCommand(shellinput);
		}
	}
	return 0;
}

/* Take command and execute it, after doing a bunch of other things */
void takeCommand(char* command)
{
	/* Initialize needed variables and split command */
	int i = 0;
	int argcount = 0;
	char* command_cpy = strdup(command);
	char** args = argsplitter(command_cpy, " ", &argcount); //get array of arguments
	
	/* append NULL or replace & with NULL */
	/* ensure argcount is equal to number of arguments, not including the ending NULL */
	int bg = 0;
	if (strcmp(args[argcount-1], "&") == 0)
	{
		bg = 1;
		args[argcount-1] = NULL;
		argcount--;
	}
	else
	{
		args = realloc(args, sizeof(char*) * (argcount+1));
		args[argcount] = NULL;
	}

	/* Check for pipes or redirections */
	/* if one of these characters is found, prepare to rewrite args list */
	int redir_out = 0;
	int redir_in = 0;
	int redir_pipe = 0;
	int redir = 0; // this gets set to 1 to confirm that redirection must take place
	for (i = 0; i < argcount; i++)
	{
		if (strcmp(args[i], "<") == 0)
		{
			redir_in = i+1;
			redir = 1;
			break;
		}
		if (strcmp(args[i], ">") == 0)
		{
			redir_out = i+1;
			redir = 1;
			break;
		}
		if (strcmp(args[i], "|") == 0)
		{
			redir_pipe = i+1;
			redir = 1;
			break;
		}
	}
	/* Argument array is created; now execute command */
	if (redir_pipe > 0)
	{
		/* Piping requires a different approach than usual */
		/* Copy args */
		char** args_cpy = (char**)calloc(argcount+1, sizeof(char*));
			for (i = 0; i <= argcount; i++)
			{
				args_cpy[i] = args[i];
			}		
		int childProc;
		int childProc2;
		int fds[2];
		pipe(fds);
		/* Fork the children to be executed */
		childProc = fork();
		if (childProc < 0)
		{
			printf("Oh no! fork failed!\n");
			free(args);
			free(args_cpy);
			return;
		}
		if (childProc == 0)
		{
			close(fds[0]);
			dup2(fds[1], STDOUT_FILENO); //redirect STDOUT of first process to pipe
			close(fds[1]);
			args = realloc(args, sizeof(char*) * redir_pipe); //trim args
			args[redir_pipe-1] = NULL; //get new NULL ending
			if (execvp(args[0], args) < 0)
			{
				printf("Oh no! execvp failed!\n");
				free(args);
				free(args_cpy);
				return;
			}
			_exit(EXIT_FAILURE);
		}
		childProc2 = fork();
		if (childProc2 < 0)
		{
			printf("Oh no! fork failed!\n");
			free(args);
			free(args_cpy);
			return;
		}
		else if (childProc2 == 0)
		{
			close(fds[1]);
			dup2(fds[0], STDIN_FILENO);
			close(fds[0]);
			int argcount2 = (argcount - redir_pipe);
			args = realloc(args, sizeof(char*) * (argcount2 + 1)); //second args
			int k; // second iterator
			for (i = (redir_pipe), k = 0; i <= argcount; i++, k++)
			{
				args[k] = args_cpy[i];
			}
			if (execvp(args[0], args) < 0)
			{
				printf("Oh no! execvp failed!\n");
				free(args);
				free(args_cpy);
				return;
			}
			_exit(EXIT_FAILURE);
		}
		close(fds[0]);
		close(fds[1]);
		if (bg == 0)
		{
			waitpid(childProc, NULL, 0);
			waitpid(childProc2, NULL, 0);
		}
		free(args);
		free(args_cpy);
		return;
	}
	if(strcmp(args[0], "cd") == 0)
	{
		chdir(args[1]);
	}
	else
	{
		pid_t pid = fork();
		if (pid < 0)
		{
			printf("Oh no! fork failed!\n");
			return;
		}
		else if (pid > 0)
		{
			if (bg == 0)
			{
				int status;
				waitpid(pid, &status, 0);
			}
		}
		else if (pid == 0)
		{
			/* See if we have redirection or a pipe */
			if (redir == 1)
			{
				/* We have redirection or a pipe */
				/* Copy args */
				char** args_cpy = (char**)calloc(argcount+1, sizeof(char*));
				for (i = 0; i <= argcount; i++)
				{
					args_cpy[i] = args[i];
				}
				if(redir_out > 0)
				{
					args = realloc(args, sizeof(char*) * redir_out); //trim args
					args[redir_out-1] = NULL; //set new end of args to NULL
					int opfile = open(args_cpy[redir_out], O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR); //open target file
					if (opfile < 0) //make sure file opening succeeded
					{
						printf("Oh no! File opening failed!\n");
						free(args);
						free(args_cpy);
						return;
					}
					dup2(opfile, 1); //send stdout to file
					close(opfile); //close file
					free(args_cpy); //free args_cpy, it won't be needed anymore
				}
				if(redir_in > 0)
				{
					args = realloc(args, sizeof(char*) * redir_in); //trim args
					args[redir_in-1] = NULL; //set new end of args to NULL
					int opfile = open(args_cpy[redir_in], O_RDONLY); //open target file
					if (opfile < 0) // make sure file opening succeeded
					{
						printf("Oh no! file opening failed!\n");
						free(args);
						free(args_cpy);
						return;
					}
					dup2(opfile, 0); //get input from file
					close(opfile); //close file
					free(args_cpy); //free args_cpy, it won't be needed anymore
				}
			}
			if(execvp(args[0], args) < 0) //execute command
			{
				printf("Oh no! execvp failed!\n");
				free(args);
				return;
			}
		}
	}
	free(args);
	return;
}

/* Argument splitting function */
char** argsplitter(char* arg, char* tokarg, int *argcounter)
{
	int argcount = 0;
	char** args = NULL;
	char* argument = strtok(arg, tokarg);
	while (argument != NULL)
	{
		/* Use realloc to resize the array with each argument added */
		args = realloc(args, sizeof(char*) * ++argcount);
		if (args == NULL)
		{
			printf("Oh no! Memory allocation failure!\n");
			exit(-1);
		}
		args[argcount-1] = argument; // Add argument to array
		argument = strtok(NULL, " "); // Get next argument
	}
	free(argument); //free this so it doesn't hang around in memory
	*argcounter = argcount;
	return args;
}
