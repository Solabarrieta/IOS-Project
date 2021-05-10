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

    while (read(fd, buff, 1) == 1)
    {
        if (*buff == '_')
        {
            write(1, "PLAYER", 7);
        }
        else if (!strncmp("Badwitch", buff, 9))
        {
            write(1, OFELIA, strlen(OFELIA));
            // lseek(1, strlen(OFELIA), SEEK_CUR);
        }
        else if (!strncmp("Goodwitch", buff, 10))
        {
            write(1, GLINDA, strlen(GLINDA));
            // lseek(1, strlen(GLINDA), SEEK_CUR);
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
