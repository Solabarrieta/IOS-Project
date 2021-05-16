/**
 * @file help.c
 * @author Zdravko Todorov, Team 2.2
 * @brief Gives info about available commands
 * @version 1
 * @date 2021-04-21
 * 
 * @copyright Copyright (c) 2021
 */

#include "headers/libstring/libstring.h"

#include <stdlib.h>
#include <unistd.h>

void _help()
{
	char *jasmine = JASMINE;
	speak_character(jasmine, "Our my sweetest child, this is the spells you can use in this travel:");

	/* Prints all the available commands to the stdout */
	// HELP
	println(bold("help:"));
	println("\tYou've just used it to read this :)");
	// CAT
	println(bold("cat:"));
	println("\tYou can read notes with this command.");
	// CD
	println(bold("cd :"));
	println("\tTo move to another location in the map. Even teleport yourself and your companions!");
	// CP
	println(bold("cp :"));
	println("\tTo clone something into something new!");
	// GREP
	println(bold("grep :"));
	println("\tTo search something in a book or a note.");
	// LS
	println(bold("ls :"));
	println("\tTo look around you and get notice of the path you have to follow!");
	// MV
	println(bold("mv :"));
	println("\tTo move items or companions (Toto!) from one place to another, manually, of course.");
	// PWD
	println(bold("pwd :"));
	println("\tTo locate yourself in OS. Answer: <<Where Am I?>>");
	// STEE
	println(bold("stee :"));
	println("\tWhat's your name, darling?");
	// TOUCH
	println(bold("touch :"));
	println("\tTo craft a new item, following a recipe.");
}

int main(int argc, const char *argv[])
{
	char *ofelia = OFELIA;
	char *err_title = THE_SYSTEM;

	// If incorrect number of arguments
	if (argc != 1)
	{
		printerr("Oh, poor little player, you can't even ask for help correctly...", err_title);
		// Bad witch in action, oh yeah.
		speak_character(ofelia, "Look at the manual, you little useless piece of garbage!");

		return 1;
	}

	// If there is only ARGUMENT, that is, if only "help" is written.
	_help();
	return 0;
}