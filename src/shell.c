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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>

#define error(a) \
   {             \
      perror(a); \
      exit(1);   \
   };
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

/**
 * @brief Execute a process, given a command and its arguments.
 * 
 * @param argc Argument counter: the number of arguments that are passed (int, >= 1).
 * @param argv Argument vector: the arguments that are passed (char*, len(char*) >= 1)
 * @return int -1 if error creating the process, 1 if error while executing the process or 0 if ok.
 */
int execute(int argc, char *argv[])
{
   pid_t child_pid = fork();

   switch (child_pid)
   {
   case -1:
      return 1;
      break;

   case 0:
      // Child process
      execvp(argv[0], argv);
      break;

   default:
      // Parent process.
      wait(NULL);
      break;
   }

   return 0;
}

int main()
{
   char *Prompt = "GlindOS";
   int eof = 0;
   int argc;
   char *args[MAXARGS];

   char *path[10] = {"cat", "cp", "grep", "help", "ls", "man", "mv", "pwd", "touch", "stee"};
   int index;

   char *root_dir = getcwd((char *)NULL, 0);

   char *cmd_dir = concat(root_dir, "/bin/");
   char *game_dir = concat(root_dir, "/config/.gamedir/village/");
   char *current_dir;

   char *prompt_name;

   // Set game_dir
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
         if (!strcmp(args[0], "exit"))
         {
            if (!exit_game())
            {
               exit(127);
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
               if (strlen(args[1]) < strlen(game_dir) || strncmp(current_dir, args[1], strlen(current_dir))) {
                  perror("That is not a valid cd instruction, player.");
               } else {
                  cd(args[1]);
               }
            }
            else
            {
               perror("That is not a valid cd instruction, player.");
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
   }

   return 0;
}
