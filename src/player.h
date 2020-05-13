/*! \file player.h                                                                                                                            
 * \brief player basic functions                                                                                                                 
 *                                                                                                                                                                                                                                                                         
 * \include path.c                                                                                                                                                                                                                                               
 */
#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <stdlib.h>
#include "move.h"
#include "pile.h"
#include "graph_aux.h"

/**
 * @brief Access to player informations to return its name
 * 
 * @return char const* 
 */
char const *get_player_name();

/**
 * @brief  Returns a single move for an opening
 * - a call to initialize_graph has been made
 * @return struct move_t 
 */
struct move_t propose_opening();

/**
 * @brief Acceptation of the opening
 * - a call to initialize_graph has been made
 * - the move is valid with regard to this graph
 * @param opening 
 * @return int a boolean telling if the player accepts the opening
 */
int accept_opening(const struct move_t opening);

/**
 * @brief graph initialization
 * - `graph` is a heap-allocated copy of the graph where the game is
 *   played, that must be freed in the end
 * - initialize_graph has never been called before
 * @param graph 
 */
void initialize_graph(struct graph_t *graph);

/**
 * @brief Player color initialization
 * - id is either BLACK or WHITE
 * - initialize_color has never been called before
 * @param id the color assigned to the player
 */
void initialize_color(enum color_t id);

/**
 * @brief Computes next move
 * 
 * @param previous_move 
 * @return struct move_t 
 */
struct move_t play(struct move_t previous_move);

/* Announces the end of the game to the player, and cleans up the
   memory he may have been using.
 * POSTCOND:
 * - every allocation done during the calls to initialize and play
 *   functions must have been freed
 */

/**
 * @brief cleans up the memory he may have been using
 * - every allocation done during the calls to initialize and play
 *   functions must have been freed
 */
void finalize();

//void get_player();

#endif // _PLAYER_H_
