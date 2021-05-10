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
    int main_fd = open(filename, O_RDONLY);
    int secd_fd = open(filename, O_RDONLY);

    char character, word, *taboo[2] = {"Badwitch", "Goodwitch"};
    int i, broken;

    while (read(main_fd, &character, 1) == 1)
    {
        i = 0;
        broken = 0;

        read(secd_fd, &word, 1);

        while (!((word == ',' || word == '.' || word == '?' || word == '!' || word == '\n' || word == ' ')))
        {
            if (word != taboo[0][i++])
            {
                broken = 1;
                break;
            }

            read(secd_fd, &word, 1);
        }

        if (!broken && (i == strlen(taboo[0])))
        {
            print(OFELIA);
            lseek(main_fd, i - 1, SEEK_CUR);
            lseek(secd_fd, strlen(OFELIA), SEEK_CUR);
        }

        if (character == '_')
        {
            write(1, ADMIN, 7);
        }
        else if (character == '*')
        {
            write(1, OFELIA, strlen(OFELIA));
        }
        else if (character == '%')
        {
            write(1, GLINDA, strlen(GLINDA));
        }
        else if (character == '$')
        {
            write(1, SCARECROWN, strlen(SCARECROWN));
        }
        else
        {
            write(1, &character, 1);

            if (character == '.' || character == '!' || character == '?')
            {
                write(1, "\n", 1);
                wait_until_enter();
            }
        }
    }

    close(main_fd);
    close(secd_fd);

    return 0;
}
