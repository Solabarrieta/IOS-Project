/**
 * @file stee.c
 * @author Mikel Aristu
 * @brief The command that saves the name of the player.
 * @version 0.4
 * @date 2021-04-30
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

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      printerr("Error! You don't even know how to write you name, you ape? OK, write <<stee \"your_name\">>", THE_SYSTEM);
      return 1;
   }

   char *name = (char *) calloc(10, sizeof(char));
   unlink(argv[1]);
   int namefile = creat(argv[1], S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);

   if (namefile == -1)
   {
      printerr(THE_SYSTEM, "Oh! I cannot access that file!");
      return 1;
   }

   speak_character(GLINDA, "What's your name, darling?");
   scanf("%s", name);
   
   // Write the string to file (max 10 char).
   write(namefile, name, strlen(name));

   free(name);
   close(namefile);

   println("Welcome!");

   return 0;
}