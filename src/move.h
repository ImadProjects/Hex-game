#ifndef _HEX_MOVE_H_
#define _HEX_MOVE_H_

#include <stdlib.h>

/* Players */
enum color_t { BLACK=0, WHITE=1 };

/* Positions */
struct move_t { size_t v; }; // An index between 0 and the number of vertices of - 1

struct col_move_t {
  struct move_t m;
  enum color_t c;
};

#endif // _HEX_MOVE_H_