#include "snake.h"

static void	draw(t_game *game)
{
	system("clear");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
			ft_putchar(game->map[j][i] + '0');
		ft_putchar('\n');
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
	int		vx = (head->dir == 2 ? -1 : 0) + (head->dir == 3 ? 1 : 0);
	int		vy = (head->dir == 1 ? -1 : 0) + (head->dir == 4 ? 1 : 0);

	//printf("v %d %d -- %d\n", vx, vy, head->dir);
	if (head->x + vx == -1 || head->x + vx == WIDTH ||\
		head->y + vy == -1 || head->y + vy == HEIGHT ||\
		game->map[head->x + vx][head->y + vy] == 1)
		return (1);
	if (game->map[head->x + vx][head->y + vy] == 2)
	{
		add_node(&(game->snake), game->snake->x, game->snake->y);
		snake = snake->next;
	}
	else
		game->map[snake->x][snake->y] = 0;
	while (snake->next)
	{
		snake->x = snake->next->x;
		snake->y = snake->next->y;
		snake = snake->next;
	}
	snake->x += vx;
	snake->y += vy;
	game->map[snake->x][snake->y] = 1;
	return (0);
}

int			game_loop(t_game *game)
{
	int		win = 0;
	int		lose = 0;

	draw(game);
	while (!win && !lose)
	{
		sleep(1);
		game->head->dir = algo(game, game->head, game->snake);
		lose = move(game, game->head, game->snake);
		if (game->head->x == game->apple_x && game->head->y == game->apple_y)
			win = generate_apple(game);
		draw(game);
	}
	if (lose)
	{
		ft_putstr("LOSE - Score : ");
		ft_putnbr(game->snake->index + 1);
		ft_putchar('\n');
	}
	else
		ft_putendl("BRAVO ! Tu as gagne !");
	return (0);
}
