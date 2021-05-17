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

#include "headers/game.h"

#define MAXLINE 200
#define MAXARGS 20

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
   int index, state, argc, eof = 0;
   char *game_dir, *root_dir, *cmd_dir, *current_dir, *prompt_name, *args[MAXARGS], *Prompt = "GlindOS";
   static char *path[10] = {"cat", "cp", "grep", "help", "ls", "man", "mv", "pwd", "touch", "stee"};

   if (argcv == 3)
   {
      root_dir = argv[2];
      game_dir = argv[1];

      if (strstr(game_dir, "castle") != NULL)
      {
         state = CASTLE;
      }
      else if (strstr(game_dir, "prairie") != NULL)
      {
         state = PRAIRIE;
      }
      else if (strstr(game_dir, "emerald_city") != NULL)
      {
         state = EMERALD_CITY;
      }
      else if (strstr(game_dir, "forest") != NULL)
      {
         state = FOREST;
      }
      else if (strstr(game_dir, ".trees") != NULL)
      {
         state = TREES_P;
      }
      else if (strstr(game_dir, "forest_entrance") != NULL)
      {
         state = FOREST_ENTRANCE;
      }
      else if (strstr(game_dir, ".haunted_house") != NULL)
      {
         state = HAUNTED_HOUSE;
      }
      else if (strstr(game_dir, "grove") != NULL)
      {
         state = GROVE;
      }
      else if (strstr(game_dir, "village") != NULL)
      {
         state = VILLAGE;
      }
      else
      {
         state = MENU;
      }
   }
   else
   {
      root_dir = getcwd((char *)NULL, 0);
      game_dir = concat(root_dir, "/config/.gamedir/village/");
      state = MENU;
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

      argc = 0;

      if (read_args(&argc, args, MAXARGS, &eof) && argc > 0)
      {
         if (!strcmp(args[0], "clear"))
         {
            clear_screen();
         }
         else
         {
            switch (state)
            {
            case VILLAGE:
               if (argc < 3 && !strcmp(args[0], "ls"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  execute(argc, args);
               }
               else if (argc == 1 && !strcmp(args[0], "cd"))
               {
                  cd(".");
               }
               else if (argc == 1)
               {
                  if (!strcmp(args[0], "pwd") || !strcmp(args[0], "help") || !strcmp(args[0], "man"))
                  {
                     if (argc == 1)
                     {
                        args[0] = concat(cmd_dir, args[0]);
                        execute(argc, args);
                     }
                  }
                  else if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
                  {
                     return 0;
                  }
                  else
                  {
                     return 1;
                  }
               }
               else if (argc == 2)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     if (!strcmp(current_dir, game_dir) && !strncmp(args[1], "..", 2))
                     {
                        printerr(THE_SYSTEM, "<<The night is dark and full of terrors>>, or that's what The Admin once said.");
                        return 1;
                     }

                     if (!strcmp(args[1], "grove") || !strcmp(args[1], "grove/") || !strcmp(args[1], concat(game_dir, "grove/")))
                     {
                        cd(args[1]);
                     }
                     else
                     {
                        return 1;
                     }
                  }
               }
               else
               {
                  return 1;
               }

               break;

            case GROVE:
               if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
               {
                  return 0;
               }

               if (!strcmp(args[0], "pwd"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  execute(argc, args);
               }
               else if (argc > 1)
               {
                  printerr(THE_SYSTEM, "Your only available command is PWD. Remember it, player.");
                  return 1;
               }

               break;

            case HAUNTED_HOUSE:
               if (!strcmp(args[0], "ls"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  execute(argc, args);
               }
               else if (argc == 2)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     if (!strcmp(current_dir, game_dir) && !strncmp(args[1], "..", 2))
                     {
                        printerr(THE_SYSTEM, "<<The night is dark and full of terrors>>, or that's what The Admin once said.");
                        return 1;
                     }

                     if (!strcmp(args[1], "basement") || !strcmp(args[1], "basement/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/basement/")))
                     {
                        return BASEMENT;
                     }
                     else if (!strcmp(args[1], "bathroom") || !strcmp(args[1], "bathroom/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/bathroom/")))
                     {
                        return BATHROOM;
                     }
                     else if (!strcmp(args[1], "bedroom") || !strcmp(args[1], "bedroom/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/bedroom/")))
                     {
                        return BEDROOM;
                     }
                     else if (!strcmp(args[1], "kitchen") || !strcmp(args[1], "kitchen/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/kitchen/")))
                     {
                        return KITCHEN;
                     }
                     else if (!strcmp(args[1], "livingroom") || !strcmp(args[1], "livingroom/") || !strcmp(args[1], concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/livingroom/")))
                     {
                        return LIVINGROOM;
                     }
                  }
               }
               else if (argc == 1)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     cd(".");
                  }
                  else if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
                  {
                     return 0;
                  }
               }
               else
               {
                  return 1;
               }

               break;

            case BASEMENT:
               game_dir = concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/");

               if (!strcmp(args[0], "ls"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  execute(argc, args);
               }
               else if (argc == 2)
               {
                  if (!strcmp(argv[0], "cd"))
                  {
                     if (!strcmp(current_dir, game_dir) && !strncmp(args[1], "..", 2))
                     {
                        printerr(THE_SYSTEM, "<<The night is dark and full of terrors>>, or that's what The Admin once said.");
                        return 1;
                     }
                     else if (!strcmp(args[1], ".."))
                     {
                        return HAUNTED_HOUSE;
                     }
                  }
                  else if (!strcmp(args[1], "cat"))
                  {
                     args[0] = concat(cmd_dir, args[0]);
                     if (!execute(argc, args))
                     {
                        return FOREST_ENTRANCE;
                     }
                  }
               }
               else if (argc == 1)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     cd(".");
                  }
                  else if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
                  {
                     return 0;
                  }
               }
               else
               {
                  return 1;
               }

               break;

            case BATHROOM:
               game_dir = concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/");

               if (!strcmp(args[0], "ls"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  execute(argc, args);
               }
               else if (argc == 2)
               {
                  if (!strcmp(argv[0], "cd"))
                  {
                     if (!strcmp(current_dir, game_dir) && !strncmp(args[1], "..", 2))
                     {
                        printerr(THE_SYSTEM, "<<The night is dark and full of terrors>>, or that's what The Admin once said.");
                        return 1;
                     }
                     else if (!strcmp(args[1], ".."))
                     {
                        return HAUNTED_HOUSE;
                     }
                  }
               }
               else if (argc == 1)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     cd(".");
                  }
                  else if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
                  {
                     return 0;
                  }
               }
               else
               {
                  return 1;
               }
               break;

            case BEDROOM:
               game_dir = concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/");

               if (!strcmp(args[0], "ls"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  execute(argc, args);
               }
               else if (argc == 2)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     if (!strcmp(current_dir, game_dir) && !strncmp(args[1], "..", 2))
                     {
                        printerr(THE_SYSTEM, "<<The night is dark and full of terrors>>, or that's what The Admin once said.");
                        return 1;
                     }
                     else if (!strcmp(args[1], ".."))
                     {
                        return HAUNTED_HOUSE;
                     }
                  }
               }
               else if (argc == 1)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     cd(".");
                  }
                  else if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
                  {
                     return 0;
                  }
               }
               else
               {
                  //TODO:IMPLEMENT getpass
                  return 1;
               }

               break;

            case KITCHEN:
               game_dir = concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/");

               if (!strcmp(args[0], "ls"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  execute(argc, args);
               }
               else if (argc == 2)
               {
                  if (!strcmp(argv[0], "cd"))
                  {
                     if (!strcmp(current_dir, game_dir) && !strncmp(args[1], "..", 2))
                     {
                        printerr(THE_SYSTEM, "<<The night is dark and full of terrors>>, or that's what The Admin once said.");
                        return 1;
                     }
                     else if (!strcmp(args[1], ".."))
                     {
                        return HAUNTED_HOUSE;
                     }
                  }
               }
               else if (argc == 1)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     cd(".");
                  }
                  else if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
                  {
                     return 0;
                  }
               }
               else
               {
                  return 1;
               }

               break;

            case LIVINGROOM:
               game_dir = concat(root_dir, "/config/.gamedir/village/grove/.haunted_house/");

               if (!strcmp(args[0], "ls"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  execute(argc, args);
               }
               else if (argc == 2)
               {
                  if (!strcmp(argv[0], "cd"))
                  {
                     if (!strcmp(current_dir, game_dir) && !strncmp(args[1], "..", 2))
                     {
                        printerr(THE_SYSTEM, "<<The night is dark and full of terrors>>, or that's what The Admin once said.");
                        return 1;
                     }
                     else if (!strcmp(args[1], ".."))
                     {
                        return HAUNTED_HOUSE;
                     }
                  }
               }
               else if (argc == 1)
               {
                  if (!strcmp(args[0], "cd"))
                  {
                     cd(".");
                  }
                  else if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
                  {
                     return 0;
                  }
               }
               else
               {
                  return 1;
               }
               break;

            case FOREST_ENTRANCE:
               if (argc == 1)
               {
                  if (!strcmp(args[0], "oil"))
                  {
                     return 0;
                  }
                  else if (!strcmp(args[0], "quit") || !strcmp(args[0], "quit"))
                  {
                     return 1;
                  }
               }
               else if (argc == 2 && !strcmp(args[0], "grep"))
               {
                  args[0] = concat(cmd_dir, args[0]);
                  return execute(argc, args) ? -1 : 0;
               }
               else
               {
                  return 1;
               }
               break;

            case TREES_P:
               break;

            case FOREST:
               break;

            case EMERALD_CITY:
               break;

            case PRAIRIE:
               if (!strcmp(args[0], "exit"))
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

               break;

            case CASTLE:
               break;

            default:
               if (!strcmp(args[0], "exit"))
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

               break;
            }

            if (eof)
            {
               exit(0);
            }

            free(prompt_name);
         }
      }
   }

   return 0;
}
