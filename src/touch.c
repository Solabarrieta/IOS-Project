/**
 * @file touch.c
 * @author Mikel Aristu
 *
 * @brief The command used to create items.
 *
 * @version 0.3
 * @date 2021-03-24
 *
 * @copyright Copyright (c) 2021
 * 
 */

#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printerr(THE_SYSTEM, "Oh no, you hit your hand while you where making that tool!");
        return 1;
    }

    int file_desc = creat(argv[1], S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

    if (file_desc == -1)
    {
        printerr(THE_SYSTEM, "Impossible to create a file here!");
        return 1;
    }

    close(file_desc);

    return 0;
}
