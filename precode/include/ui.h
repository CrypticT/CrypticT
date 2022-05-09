/**
 * @file ui.h
 * @author Morten Grønnesby (morten.gronnesby@uit.no)
 * @brief Defines the UI.
 * @version 0.1
 * 
 * Defines the UI for the exam.
 */
#ifndef UI_H
#define UI_H

#include "index.h"

#define MIN_SUGGESTION_LEN 3

/**
 * @brief Initializes the UI system.
 * 
 * This initializes a terminal "full-screen" interface.
 */
void ui_init();


/**
 * @brief Deinitializes the UI system.
 *
 * This will clear any terminal "full-screen" output.
 */
void ui_deinit();

/**
 * @brief Main UI.
 * 
 * @param idx The document index.
 * @return char* The search string.
 * 
 * 
 */
char *ui_main(index_t *idx);


/**
 * @brief Displays results in the UI.
 * 
 * @param res Pointer to the result of the last search.
 * 
 * 
 */
void ui_result(search_result_t *res);

#endif