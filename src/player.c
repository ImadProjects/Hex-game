 #include "player.h"

struct player{
  char const *name;
  struct move_t move;
  enum color_t color;
  struct move_t (*player_propose_opening)();
  int (*accept_opening)(const struct move_t opening);
  void (*initialize_color)(enum color_t id);
  void (*initialize_graph)(struct graph_t* graph);
  struct move_t (*play)(struct move_t previous_move);
  void (*finalize)();
};


 struct player player1={"heeeero"};


void initialize_player_functions(struct player* player)
{
  player->player_propose_opening = propose_opening;
  player->accept_opening = accept_opening;
  player->initialize_graph = initialize_graph;
  player->initialize_color = initialize_color;
  player->play = play;
}

struct player get_player()
{
  initialize_player_functions(&player1);
  player1.name = "player1";
  return player1;
}

char const* get_player_name()
{
  return player1.name;
}
/* Returns a single move for an opening
 * PRECOND:
 * - a call to initialize_graph has been made
 * RETURNS:
 * - a correct move inside the graph
 */
struct move_t propose_opening()
{
  return player1.move;
}

/* Acceptation of the opening
 * PARAM:
 * - opening : a move inside the graph
 * PRECOND:
 * - a call to initialize_graph has been made
 * - the move is valid with regard to this graph
 * RETURNS:
 * - a boolean telling if the player accepts the opening
 */
int accept_opening(const struct move_t opening)
{
  (void)opening;
  return 1;
}

/* Player graph initialization
 * PARAM:
 * - graph : the graph where the game is played
 * PRECOND:
 * - `graph` is a heap-allocated copy of the graph where the game is
 *   played, that must be freed in the end
 * - initialize_graph has never been called before
 */
void initialize_graph(struct graph_t* graph)
{
  // graph = new__graph_t(3, 'c');

}

/* Player color initialization
 * PARAM:
 * - id : the color assigned to the player
 * PRECOND:
 * - id is either BLACK or WHITE
 * - initialize_color has never been called before
 */
void initialize_color(enum color_t id)
{
  player1.color = id;
}

/* Computes next move
 * PARAM:
 * - previous_move: the move from the previous player
 * RETURNS:
 * - the next move for the player.
 */
struct move_t play(struct move_t previous_move)
{

  return previous_move;
}

/* Announces the end of the game to the player, and cleans up the
   memory he may have been using.
 * POSTCOND:
 * - every allocation done during the calls to initialize and play
 *   functions must have been freed
 */
void finalize()
{
 printf("The winner is %s\n",player1.name);
}
