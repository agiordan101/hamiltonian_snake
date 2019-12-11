#ifndef SNAKE_H
# define SNAKE_H

# include "libft.h"
# include "stdlib.h"
# include "stdio.h"
# include "unistd.h"
# include "time.h"

#define WIDTH	6
#define HEIGHT	6

typedef struct	s_coord
{
	int			x;
	int			y;
}				t_coord;

typedef struct	s_node
{
	int			x;
	int			y;
	int			index;
	int			dir;
	struct s_node	*next;
}				t_node;

typedef struct	s_hamiltonian
{
	int			exist;
	t_node		cycle_tab[WIDTH][HEIGHT];	//Tab avec le numero dans le cycle
	//t_node		*cycle_lst;					//Cycle avec les coords de la case
	int			i;
	//int			first_x;
	//int			first_y;
}				t_hamiltonian;

typedef struct	s_game
{
	int			w;
	int			h;
	int			apple_x;
	int			apple_y;

	t_node		*snake;
	t_node		*head;
	int			map[WIDTH][HEIGHT];
	t_hamiltonian	cycle;
}				t_game;

void			init_hamiltonian_cycle(t_hamiltonian *cycle, t_node *snake, t_node *head);
void			draw(int map[WIDTH][HEIGHT], int clear);
void			draw_hamiltonian_cycle(t_node map[WIDTH][HEIGHT], int clear);

int				game_loop(t_game *game);
int				generate_apple(t_game *game);
void			add_node(t_node **lst, int x, int y);

int				algo(t_game *game, t_node *head, t_node *snake);

#endif
