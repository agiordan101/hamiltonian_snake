#include "snake.h"

void			add_node(t_node **lst, int x, int y)
{
	t_node		*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return ;
	node->x = x;
	node->y = y;
	node->index = *lst ? (*lst)->index + 1 : 0;
	node->dir = 0;
	node->next = *lst;
	*lst = node;
//	t_node		*tmp;

//	tmp = *lst;
//	if (!tmp)
//	{
//		node->index = 0;
//		*lst = node;
//	}
//	else
//	{
//		while (tmp->next)
//			tmp = tmp->next;
//		node->index = tmp->index + 1;
//		tmp->next = node;
//	}
//	node->next = NULL;
}

static int		init_map(t_game *game)
{
	t_node		*node;

	ft_bzero(game->map, sizeof(int) * HEIGHT * WIDTH);
	node = game->snake;
	while (node)
	{
		game->map[node->x][node->y] = 1;
		node = node->next;
	}
	//generate_apple(game);
	return (0);
}

static int		init_snake(t_game *game)
{
	game->snake = NULL;
	add_node(&(game->snake), WIDTH / 2, HEIGHT / 2);
	game->head = game->snake;
	add_node(&(game->snake), WIDTH / 2 - 1, HEIGHT / 2);
	add_node(&(game->snake), WIDTH / 2 - 2, HEIGHT / 2);	
	return (0);
}

int	main()
{
	t_game	game;

	printf("Snake\n");
	game.w = WIDTH;
	game.h = HEIGHT;
	if (init_snake(&game) || init_map(&game))
		return (1);

	game.apple_x = 8;
	game.apple_y = 5;
	game.map[game.apple_x][game.apple_y] = 2;

	game_loop(&game);
	return (0);
}
