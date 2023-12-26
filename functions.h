#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#define MAX_LINE 2048
#define TEMP_SIZE 1000
#define BUFFER_SIZE 1000
#define COLUMNS 3
void printTableHeader()
{

    printf("| %-35s | %-25s | %-25s |\n", "Oblast", "Population", "Square");
}
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
void removeWhiteSpaces(char *str)
{
    int start = 0, end = strlen(str) - 1;

    while (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r')
    {
        start++;
    }

    while (end >= 0 && (str[end] == ' ' || str[end] == '\t' || str[end] == '\n' || str[end] == '\r'))
    {
        end--;
    }

    int length = end - start + 1;

    memmove(str, str + start, length);

    str[length] = '\0';
}
int handleInput(FILE *file, const char *name, int linecount)
{
    char buffer[BUFFER_SIZE];

    char ***arr = (char ***)malloc(linecount * sizeof(char **));
    for (int i = 0; i < linecount; i++)
    {
        arr[i] = (char **)malloc(COLUMNS * sizeof(char *));
        for (int j = 0; j < 3; j++)
        {
            arr[i][j] = (char *)malloc(BUFFER_SIZE * sizeof(char));
        }
    }

    for (int i = 0; i < linecount; i += 1)
    {

        printf("Enter the city: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        removeWhiteSpaces(buffer);
        strcpy(arr[i][0], buffer);

        printf("Enter the population: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        removeWhiteSpaces(buffer);
        strcpy(arr[i][1], buffer);

        printf("Enter the square: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        removeWhiteSpaces(buffer);
        strcpy(arr[i][2], buffer);

        fprintf(file, "| %-35s | %-25s | %-25s |\n", arr[i][0], arr[i][1], arr[i][2]);
    }
    for (int i = 0; i < linecount; i++)
    {
        for (int j = 0; j < COLUMNS; j++)
        {
            free(arr[i][j]);
        }
        free(arr[i]);
    }
    free(arr);
}

int WriteLines(const char *name)
{
    int linecount = getInput("\nEnter number of lines you want to write: ");
    while ((getchar()) != '\n')
        ;

    FILE *file_ptr = fopen(name, "a");
    if (file_ptr == NULL)
    {
        char buf[256];
        strerror_r(errno, buf, 256);
        printf("Error opening file(s) because: %s\n", buf);
        return 1;
    }

    handleInput(file_ptr, name, linecount);
    fclose(file_ptr);

    return 0;
}

int PasteLine(const char *name)
{
    FILE *file_ptr, *temp;
    char temp_filename[TEMP_SIZE];
    char buffer[MAX_LINE];
    char newLine[MAX_LINE];
    strcpy(temp_filename, "temp____");
    strcat(temp_filename, name);
    int write_line = getInput("Line number: ");
    printf("New line: ");
    fflush(stdin);
    fgets(newLine, MAX_LINE, stdin);
    file_ptr = fopen(name, "r");
    temp = fopen(temp_filename, "w");
    if (file_ptr == NULL || temp == NULL)
    {
        char buf[256];
        strerror_r(errno, buf, 256);
        printf("Error opening file(s) because: %s\n", buf);
        return 1;
    }
    bool keep_reading = true;
    int current_line = 1;
    do
    {
        fgets(buffer, MAX_LINE, file_ptr);
        if (feof(file_ptr))
        {
            keep_reading = false;
        }
        else if (write_line == current_line)
        {

            printf("Enter the city: ");
            fgets(newLine, MAX_LINE, stdin);
            removeWhiteSpaces(newLine);
            fprintf(temp, "| %-35s |", newLine);

            printf("Enter the population: ");
            fgets(newLine, MAX_LINE, stdin);
            removeWhiteSpaces(newLine);
            fprintf(temp, " %-25s |", newLine);

            printf("Enter the square: ");
            fgets(newLine, MAX_LINE, stdin);
            removeWhiteSpaces(newLine);
            fprintf(temp, " %-25s |\n", newLine);
            fputs(buffer, temp);
        }
        else
        {
            fputs(buffer, temp);
        }
        current_line += 1;
    } while (keep_reading);
    fclose(file_ptr);
    fclose(temp);
    remove(name);
    rename(temp_filename, name);
}
int DeleteLine(const char *name)
{
    FILE *file_ptr, *temp;
    char temp_filename[TEMP_SIZE];
    char buffer[MAX_LINE];

    strcpy(temp_filename, "temp____");
    strcat(temp_filename, name);

    int delete_line = getInput("\nDelete line number: ");
    file_ptr = fopen(name, "r");
    temp = fopen(temp_filename, "w");
    if (file_ptr == NULL || temp == NULL)
    {
        char buf[256];
        strerror_r(errno, buf, 256);
        printf("Error opening file(s) because: %s\n", buf);
        return 1;
    }
    bool keep_reading = true;
    int current_line = 1;
    do
    {
        fgets(buffer, MAX_LINE, file_ptr);
        if (feof(file_ptr))
        {
            keep_reading = false;
        }
        else if (delete_line != current_line)
        {
            fputs(buffer, temp);
        }
        current_line += 1;
    } while (keep_reading);
    fclose(file_ptr);
    fclose(temp);
    remove(name);
    rename(temp_filename, name);
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
    char buffer[MAX_LINE];
    printTableHeader();
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
    char buffer[MAX_LINE];
    printTableHeader();
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
    int option = getInput("\nEnter your option: ");
    switch (option)
    {
    case 1:
        ReadLine(name);
        break;
    case 2:
        ReadFile(name);
        break;
    case 4:
        PasteLine(name);
        break;
    case 5:
        DeleteLine(name);
        break;
    case 3:
        WriteLines(name);
        break;
    }
}
