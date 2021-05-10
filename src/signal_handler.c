#include "headers/characters/character.h"
#include "headers/libstring/libstring.h"
#include "headers/exit.h"

#include <signal.h>
#include <unistd.h>

void signint_parent(int sig) {
   speak_character(GLINDA, "Oh, are you abandonning this reality this way, aren't you?");
   speak_character(GLINDA, "Then, I'm afraid there must be something wrong with you, player.");
   _exit(127);
}

void signint_child(int sig) {
   speak_character(GLINDA, "Do you really want to exit the game, honey?");
   speak_character(GLINDA, "I think you don't, >:)");
}

void signstp(int sig) {
   printerr("Hey! STOP IT NOW!!", THE_SYSTEM);
}