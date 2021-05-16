/**
 * @file cd.c
 * @author Mikel Aristu, David Cuenca Marcos
 * @brief Utilities to deal with files, directories.
 * @version 3
 * @date 2021-04-16
 * 
 * @copyright Copyright (c) 2021
 */
#include "headers/cd.h"
#include "headers/libstring/libstring.h"

#include <unistd.h>
#include <errno.h>

int cd(char *path)
{
    int ch_result = chdir((const char *)path);

    if (ch_result == -1)
    {
        printerr(THE_SYSTEM, "No such directory!");
        return 1;
    }

    return 0;
}