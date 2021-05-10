#include "headers/recognizer.h"
#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void wait_until_enter()
{
    do
    {

    } while (getchar() != 10);
}

int read_doc(char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *buff;
    char *word;

    while (read(fd, buff, 1) == 1)
    {
        if (*buff == '_')
        {
            write(1, ADMIN, 7);
        }
        else if (*buff == '*')
        {
            write(1, OFELIA, strlen(OFELIA));
        }
        else if (*buff == '%')
        {
            write(1, GLINDA, strlen(GLINDA));
        }
        else if (*buff == '$')
        {
            write(1, SCARECROWN, strlen(SCARECROWN));
        }
        else
        {
            write(1, buff, 1);

            if (*buff == '.' || *buff == '!' || *buff == '?')
            {
                write(1, "\n", 1);
                wait_until_enter();
            }
        }
    }

    close(fd);

    return 0;
}
