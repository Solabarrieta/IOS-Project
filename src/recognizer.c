#include "headers/recognizer.h"
#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

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
    char character, *word, text[10000], *split[10000];
    int i, j, main_fd = open(filename, O_RDONLY);

    // Process the text and extract the speech.
    for (i = 0; i < 9999; i++)
    {
        text[i] = ' ';
    }

    text[9999] = '\0';

    i = 0;
    while (read(main_fd, &character, 1) == 1 || character == '\n')
    {
        text[i++] = character;
    }

    close(main_fd);

    // Split all the words by spaces.
    for (i = 0; i < 10000; i++)
    {
        if (i == 0)
        {
            split[i] = strtok(text, " \n");
        }
        else
        {
            split[i] = strtok(NULL, " \n");
        }

        if (split[i] == NULL)
        {
            break;
        }
    }

    // Then, process the speech.
    for (j = 0; j < i; j++)
    {
        word = split[j];
        character = split[j][strlen(split[j]) - 1];

        if (!strcmp(to_lowercase(word), "badwitch"))
        {
            print(OFELIA);
        }
        else if (!strcmp(to_lowercase(word), "goodwitch"))
        {
            print(GLINDA);
        }
        else if (!strcmp(to_lowercase(word), "admin"))
        {
            print(ADMIN);
        }
        else if (!strcmp(to_lowercase(word), "scarecrow"))
        {
            print(SCARECROWN);
        }
        else if (!strcmp(to_lowercase(word), "tinman"))
        {
            print(TINMAN);
        }
        else if (!strcmp(to_lowercase(word), "lion"))
        {
            print(LION);
        }
        else if (!strcmp(to_lowercase(word), "dog") || !strcmp(to_lowercase(word), "toto"))
        {
            print(DOG);
        }
        else if (!strcmp(to_lowercase(word), "trees"))
        {
            print(TREES);
        }
        else if (!strcmp(to_lowercase(word), "guardian"))
        {
            print(GUARDIAN);
        }
        else if (!strcmp(to_lowercase(word), "ghost") || !strcmp(to_lowercase(word), "casper"))
        {
            print(GHOST);
        }
        else if (is_command(to_lowercase(word)))
        {
            if (!strcmp(to_lowercase(word), "cat"))
            {
                print(concat(ANSI_COLOR_MAGENTA, "CAT"));
            }
            else if (!strcmp(to_lowercase(word), "cp"))
            {
                print(concat(ANSI_COLOR_MAGENTA, "CP"));
            }
            else if (!strcmp(to_lowercase(word), "grep"))
            {
                print(concat(ANSI_COLOR_MAGENTA, "GREP"));
            }
            else if (!strcmp(to_lowercase(word), "help"))
            {
                print(concat(ANSI_COLOR_GREEN, "HELP"));
            }
            else if (!strcmp(to_lowercase(word), "ls"))
            {
                print(concat(ANSI_COLOR_YELLOW, "LS"));
            }
            else if (!strcmp(to_lowercase(word), "man"))
            {
                print(concat(ANSI_COLOR_GREEN, "MAN"));
            }
            else if (!strcmp(to_lowercase(word), "mv"))
            {
                print(concat(ANSI_COLOR_MAGENTA, "MV"));
            }
            else if (!strcmp(to_lowercase(word), "pwd"))
            {
                print(concat(ANSI_COLOR_YELLOW, "PWD"));
            }
            else if (!strcmp(to_lowercase(word), "touch"))
            {
                print(concat(ANSI_COLOR_BLUE, "TOUCH"));
            }
            else if (!strcmp(to_lowercase(word), "stee"))
            {
                print(concat(ANSI_COLOR_WHITE, "STEE"));
            }
            else if (!strcmp(to_lowercase(word), "exit"))
            {
                print(concat(ANSI_COLOR_RED, "EXIT"));
            }
            else if (!strcmp(to_lowercase(word), "cd"))
            {
                print(concat(ANSI_COLOR_CYAN, "CD"));
            }
        }
        else
        {
            word = (char *)malloc(strlen(split[j]) - 1);

            for (int k = 0; k < strlen(split[j]) - 1; k++)
            {
                word[k] = split[j][k];
            }

            if (!strcmp(to_lowercase(word), "badwitch"))
            {
                print(OFELIA);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "goodwitch"))
            {
                print(GLINDA);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "admin"))
            {
                print(ADMIN);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "scarecrow"))
            {
                print(SCARECROWN);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "tinman"))
            {
                print(TINMAN);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "lion"))
            {
                print(LION);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "dog") || !strcmp(to_lowercase(word), "toto"))
            {
                print(DOG);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "trees"))
            {
                print(TREES);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "guardian"))
            {
                print(GUARDIAN);
                write(1, &character, 1);
            }
            else if (!strcmp(to_lowercase(word), "ghost") || !strcmp(to_lowercase(word), "casper"))
            {
                print(GHOST);
                write(1, &character, 1);
            }
            else if (is_command(to_lowercase(word)))
            {
                if (!strcmp(to_lowercase(word), "cat"))
                {
                    print(concat(ANSI_COLOR_MAGENTA, "CAT"));
                }
                else if (!strcmp(to_lowercase(word), "cp"))
                {
                    print(concat(ANSI_COLOR_MAGENTA, "CP"));
                }
                else if (!strcmp(to_lowercase(word), "grep"))
                {
                    print(concat(ANSI_COLOR_MAGENTA, "GREP"));
                }
                else if (!strcmp(to_lowercase(word), "help"))
                {
                    print(concat(ANSI_COLOR_GREEN, "HELP"));
                }
                else if (!strcmp(to_lowercase(word), "ls"))
                {
                    print(concat(ANSI_COLOR_YELLOW, "LS"));
                }
                else if (!strcmp(to_lowercase(word), "man"))
                {
                    print(concat(ANSI_COLOR_GREEN, "MAN"));
                }
                else if (!strcmp(to_lowercase(word), "mv"))
                {
                    print(concat(ANSI_COLOR_MAGENTA, "MV"));
                }
                else if (!strcmp(to_lowercase(word), "pwd"))
                {
                    print(concat(ANSI_COLOR_YELLOW, "PWD"));
                }
                else if (!strcmp(to_lowercase(word), "touch"))
                {
                    print(concat(ANSI_COLOR_BLUE, "TOUCH"));
                }
                else if (!strcmp(to_lowercase(word), "stee"))
                {
                    print(concat(ANSI_COLOR_WHITE, "STEE"));
                }
                else if (!strcmp(to_lowercase(word), "exit"))
                {
                    print(concat(ANSI_COLOR_RED, "EXIT"));
                }
                else if (!strcmp(to_lowercase(word), "cd"))
                {
                    print(concat(ANSI_COLOR_CYAN, "CD"));
                }

                write(1, &character, 1);
            }
            else
            {
                if (is_uppercase(split[j]))
                {
                    print(bold(concat(ANSI_COLOR_YELLOW, split[j])));
                }
                else
                {
                    print(split[j]);
                }
            }
        }

        if (character == '.' || character == '!' || character == '?')
        {
            println(bold(" << Press ENTER key to continue... >> "));
            wait_until_enter();
        }
        else
        {
            print(" ");
        }
    }

    close(main_fd);

    println(" ");

    return 0;
}