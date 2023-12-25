#include "functions.h"

int main()
{
    FILE *file_ptr;
    const int SIZE = 100;
    char input[SIZE];
    char name[SIZE];
    while (1)
    {
        printf("Choose: opening/creating/deleting a new file(open/create/delete/exit): ");
        scanf("%s", &input);
        if (strcmp(input, "create") == 0)
        {
            printf("Please, enter the name of a file without the format (example): ");
            scanf("%s", &name);
            strcat(name, ".txt");
            CreateFile(name);
        }
        else if (strcmp(input, "delete") == 0)
        {
            printf("Please, enter the name of a file without the format (example): ");
            scanf("%s", &name);
            strcat(name, ".txt");
            DeleteFile(name);
        }
        else if (strcmp(input, "open") == 0)
        {
            printf("Please, enter the name of a file without the format (example): ");
            scanf("%s", &name);
            strcat(name, ".txt");
            OpenFile(name);
        }
        else
        {
            return 0;
        }
    }
    return 0;
}