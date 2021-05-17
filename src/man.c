/**
 * @file man.c
 * @author David Cuenca Marcos
 * @brief Manual, for The Wizard of SO
 * @version 0.1
 * @date 2021-04-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "headers/libstring/libstring.h"
#include "headers/recognizer.h"

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printerr(THE_SYSTEM, "Don't you dare disturb me while I'm reading, ape!");
        println("It costs me a lot...");

        return 1;
    }

    int fd;
    char buffer;
    char *root = "doc/__manual__/";
    struct dirent *d;
    DIR *directory = opendir(root);

    if (directory == NULL)
    {
        printerr(THE_SYSTEM, "SH*T!!!!");
        return 1;
    }

    do
    {
        d = readdir(directory);

        if (!strcmp(concat(argv[1], "_specificationDoc.txt"), d->d_name))
        {
            chdir(root);
            fd = open(d->d_name, O_RDONLY);

            while (read(fd, &buffer, 1) == 1)
            {
                write(1, &buffer, 1);
            }

            close(fd);
            break;
        }

    } while (d != NULL);

    closedir(directory);

    return 0;
}