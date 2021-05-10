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
#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"

#include <unistd.h>
#include <errno.h>

int cd(char *path)
{
    if (chdir((const char *)path) == -1)
    {
        // If the directory is not found.
        if (errno = ENOENT)
        {
            printerr("No DIR found. %ERROR!", THE_SYSTEM);
            speak_character(GLINDA, "It look like that place you mean doesn't exist, my dear sweet child.");
            speak_character(GLINDA, "You'd better apply in you Geography lectures, if you don't want to loose yourself.");
        }
        else
        {
            // If the directory is not readable, then throw error and exit.
            printerr("No DIR found. %ERROR!\n Revise your internal configuration, player.", THE_SYSTEM);
        }

        return 1;
    }

    return 0;
}