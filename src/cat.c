/**
 * @file cat.c
 * @author Mikel Aristu, David Cuenca, Team 2.2
 * @brief The command used to read files.
 * @version 3
 * @date 2021-05-04
 * @copyright Copyright (c) 2021
 *
 */
#include "headers/libstring/libstring.h"
#include "headers/characters/character.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      // If the command is used incorrectly, it will teach the player how to use it.
      printerr("No, no, no. Usage: cat file_name. Revise your notes, please.", THE_SYSTEM);
      speak_character(GLINDA, "Please, remember to go to class, player. It is good for you, sweety.");

      return 1;
   }

   char *character;
   int file_descriptor;
   ssize_t bytes_read;

   // Open the file in read-only mode.
   file_descriptor = open(argv[1], O_RDONLY);

   // If there is any error when trying to open the file.
   if (file_descriptor == -1)
   {
      printerr(THE_SYSTEM, "Error while opening the file.");
      printerr(THE_SYSTEM, "YOU DON'T EVEN KNOW TO READ!!!");
      return 1;
   }

   // Read the file, while read 1 byte (char) at a time.
   do
   {
      bytes_read = read(file_descriptor, character, 1);
      print(character);
   } while (bytes_read == 1);

   close(file_descriptor);

   return 0;
}