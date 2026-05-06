//<stdio.h> for printf()fgets()stdin; Input/output.
#include <stdio.h>
// <stdlib.h> for strtol() exit(); 
#include <stdlib.h>
// <limits.h> for INT_MIN and INT_MAX; 
#include <limits.h>
// <errno.h> for errno and ERANGE
#include <errno.h>
// <ctype.h> for isspace()
#include <ctype.h>
// <string.h> for strchr()
#include <string.h>
// <sys/types.h> for ssize_t
#include <sys/types.h>


int get_int(const char *prompt)
{
    // Buffer to hold user input and pointer for strtol
    char buffer[100];
    // Loop until valid input is received
    while (1)
    {
        if (prompt != NULL)
        {
            printf("%s", prompt);
        }
        
        // Read input from user
        if (fgets(buffer, sizeof(buffer), stdin) == NULL)
        {
            printf("Input closed.\n");
            exit(1);
        }
        // If fgets doesn't read '\n', input exceeded buffer → flush stdin
        if (strchr(buffer, '\n') == NULL)
        {
            int ch;
            int too_long = 0;

            while ((ch = getchar()) != '\n' && ch != EOF)
            {
                too_long = 1;
            }

            if (too_long)
            {
                printf("Input too long.\n");
                continue;
            }
        }
        
        // Reset errno before strtol, since it's global and may carry old errors
        errno = 0;
        char *end;
        long value = strtol(buffer, &end, 10);
        // No digits were found at start of input
        if (end == buffer)
        {
            printf("Invalid input.\n");
            continue;
        }
        // skip whitespace to ensure no trailing garbage
        while (isspace((unsigned char)*end))
        {
            end++;
        }
        // Check for extra characters after the number
        if (*end != '\0')
        {
            printf("Extra characters found.\n");
            continue;
        }
        // errno == ERANGE → overflow/underflow
        if (errno == ERANGE || value < INT_MIN || value > INT_MAX)
        {
            printf("Out of range.\n");
            continue;
        }

        return (int)value;
    }
}
// get_string() prompts user for string input
char *get_string(const char *prompt)
{
    // Prompt user if prompt is not NULL
    if (prompt != NULL)
    {
        printf("%s", prompt);
        fflush(stdout); // Ensure prompt is printed before input
    }

    // Buffer to hold user input and pointer for getline
    char *line = NULL;
    size_t size = 0;
    // Read input from user
    ssize_t nread = getline(&line, &size, stdin);
    // Check for errors or EOF
    if (nread == -1)
    {
        free(line);
        return NULL; // EOF or error
    }
    // Remove trailing newline if present
    if (nread > 0 && line[nread - 1] == '\n')
    {
        line[nread - 1] = '\0';
    }

    return line;
}
int main(void)
{
    char *name = get_string("What is your name?: ");
    if (!name)
    {
    fprintf(stderr, "Input closed.\n");
    return 1;
    }
    
    printf("Hello, %s\n", name);
    free(name);
    int age = get_int("Age: ");
    printf("Age = %d\n", age);
    int height = get_int("Height: ");
    printf("Height = %d\n", height);
    int weight = get_int("Weight: ");
    printf("Weight = %d\n", weight);
    return 0;
}