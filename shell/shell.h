/* Jacob Chapin */
/* Simple Shell Header File */

// Max lenth for the command line
#define MAX_COMMAND_LINE_LENGTH 1000

// Shell prompt
#define SHELL_PROMPT            "swell shell:"

// Command execution function
void takeCommand(char* command);

// Argument splitting function
char** argsplitter(char* arg, char* tokarg, int* argcounter);
