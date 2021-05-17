/**
 * @file ls.c
 * @author Zdravko Todorov, Team 2.2
 * @brief Lists the directory and files.
 * @version 1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/libstring/libstring.h"

//Used for handling directory files
#include <dirent.h>
//For stat system call for file attributes
#include <sys/stat.h>
// Error control
#include <errno.h>
// Stdlib
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * @brief List directory.
 * 
 * @param dir The directory 'to list'.
 * @param op_a -a option selected.
 * @param op_l -l option selected.
 */
void _ls(const char *dir, int op_a, int op_l)
{
	char *err_title = THE_SYSTEM;

	// Pointer to stat struct
	struct stat sfile;

	// Here we will list the directory
	struct dirent *d;

	/* 1- Try to open the directory */
	DIR *dh = opendir(dir);

	//If the directory is not accessible
	if (dh == NULL)
	{
		// Throw error and exit
		if (errno = ENOENT)
		{
			// If the directory is not found
			printerr("Directory doesn't exist. Try again, ape.", err_title);
		}
		else
		{
			// If the directory is not readable
			printerr("Unable to read directory. Try again, ape.", err_title);
		}

		printerr("ERROR!", err_title);
		_exit(EXIT_FAILURE);
	}

	/* 2- While the next entry is not readable we will print directory files */
	while ((d = readdir(dh)) != NULL)
	{
		if (d->d_name[0] == '.')
		{
			if (op_a)
			{
				// Show the alternative path, if requested.
				println(concat(ANSI_COLOR_CYAN, d->d_name));
			}
			else
			{
				continue;
			}
		}
		else
		{
			if (!strcmp(d->d_name, "emerald_city"))
			{
				// If we are in Emerald City, print in Green color and bold (Emerald City)
				println(bold(concat(ANSI_COLOR_GREEN, d->d_name)));
			}
			else if (strstr(getcwd((char *)NULL, 0), "basement") != NULL && !strcmp(d->d_name, "message.txt"))
			{
				println(bold(concat(ANSI_COLOR_GREEN, d->d_name)));
			}
			else
			{
				// For the main path, simply print it on screen.
				println(concat(ANSI_COLOR_YELLOW, d->d_name));
			}
		}

		// If ls -l,
		if (op_l)
		{
			// Stat syscall, in order to get additional info about a file.
			stat(d->d_name, &sfile);

			// Accessing st_mode --> Permissions.
			println("User file permissions: ");
			println((sfile.st_mode & S_IRUSR) ? "You can see whats appening there!" : "Get out of there!!!");
			println((sfile.st_mode & S_IWUSR) ? "You can call the door!" : "You CANNOT call the door, very shy :)");
			println((sfile.st_mode & S_IXUSR) ? "You can enter!!!" : "You CANNOT enter");
		}
	}
}

int main(int argc, const char *argv[])
{
	char *err_title = THE_SYSTEM;

	if (argc == 1)
	{
		// If there is one argument, call ls alone, to ".".
		_ls(".", 0, 0);
	}
	else
	{
		// If there are two arguments, check if a valid option is passed:
		if (argv[1][0] == '-')
		{
			// Supported options: -a, -l
			int op_a = 0;
			int op_l = 0;

			// Read the option
			char *p = (char *)(argv[1] + 1);

			while (*p)
			{
				if (*p == 'a')
				{
					// If option is -a
					op_a = 1;
				}
				else if (*p == 'l')
				{
					// If option is -l
					op_l = 1;
				}
				else
				{
					printerr("Option not available. Try again, you useless ape.", err_title);
					return 1;
				}

				p++;
			}

			if (argc == 3)
			{
				_ls(argv[2], op_a, op_l);
			}
			else if (argc == 2)
			{
				_ls(".", op_a, op_l);
			}
			else
			{
				printerr("Option not available. Try again, you useless ape.", err_title);
				return 1;
			}
		}
		else if (argc == 2)
		{
			_ls(argv[1], 0, 0);
		}
		else
		{
			printerr("Option not available. Try again, you useless ape.", err_title);
			return 1;
		}
	}

	return 0;
}