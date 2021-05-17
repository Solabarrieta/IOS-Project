/* STATES of the GAME */
#define RESTART -1
#define MENU -2
#define GAME_OVER -3
#define VILLAGE 1
#define GROVE 2
#define HAUNTED_HOUSE 21
#define BASEMENT 211
#define BATHROOM 212
#define BEDROOM 213
#define KITCHEN 214
#define LIVINGROOM 215
#define FOREST_ENTRANCE 3
#define TREES_P 31
#define FOREST 4
#define EMERALD_CITY 5
#define PRAIRIE 6
#define CASTLE 7
/* STATES of the GAME */

/* CHAPTERS, SECTIONS TITLE */
#define VILLAGE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 1: <<THE VILLAGE>>"))
#define GROVE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 2: <<THE GROVE>>"))
#define HAUNTED_HOUSE_TIT concat(ANSI_COLOR_CYAN, bold("CHAPTER 2b: <<THE HAUNTED HOUSE>>"))
#define BASEMENT_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The basement")
#define BATHROOM_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The bathroom")
#define BEDROOM_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The bedroom")
#define KITCHEN_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The kitchen")
#define LIVINGROOM_TIT concat(ANSI_COLOR_CYAN, "<<THE HAUNTED HOUSE>>: The livingroom")
#define FOREST_ENTRANCE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 3: <<THE FOREST ENTRANCE>>"))
#define TREES_P_TIT concat(ANSI_COLOR_CYAN, bold("CHAPTER 3b: <<THE TREES>>"))
#define FOREST_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 4: <<THE FOREST>>"))
#define EMERALD_CITY_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 5: <<EMERALD CITY>>"))
#define PRAIRIE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 6: <<THE PRAIRIE>>"))
#define CASTLE_TIT concat(ANSI_COLOR_YELLOW, bold("CHAPTER 7: <<THE CASTLE>>"))
/* CHAPTERS, SECTIONS TITLE */

// The number of seconds to sleep on loading screens.
static float loading_screen = 0.2;

// The number of seconds to sleep before changing the character's line.
static float loading_line = 0.8 * 1000000;

// Medium saving rate...
static float saving_time = 0.11;
