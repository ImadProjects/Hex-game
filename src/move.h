/*! \file move.h                                                                                                                            
 * \brief structures for graph positionning                                                                                                                 
 *                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
 */
#ifndef _HEX_MOVE_H_
#define _HEX_MOVE_H_

#include <stdlib.h>

/**
 * @brief type enum for the colors of the graph
 */
enum color_t
{
  BLACK = 0,
  WHITE = 1,
  NO_COLOR = 2
};

/**
 * @brief data structure for the position in the graph
 */
struct move_t
{
  size_t m;       // An index between 0 and the number of vertices of - 1
  enum color_t c; // The color of the player
};

#endif // _HEX_MOVE_H_
