#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int execute(int argc, char *argv[])
{
   pid_t child_pid = fork();
   int status;

   switch (child_pid)
   {
   case -1:
      return 1;

   case 0:
      // Child process
      execvp(argv[0], argv);
      break;

   default:
      // Parent process.
      wait(&status);
      return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
   }

   return 0;
}