#include "../include/snake.h"

void			add_node(t_node **lst, int x, int y)
{
	t_node		*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return ;
	node->x = x;
	node->y = y;
	node->index = *lst ? (*lst)->index + 1 : 1;
	node->dir = 3;
	node->next = *lst;
	*lst = node;
}

static int		init_map(t_game *game)
{
	t_node		*node;

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			game->map[i][j] = 0;
	//ft_bzero(game->map[i], sizeof(int) * HEIGHT);
	node = game->snake;
	while (node)
	{
		game->map[node->x][node->y] = 1;
		printf("Snake init : %d %d\n", node->x, node->y);
		node = node->next;
	}
	generate_apple(game);
	return (0);
}

static int		init_snake(t_game *game)
{
	game->snake = NULL;
	add_node(&(game->snake), WIDTH / 2, HEIGHT / 2);
	game->head = game->snake;
	add_node(&(game->snake), WIDTH / 2 - 1, HEIGHT / 2);
	add_node(&(game->snake), WIDTH / 2 - 2, HEIGHT / 2);
	//printf("Snake : %p %p %p\n", game->snake, game->snake->next, game->snake->next->next);
	return (0);
}

int	main()
{
	t_game	game;

	printf("Snake\n");
	//game.w = WIDTH;
	//game.h = HEIGHT;
	if (init_snake(&game) || init_map(&game))
		return (1);

	if (init_hamiltonian_cycle(&(game.cycle), game.snake, game.head))
		game_loop(&game);
	else
		printf("Can't find an hamiltonian_cycle\n");
	return (0);
}
