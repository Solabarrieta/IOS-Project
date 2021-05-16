/**
 * @file grep.c
 * @author Zdravko Todorov, Team 2.2
 * @brief Prints the line containing the word and the occurance number
 * @version 1
 * @date 2021-03-30
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/libstring/libstring.h"

// Defines flags for open and related library functions
#include <fcntl.h>
// For write system call
#include <unistd.h>
// Stdlib library
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    char *err_title = THE_SYSTEM;

    int des, fhandle, i, j, k, arg_ind = 2, occurances = 0;
    int linecount;
    int lineflag;
    char buf, line[160];

    // To check the syntax, the number of args.
    if (argc < 4)
    {
        printerr("Pattern recognition error! The CORRECT SYNTAX is : grep \"pattern\" \"filename\". Revise your notes, please.", err_title);
        _exit(EXIT_FAILURE);
    }

    lineflag = 0;

    // Open the file specified by the command
    des = open(argv[3], O_RDONLY);
    linecount = 0;

    // Read upto the end of file and copy to the array line[i].
    do
    {
        //Read a line
        i = 0;

        do
        {
            fhandle = read(des, &buf, 1);
            line[i++] = buf;
        } while ((fhandle != 0) && (buf != '\n'));

        line[i] = '\0';
        linecount++;

        //Check character matching
        i = 0;

        while (line[i] != '\0')
        {
            if (line[i] == argv[2][0])
            {

                // Check all characters in a line
                k = 1;
                i++;

                while ((k < strlen(argv[2])) && (line[i] == argv[2][k]))
                {
                    i++;
                    k++;
                }

                if (k == strlen(argv[2]))
                {
                    // Print out the line
                    println(line);
                    // Count occurances of that string
                    occurances++;
                }
            }

            i++;
        }

    } while (fhandle != 0);

    close(des);
    arg_ind++;

    // Show results.
    char *res = (char *)malloc(strlen("Number of occurances: %d") + sizeof(occurances));
    sprintf(res, "Number of occurances: %d", occurances);
    println(bold(res));

    return 1;
}