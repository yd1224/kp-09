#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
bool isScientificNotation(const char *input)
{
    int len = strlen(input);
    int eCount = 0;
    int digitsBeforeE = 0;
    int digitsAfterE = 0;

    for (int i = 0; i < len; i++)
    {
        char c = input[i];
        if (c == 'e' || c == 'E')
        {
            eCount++;
        }
        else if (isdigit(c) && eCount == 0)
        {
            digitsBeforeE++;
        }
        else if (isdigit(c) && eCount == 1)
        {
            digitsAfterE++;
        }
    }

    return (eCount == 1) && (digitsBeforeE > 0) && (digitsAfterE > 0);
}
double getInput(const char *prompt)
{
    const int SIZE = 100;
    char input[SIZE];
    double number;

    do
    {
        printf("%s", prompt);
        scanf("%s", input);

        int invalidInput = 0;
        for (int i = 0; input[i]; i++)
        {
            if (isdigit(input[i]) == 0 && input[i] != '.' && input[i] != '-' && !isScientificNotation(input))
            {
                printf("\nYour input is invalid\n");
                invalidInput = 1;
                break;
            }
        }

        if (!invalidInput)
        {
            number = atof(input);
            break;
        }
    } while (1);

    return number;
}

int CreateFile(const char *name)
{
    FILE *file_ptr;
    file_ptr = fopen(name, "w");
    if (file_ptr == NULL)
    {
        printf("Error of creating the file.\n");
        return 1;
    }
    else
    {
        printf("Created file successfully.\n");
    }
    fclose(file_ptr);
}
void DeleteFile(const char *name)
{
    int res = remove(name);
    if (res == 0)
    {
        printf("Removed file successfully\n");
    }
    else
    {
        char buf[256];
        strerror_r(errno, buf, 256);
        printf("Failed to remove because: %s\n", buf);
    }
}
int ReadLine(const char *name)
{
    int read_line = getInput("\nRead line number: ");
    FILE *file_ptr;
    file_ptr = fopen(name, "r");
    if (file_ptr == NULL)
    {
        char buf[256];
        strerror_r(errno, buf, 256);
        printf("Error opening file because: %s\n", buf);
        return 1;
    }

    bool line_found = false;
    int current_line = 1;
    const int MAX_LINE = 2048;
    char buffer[MAX_LINE];

    while (fgets(buffer, MAX_LINE, file_ptr) != NULL)
    {
        if (current_line == read_line)
        {
            line_found = true;
            printf("Line: \n%s\n", buffer);
            break;
        }
        current_line += 1;
    }

    if (!line_found)
    {
        printf("File %d lines.\n", current_line - 1);
        printf("Couldn't find line %d.\n", read_line);
    }

    fclose(file_ptr);
    return 0;
}

int ReadFile(const char *name)
{

    FILE *file_ptr;
    file_ptr = fopen(name, "r");
    if (file_ptr == NULL)
    {
        char buf[256];
        strerror_r(errno, buf, 256);
        printf("Error opening file because: %s\n", buf);
        return 1;
    }
    bool keep_reading = true;
    int current_line = 1;
    const int MAX_LINE = 2048;
    char buffer[MAX_LINE];
    do
    {
        fgets(buffer, MAX_LINE, file_ptr);
        if (feof(file_ptr))
        {
            keep_reading = false;
        }

        printf("Line %d: %s", current_line, buffer);

        current_line += 1;
    } while (keep_reading);
    printf("\n");
    fclose(file_ptr);
}
void OpenFile(const char *name)
{
    FILE *file_ptr;
    printf("+------------------------------------+\n");
    printf("| Option |       Function            |\n");
    printf("+------------------------------------+\n");
    printf("|   1    |      Read line            |\n");
    printf("|   2    |      Read file            |\n");
    printf("|   3    |      Write                |\n");
    printf("|   4    |      Paste line           |\n");
    printf("|   5    |      Delete line          |\n");
    printf("|   6    |      Sort file            |\n");
    printf("|   7    |      Change line          |\n");
    printf("+------------------------------------+\n");
    printf("%s", name);
    int option = getInput("\nEnter your option: ");
    switch (option)
    {
    case 1:
        ReadLine(name);
        break;
    case 2:
        ReadFile(name);
        break;
    }
}
