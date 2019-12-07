#include "snake.h"

void		draw(int map[WIDTH][HEIGHT], int clear)
{
	if (clear)
		system("clear");
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			printf("%d ", map[j][i]);
			/*
			ft_putstr(ft_itoa(map[j][i]));
			//ft_putnbr(map[j][i]);
			ft_putchar(' ');
			if (map[j][i] < 10)
				ft_putchar(' ');
			*/
		}
		printf("\n");
		//ft_putchar('\n');
	}
	printf("\n");
	//ft_putchar('\n');
	//exit(0);
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
		add_node(&(game->snake), game->snake->x, game->snake->y);
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

//Bouger le cycle en meme temps que le snake ou sur la pomme

int			game_loop(t_game *game)
{
	int		win = 0;
	int		lose = 0;

	draw(game->map, 0);
	while (!win && !lose)
	{
		sleep(1);
		game->head->dir = algo(game->head, game->snake);
		printf("Dir = %d\n", game->head->dir);
		exit(0);

		lose = move(game, game->head, game->snake);
		if (game->head->x == game->apple_x && game->head->y == game->apple_y)
			win = generate_apple(game);
		//draw(game->map, 0);
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
