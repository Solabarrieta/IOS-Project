/**
 * @file exit.c
 * @author David Cuenca Marcos
 * @brief Exit command implementation.
 * @version 2
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"
#include "headers/exit.h"
#include <stdlib.h>
#include <stdio.h>

int exit_game()
{
    char ans;
    scanf(concat(GLINDA, ": Do you really want to exit the game? [Y]es / [N]o, of course %c\n"), &ans);

    if (ans == 'y' || ans == 'Y')
    {
        speak_character(GLINDA, "Ok darling, have a nice day. See ya', dada!");
        return 0;
    }
    else if (ans == 'n' || ans == 'N')
    {
        speak_character(GLINDA, "Well, let's play together! Let's go to hell!");
        return 1;
    }
    else
    {
        printerr(THE_SYSTEM, "Say something useful, you fool!");
        return -1;
    }
}