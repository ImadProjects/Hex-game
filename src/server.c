#include <dlfcn.h>
#include "graph.h"
#include <getopt.h>
#include <time.h>
#include "player.h"


// Global seed for the random number generator
static int Length = 3;
static char Shape = 'c';

////////////////////////////////////////////////////////////////
// Function for parsing the options of the program
// Currently available options are :
// -s <seed> : sets the seed
void parse_opts(int argc, char* argv[]) {
  int opt;
  while ((opt = getopt(argc, argv, "m:t:")) != -1) {
    switch (opt) {
    case 'm':
      Length = atoi(optarg);
      break;
    case 't':
      Shape = atoi(optarg);
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-m Length] \n ",
              argv[0]);
      fprintf(stderr, "Usage: %s [-t Shape] \n ",
              argv[0]);
    }
  }
}

struct player{
  
  char const *name;
  struct graph_t *graph;
  enum color_t color;
  struct move_t (*propose_opening)();
  int (*accept_opening)(const struct move_t opening);
  void (*initialize_color)(enum color_t id);
  void (*initialize_graph)(struct graph_t* graph);
  struct move_t (*play)(struct move_t previous_move);
  void (*finalize)();
  
};


struct player * compute_next_player(struct player *p1, struct player *p2, struct col_move_t *last_move)
{
  
  if(last_move->c == p1->color)
    
    return p2;
  
  return p1;
  
}



int main(int argc,  char* argv[]){
  
	  printf("*********paramètres du jeu**********");
  parse_opts(argc, argv);
  printf("\nLength : %d\n", Length);
  printf("shape : %d\n", Shape);
//-------------------------------------------
        struct graph_t *graph = new__graph_t(Length, Shape); 
	void * player1 = dlopen("install/player1.so",RTLD_NOW);
	void * player2 = dlopen("install/player2.so",RTLD_NOW);

	struct player * p1 = dlsym(player1,"player1");

	p1->propose_opening = dlsym(player1,"propose_opening");
	p1->accept_opening = dlsym(player1,"accept_opening");
	p1->initialize_color = dlsym(player1,"initialize_color");
	p1->initialize_graph = dlsym(player1,"initialize_graph");
	p1->play = dlsym(player1,"play");
	p1->finalize = dlsym(player1,"finalize");
	p1->initialize_graph(graph);

	struct player * p2 = dlsym(player2,"player2");

	p2->propose_opening = dlsym(player2,"propose_opening");
	p2->accept_opening = dlsym(player2,"accept_opening");
	p2->initialize_color = dlsym(player2,"initialize_color");
	p2->initialize_graph = dlsym(player2,"initialize_graph");
	p2->play = dlsym(player2,"play");
	p2->finalize = dlsym(player2,"finalize");
	p2->initialize_graph(graph);
	
	struct move_t move = p1->propose_opening();
	//struct col_move_t * last_move;
	//last_move->m = move;
	//last_move->c = 0;

	p1->initialize_color(1 - p2->accept_opening(move));
	p2->initialize_color(p2->accept_opening(move));
	
	int select_player = 0;
	struct move_t t ={1};
	while (1){

	  srand(time(NULL));
	  
	  if (select_player==0)
		{
			select_player++;	
			move = p1->play(move);
			coloriate__graph_t(graph, 0, t);
			print_graph(graph, 'c');
			t.v++;
			//printf("%d\n",select_player);
			//printf("%d\n",t.v++); debug
		}
		else
		{
			select_player++;	
			move = p2->play(move);
			print_graph(graph, 'c');
			select_player %=2;
		}
			//printf("%d\n",select_player); debug

	 /* struct player * current_player = compute_next_player(player1,player2,last_move);
	  move = current_player->play(move);
	  last_move->m = move;
	  last_move->c = current_player->color;
	  coloriate__graph_t(graph, current_player->color, t);
	  t.v++;*/
	  print_graph(graph, 'c');
	  if (is_winning(graph,0,move,'c') || is_winning(graph,1,move,'c'))
			break;
	}
	
	if (is_winning(graph,0,move,'c')==0 )
	  
	  printf("The winner is the player 1\n");
	
	else
	  
	  printf("The winner is the player 2\n");

	free__graph_t(graph);
	dlclose(player1);
	dlclose(player2);
	return 0;
}
