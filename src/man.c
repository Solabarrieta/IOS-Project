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
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char *argv[])
{
    if (argc == 3) {
        DIR *directory = opendir(argv[2]);

        if (directory == NULL) {
            printerr(THE_SYSTEM, "SH*T!!!!");
            return 1;
        }

        int fd, perc = 0;
        char *buffer, interior[17];
        struct dirent *d;
        struct stat file;

        do {
            d = readdir(directory);

            if (!strncmp(argv[1], d->d_name, strlen(argv[1]))) {
                stat(d->d_name, &file);
                fd = open(d->d_name, O_RDONLY);
                
                read(fd, &buffer, file.st_size);

                for (int i = 0; i < (int) ceil((float) file.st_size / 100); i++) {
                    perc += (int) ceil((float) write(1, &buffer, file.st_size)*100 / file.st_size);
                    sprintf(interior, "   Read: %d%%", perc);
                    println(interior);
                    wait_until_enter();
                }

                close(fd);
                break;
            }

        } while (d != NULL);

        return 0;

    } else {
        printerr(THE_SYSTEM, "Don't you dare disturb me while I'm reading, ape!");
        println("It costs me a lot...");

        return 1;
    }
}