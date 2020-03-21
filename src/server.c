
#include <dlfcn.h>
#include "graph.h"
#include "player.h"



struct player{
  char const *name;
  struct move_t move;
  enum color_t color;
  struct move_t (*propose_opening)();
  int (*accept_opening)(const struct move_t opening);
  void (*initialize_color)(enum color_t id);
  void (*initialize_graph)(struct graph_t* graph);
  struct move_t (*play)(struct move_t previous_move);
  void (*finalize)();
};

/*
struct player * compute_next_player(struct player *p1, struct player *p2)
{
	if(! p1->accept_opening())

}
	*/


int main()
{
	struct graph_t *graph = new__graph_t(3, 'c');
	void * player1 = dlopen("install/player1.so",RTLD_NOW);
	void * player2 = dlopen("install/player2.so",RTLD_NOW);

	struct player * p1 = dlsym(player1,"player1");

	p1->propose_opening = dlsym(player1,"propose_opening");
	p1->accept_opening = dlsym(player1,"accept_opening");
	p1->initialize_color = dlsym(player1,"initialize_color");
	p1->initialize_graph = dlsym(player1,"initialize_graph");
	p1->play = dlsym(player1,"play");
	p1->finalize = dlsym(player1,"finalize");

	struct player * p2 = dlsym(player2,"player1");

	p2->propose_opening = dlsym(player2,"propose_opening");
	p2->accept_opening = dlsym(player2,"accept_opening");
	p2->initialize_color = dlsym(player2,"initialize_color");
	p2->initialize_graph = dlsym(player2,"initialize_graph");
	p2->play = dlsym(player2,"play");
	p2->finalize = dlsym(player2,"finalize");


	p1->initialize_graph(graph);
	p1->initialize_graph(graph);
	struct move_t move = p1->propose_opening();

	if (p2->accept_opening(move))
	{
		p1->initialize_color(0);
		p2->initialize_color(1);
	}
	else
	{
		p1->initialize_color(1);
		p2->initialize_color(0);
	}
	int b = 1;
	int select_player = 0;
	struct move_t t ={1};
	while (b)
	{
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
			//printf("%d\n",select_player); debug
		}
		//TODO: write compute_next_player() <----------------------------------------------

		if (is_winning(graph,0,move,'c') || is_winning(graph,1,move,'c'))
			break;
	}
	if (is_winning(graph,0,move,'c')==0 )
		p1->finalize();
	else
		p2->finalize();
	free__graph_t(graph);
	dlclose(player1);
	dlclose(player2);
	return 0;
}
