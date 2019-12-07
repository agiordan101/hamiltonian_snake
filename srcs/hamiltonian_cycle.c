#include "snake.h"

static int				backtracking(t_hamiltonian *cycle, int x, int y, int dir)
{
	for (int i = 0; i < 100000000; i++);
	if (x == -1 || x == WIDTH ||\
			y == -1 || y == HEIGHT ||\
			(cycle->cycle[x][y]))
		return (0);
	//printf("New coord %d %d\n", x, y);
	cycle->cycle[x][y] = cycle->i++;
	//draw(cycle->cycle, 0);
	if (cycle->i == WIDTH * HEIGHT + 1 &&\
			(cycle->cycle[x][y - 1] == 1 ||
			 cycle->cycle[x - 1][y] == 1 ||\
			 cycle->cycle[x + 1][y] == 1 ||\
			 cycle->cycle[x][y + 1] == 1))
	{
		printf("Find issue : %d %d\n", x, y);
		return (1);
	}
	if (dir == 1)
	{
		if (backtracking(cycle, x + 1, y, 3))
			return (1);
		if (backtracking(cycle, x - 1, y, 2))
			return (1);
		if (backtracking(cycle, x, y - 1, 1))
			return (1);
	}
	else if (dir == 2)
	{
		if (backtracking(cycle, x, y - 1, 1))
			return (1);
		if (backtracking(cycle, x, y + 1, 4))
			return (1);
		if (backtracking(cycle, x - 1, y, 2))
			return (1);
	}
	else if (dir == 3)
	{
		if (backtracking(cycle, x, y - 1, 1))
			return (1);
		if (backtracking(cycle, x, y + 1, 4))
			return (1);
		if (backtracking(cycle, x + 1, y, 3))
			return (1);
	}
	else
	{
		if (backtracking(cycle, x - 1, y, 2))
			return (1);
		if (backtracking(cycle, x + 1, y, 3))
			return (1);
		if (backtracking(cycle, x, y + 1, 4))
			return (1);
	}
	//printf("Back...\n");
	cycle->cycle[x][y] = 0;
	cycle->i--;
	return (0);
}

static t_hamiltonian	hamiltonian_cycle(t_node *snake, t_node *head)
{
	t_hamiltonian		cycle;

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			cycle.cycle[i][j] = 0;
	//ft_bzero(cycle.cycle[i], sizeof(int) * HEIGHT);
	cycle.i = 1;
	while (snake->next)		//Oublie le dernier pour quil se fasse a la 1ere iteratino du backtracking
	{
		cycle.cycle[snake->x][snake->y] = cycle.i++;
		printf("Snake n%d -> %d %d\n", snake->index, snake->x, snake->y);
		snake = snake->next;
	}
	//draw(cycle.cycle, 0); //Sans la tete
	cycle.exist = backtracking(&cycle, head->x, head->y, head->dir);
	return (cycle);
}

void	init_hamiltonian_cycle(t_game *game)
{
	game->cycle = hamiltonian_cycle(game->snake, game->head);
	if (game->cycle.exist)
		printf("Hamiltonian cycle ->\n");
	else
	{
		printf("Existe pas ...\n");	
		return (-1);
	}
}
