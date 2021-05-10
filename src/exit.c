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
    char ans[10];

    speak_character(GLINDA, "Oh, my dear player, \nDo you really want to exit the game? [Y]es / [N]o, of course.");
    scanf("%s", ans);

    if (!(strncmp(ans, "y", 1) && strncmp(ans, "Y", 1)))
    {
        speak_character(GLINDA, "Ok darling, have a nice day. See ya', dada!");
        return 0;
    }
    else if (!(strncmp(ans, "n", 1) && strncmp(ans, "N", 1)))
    {
        speak_character(GLINDA, "Well, let's play together! Let's go to hell!");
    }
    else
    {
        speak_character(OFELIA, "HAHAHAHAHA, useless ape!");
        printerr("Say something useful, you fool!", THE_SYSTEM);
    }

    return 1;
}