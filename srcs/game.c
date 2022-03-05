#include "../include/snake.h"

void		draw(int map[WIDTH][HEIGHT], int clear)
{
	if (clear)
		system("clear");
	printf("Map ->\n");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%d ", map[j][i]);
		}
		printf("\n");
	}
}

void		draw_color(int map[WIDTH][HEIGHT], int clear)
{
	if (clear)
		system("clear");
	printf("Map ->\n");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			if (map[j][i] == 0)
				printf("\033[37;2m#");
			else if (map[j][i] == 1)
				printf("\033[0;31m#");
			else
				printf("\033[0;32m#");
		}
		printf("\n");
	}
	printf("\033[0m");
}

void		draw_hamiltonian_cycle(t_node cycle[WIDTH][HEIGHT], int clear)
{
	if (clear)
		system("clear");
	//printf("%p\n", &(cycle[1][1]));
	printf("Hamiltonian cycle -> %d %d\n", WIDTH, HEIGHT);
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%d%c%c ", cycle[j][i].index,	cycle[j][i].index < 10 ? ' ' : '\0',\
													cycle[j][i].index < 100 ? ' ' : '\0');
		}
		printf("\n");
	}
}

int			generate_apple(t_game *game)
{
	srand(time(0));
	int		x = rand() % WIDTH;
	int		y = rand() % HEIGHT;
	int		n = 0;

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			n += game->map[i][j];
	if (n == WIDTH * HEIGHT)
		return (1);
	while (game->map[x][y])
	{
		x = rand() % WIDTH;
		y = rand() % HEIGHT;
	}
	game->map[x][y] = 2;
	game->apple_x = x;
	game->apple_y = y;
	//printf("New apple\n");
	return (0);
}

static int	move(t_game *game, t_node *head, t_node *snake)
{
	int		vx = (head->dir == 1 ? -1 : 0) + (head->dir == 2 ? 1 : 0);
	int		vy = (head->dir == 0 ? -1 : 0) + (head->dir == 3 ? 1 : 0);

	//printf("v %d %d -- %d\n", vx, vy, head->dir);
	if (head->x + vx == -1 || head->x + vx == WIDTH ||\
		head->y + vy == -1 || head->y + vy == HEIGHT)
		return (1);
	if (game->map[head->x + vx][head->y + vy] == 2)
		add_node(&(game->snake), game->snake->x, game->snake->y);
	else
		game->map[snake->x][snake->y] = 0;
	if (game->map[head->x + vx][head->y + vy] == 1)
		return (1);
	while (snake->next)
	{
		//printf("snake : %p\n", snake);
		snake->x = snake->next->x;
		snake->y = snake->next->y;
		snake = snake->next;
	}
	snake->x += vx;
	snake->y += vy;
	game->map[snake->x][snake->y] = 1;
	return (0);
}

//Bouger le cycle en meme temps que le snake ou sur la pomme

int			game_loop(t_game *game)
{
	int		win = 0;
	int		lose = 0;

	//exit(0);
	while (!win && !lose)
	{
		draw_color(game->map, 0);
		//draw_hamiltonian_cycle(game->cycle.cycle_tab, 0);
		for (int i = 0; i < 40000000; i++);
		// sleep(1);
		//printf("Algo ->\n");
		game->head->dir = algo(game, game->head, game->snake);
		//printf("Dir = %d\n", game->head->dir);
		//exit(0);

		lose = move(game, game->head, game->snake);
		if (game->head->x == game->apple_x && game->head->y == game->apple_y)
			win = generate_apple(game);
		//draw(game->map, 0);
	}
	draw(game->map, 0);
	draw_hamiltonian_cycle(game->cycle.cycle_tab, 0);
	if (lose)
		printf("LOSE - Score : %d%%\n", (int)(100 * (float)(game->snake->index) / (WIDTH * HEIGHT)));
	else
		printf("BRAVO ! Tu as gagne !\n");
	return (0);
}
