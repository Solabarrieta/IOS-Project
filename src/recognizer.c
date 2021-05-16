#include "headers/recognizer.h"
#include "headers/libstring/libstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>
#include <sys/stat.h>
#include <math.h>

char *to_lowercase(char *word)
{
    char *res = (char *)malloc(strlen(word));

    for (int i = 0; i < strlen(word); i++)
    {
        res[i] = (char)tolower(word[i]);
    }

    return res;
}

int is_uppercase(char *word)
{
    for (int i = 0; i < strlen(word); i++)
    {
        if (!isupper(word[i]))
        {
            return 0;
        }
    }

    return 1;
}

void wait_until_enter()
{
    do
    {

    } while (getchar() != 10);
}

int is_command(char *cmd)
{
    int n = 12;
    char *path[12] = {"cat", "cp", "grep", "help", "ls", "man", "mv", "pwd", "touch", "stee", "exit", "cd"};

    for (int i = 0; i < n; i++)
    {
        if (!strcmp(cmd, path[i]))
        {
            return 1;
        }
    }

    return 0;
}

int read_doc(char *filename)
{
    char character;
    int main_fd = open(filename, O_RDONLY);

    while (read(main_fd, &character, 1) == 1)
    {
        if (character == '\n')
        {
            write(1, &character, 1);
            print("\n");
        }
        else
        {
            write(1, &character, 1);
            
            if (character == '.' || character == '!' || character == '?')
            {
                print("...");
                wait_until_enter();
            }
        }
    }

    close(main_fd);

    println("");

    return 0;
}