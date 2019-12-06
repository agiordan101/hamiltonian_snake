#ifndef SNAKE_H
# define SNAKE_H

# include "libft.h"
# include "stdlib.h"
# include "stdio.h"
# include "unistd.h"
# include "time.h"

#define WIDTH	10
#define HEIGHT	10

typedef struct	s_node
{
	int			x;
	int			y;
	int			index;
	int			dir;
	struct s_node	*next;
}				t_node;

typedef struct	s_game
{
	int			w;
	int			h;
	int			apple_x;
	int			apple_y;
	int			apple_eat;

	t_node		*snake;
	t_node		*head;
	int			map[WIDTH][HEIGHT];
}				t_game;

int				game_loop(t_game *game);
int				generate_apple(t_game *game);
void			add_node(t_node **lst, int x, int y);

int				algo(t_game *game, t_node *head, t_node *snake);

#endif
