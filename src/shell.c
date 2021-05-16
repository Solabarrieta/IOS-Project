/**
 * @file shell.c
 * @author IOS Lecturer, 2.2 Team
 * @brief Implementation of shell.
 * @version 0.1
 * @date 2021-05-07
 * 
 * @copyright Copyright (c) 2021
 */
#include "headers/libstring/libstring.h"

#include "headers/cd.h"
#include "headers/exit.h"
#include "headers/clear.h"
#include "headers/signal_handler.h"
#include "headers/executor.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXLINE 200
#define MAXARGS 20

/* STATES of the GAME */
#define RESTART -1
#define MENU -2
#define GAME_OVER -3
#define VILLAGE 1
#define GROVE 2
#define HAUNTED_HOUSE 21
#define BASEMENT 211
#define BATHROOM 212
#define BEDROOM 213
#define KITCHEN 214
#define LIVINGROOM 215
#define FOREST_ENTRANCE 3
#define TREES_P 31
#define FOREST 4
#define EMERALD_CITY 5
#define PRAIRIE 6
#define CASTLE 7
/* STATES of the GAME */

/**
 * @brief Read all the entries in a line of written code, for shell.
 * For reading commands.
 * 
 * @param argcp 
 * @param args 
 * @param max 
 * @param eofp 
 * @return int 
 */
int read_args(int *argcp, char *args[], int max, int *eofp)
{
   static char cmd[MAXLINE];
   char *cmdp;
   int ret, i;

   *argcp = 0;
   *eofp = 0;
   i = 0;
   while ((ret = read(0, cmd + i, 1)) == 1)
   {
      if (cmd[i] == '\n')
         break; // correct line
      i++;
      if (i >= MAXLINE)
      {
         ret = -2; // line too long
         break;
      }
   }

   switch (ret)
   {
   case 1:
      cmd[i + 1] = '\0'; // correct reading
      break;
   case 0:
      *eofp = 1; // end of file
      return 0;
      break;
   case -1:
      *argcp = -1; // reading failure
      fprintf(stderr, "Reading failure \n");
      return 0;
      break;
   case -2:
      *argcp = -1; // line too long
      fprintf(stderr, "Line too long -- removed command\n");
      return 0;
      break;
   }
   // Analyzing the line
   cmdp = cmd;
   for (i = 0; i < max; i++)
   { /* to show every argument */
      if ((args[i] = strtok(cmdp, " \t\n")) == (char *)NULL)
         break;
      cmdp = NULL;
   }
   if (i >= max)
   {
      fprintf(stderr, "Too many arguments -- removed command\n");
      return 0;
   }
   *argcp = i;
   return 1;
}

int main(int argcv, char *argv[])
{
   int index, argc, state, eof = 0;
   char *game_dir, *root_dir, *cmd_dir, *current_dir, *prompt_name, *args[MAXARGS], *Prompt = "GlindOS";
   static char *path[10] = {"cat", "cp", "grep", "help", "ls", "man", "mv", "pwd", "touch", "stee"};

   if (argcv == 3)
   {
      root_dir = argv[2];
      game_dir = argv[1];
      state = 1;
   }
   else if (argcv == 4)
   {
      root_dir = argv[2];
      game_dir = argv[1];
      state = (int) argv[3];
   }
   else
   {
      root_dir = getcwd((char *)NULL, 0);
      game_dir = concat(root_dir, "/config/.gamedir/village");
      state = 1;
   }

   cmd_dir = concat(root_dir, "/bin/");

   cd(game_dir);

   while (1)
   {
      current_dir = getcwd((char *)NULL, 0);

      prompt_name = (char *)malloc(strlen(Prompt) + strlen(current_dir) + 6);
      strcpy(prompt_name, Prompt);
      strcat(prompt_name, "[");
      strcat(prompt_name, current_dir);
      strcat(prompt_name, "]$ ");

      write(0, prompt_name, strlen(prompt_name));

      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
      {
         if (!strcmp(args[0], "exit") && (argcv == 4 && state == CASTLE) || (argcv < 4 && state == 1))
         {
            switch (exit_game())
            {
            case 0:
               _exit(0);
               break;

            case -1:
               _exit(1);
               break;
            }
         }
         else if (!strcmp(args[0], "cd"))
         {
            if (argc == 1)
            {
               cd(game_dir);
            }
            else if (argc == 2)
            {
               if (!strncmp(concat(current_dir, "/"), concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/"), strlen(concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/"))))
               {
                  if (!strcmp(args[1], "bedroom") || !strcmp(args[1], "bedroom/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/bedroom/")))
                  {
                     return 213;
                  }
                  else if (!strcmp(args[1], "basement") || !strcmp(args[1], "basement/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/basement/")))
                  {
                     return 211;
                  }
                  else if (!strcmp(args[1], "bathroom") || !strcmp(args[1], "bathroom/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/bathroom/")))
                  {
                     return 212;
                  }
                  else if (!strcmp(args[1], "kitchen") || !strcmp(args[1], "kitchen/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/kitchen/")))
                  {
                     return 214;
                  }
                  else if (!strcmp(args[1], "livingroom") || !strcmp(args[1], "livingroom/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/livingroom/")))
                  {
                     return 215;
                  }
               }

               if (!strcmp(current_dir, game_dir) && !strncmp(args[1], "..", 2))
               {
                  printerr(THE_SYSTEM, "<<The night is dark and full of terrors>>, or that's what The Admin once said.");
                  return 1;
               }
               else
               {
                  cd(args[1]);
               }
            }
            else
            {
               printerr(THE_SYSTEM, "That is not a valid command, player.");
               return 1;
            }
         }
         else if (!strcmp(args[0], "clear"))
         {
            clear_screen();
         }
         else if (!strncmp(args[0], "./", 2))
         {
            execute(argc, args);
         }
         else
         {
            // Check path for the new commands.
            for (index = 0; index < 10; index++)
            {
               if (!strcmp(args[0], path[index]))
               {
                  args[0] = (char *)malloc(strlen(cmd_dir) + strlen(path[index]));
                  strcpy(args[0], cmd_dir);
                  strcat(args[0], path[index]);
                  execute(argc, args);
                  break;
               }
            }
         }
      }

      if (eof)
      {
         exit(0);
      }

      free(prompt_name);
   }

   return 0;
}
