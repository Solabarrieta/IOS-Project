/**
 * @brief Wait.
 * 
 */
extern void wait_until_enter();

/**
 * @brief Recognizer program.
 * 
 * @param filename The file to recognize.
 * @param player_name The name of the player to be shown on screen.
 * @return int 0 iff successful.
 */
extern int read_doc(char *filename, char *player_name);