/**
 * @file cp.c
 * @author Mikel Aristu, David Cuenca, Team 2.2
 * @brief cp command to copy files
 * @version 0.2
 * @date 2021-04-23
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printerr(THE_SYSTEM, "Please, usage: <<cp file new_file>>");
        return 1;
    }

    int origin, end, oread, owrite;
    char *buffer;

    origin = open(argv[1], O_RDONLY);

    if (origin == -1)
    {
        printerr(THE_SYSTEM, "Error opening the origin file.");
        return 1;
    }

    end = open(argv[2], O_RDWR | O_CREAT, S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if (end == -1)
    {
        printerr(THE_SYSTEM, "Error creating copy! No such permissions.");
        return 1;
    }

    do
    {
        oread = read(origin, buffer, 1);

        if (write(end, buffer, 1) != oread)
        {
            printerr(THE_SYSTEM, "Error writing in destination!");
            return 1;
        }
    } while (oread == 1);

    return 0;
}