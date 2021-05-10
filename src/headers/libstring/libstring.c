/**
 * @file string.c
 * @author David Cuenca Marcos
 * @brief Modified string library implementation.
 * @version 0.1
 * @date 2021-03-26
 * 
 * @copyright Copyright (c) 2021
 */

#include "libstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

char *concat(char *str1, char *str2)
{
    char *r_string = (char *)malloc((strlen(str1) + strlen(str2)) * sizeof(char));
    strcpy(r_string, str1);
    strcat(r_string, str2);
    return r_string;
}

void print(char *str)
{
    char *print_s;
    ssize_t buff;

    if (strncmp(str + strlen(str) - strlen(ANSI_RESET), ANSI_RESET, strlen(ANSI_RESET)) != 0)
    {
        print_s = concat(str, ANSI_RESET);
        buff = write(1, print_s, strlen(print_s));
    }
    else
    {
        buff = write(1, str, strlen(str));
    }
}

void println(char *str)
{
    ssize_t buff;
    print(str);
    buff = write(1, "\n", 1);
}

void printerr(char *err_title, char *str)
{
    char *result = concat(concat(concat(err_title, ": "), str), "\n");
    perror(result);
}

char *bold(char *str)
{
    if (strncmp(str + strlen(str) - strlen(ANSI_RESET), ANSI_RESET, strlen(ANSI_RESET)) != 0)
    {
        return concat(BOLD, str);
    }

    return concat(concat(BOLD, str), ANSI_RESET);
}

char *underline(char *str)
{
    if (strncmp(str + strlen(str) - strlen(ANSI_RESET), ANSI_RESET, strlen(ANSI_RESET)) != 0)
    {
        return concat(UNDERLINE, str);
    }

    return concat(concat(UNDERLINE, str), ANSI_RESET);
}

char *reverse(char *str)
{
    if (strncmp(str + strlen(str) - strlen(ANSI_RESET), ANSI_RESET, strlen(ANSI_RESET)) != 0)
    {
        return concat(REVERSE, str);
    }

    return concat(concat(REVERSE, str), ANSI_RESET);
}