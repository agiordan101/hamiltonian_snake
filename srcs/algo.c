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

static int		is_a_choice(t_hamiltonian *cycle, t_head *head, t_node *snake, int x, int y)
{
	while (snake->next->next)
		snake = snake->next;
	if (x == -1 || x == WIDTH ||\
		y == -1 || y == HEIGHT ||\
		(x == snake->x && y == snake->y)
		return (0);
	return (1);
}

static int	dist_head_apple(t_game *game, t_hamiltonian *cycle, int x, int y)
{
	return (cycle->cycle[game->apple_x][game->apple_y] - cycle->cycle[x][y] +\
			(cycle->cycle[x][y] > cycle->cycle[game->apple_x][game->apple_y]) ?\
			WIDTH * HEIGHT : 0);
}

static int	best_way(t_coord *coord, t_game *game, t_hamiltonian *cycle, int search[4])
{
	int		best_choice;
	int		choice;
	int		tmp;

	if (search[0] &&\
		is_a_choice(&cycle, head, snake, head->x, head->y - 1))
	{
		choice = 0;
		best_choice = dist_head_apple(game, &cycle, head->x, head->y - 1);
		*coord = (t_coord){head->x, head->y - 1};
	}
	if (search[1] &&\
		is_a_choice(&cycle, head, snake, head->x - 1, head->y) &&\
		(tmp = dist_head_apple(game, &cycle, head->x - 1, head->y)) < best_choice)
	{
		choice = 1;
		best_choice = tmp;
		*coord = (t_coord){head->x - 1, head->y};
	}
	if (search[2] &&\
		is_a_choice(&cycle, head, snake, head->x + 1, head->y) &&\
		(tmp = dist_head_apple(game, &cycle, head->x + 1, head->y)) < best_choice)
	{
		choice = 2;
		best_choice = tmp;
		*coord = (t_coord){head->x + 1, head->y};
	}
	if (search[3] &&\
		is_a_choice(&cycle, head, snake, head->x, head->y + 1) &&\
		(tmp = dist_head_apple(game, &cycle, head->x, head->y + 1)) < best_choice)
	{
		choice = 3;
		*coord = (t_coord){head->x, head->y + 1};
	}
	return (choice);
}

static node		*find_member(t_game *game, t_hamiltonian *cycle, t_node *head, t_node *snake, int *dist_member)
{
	t_node		*tmp;

	//link le dernier au premier
	tmp = cycle->cycle_tab[head->x][head->y]->next;
	while (game->map[tmp->x][tmp->y] != 1)
		tmp = tmp->next;
	*dist_member =	tmp->index - cycle->cycle_tab[head->x][head->y]->index +\
					tmp->index < cycle->cycle_tab[head->x][head->y]->index ?\
					WIDTH * HEIGHT : 0;
	return (tmp);
}

static int		crash_snake(t_game *game, t_coord coord, t_hamiltonian *cycle, t_node *head, t_node *snake)
{
	t_node	*member;
	int		dist_member;
	t_coord	collision;

	member = find_member(game, cycle, head, snake, &dist_member);
	while (dist_member <= snake->index &&\
			member != snake)
	{
		member = find_member(game, cycle, snake, &dist_member);
		if (dist_member < snake->index - member->index)
			return (1);
	}
	return (0);
}

int			algo(t_game *game, t_node *head, t_node *snake)
{
	t_hamiltonian	cycle;
	t_coord			coord;
	int				search[4];
	int				dir;

	cycle = hamiltonian_cycle(snake, head);
	if (cycle.exist)
		printf("Hamiltonian cycle ->\n");
	else
	{
		printf("Existe pas ...\n");	
		return (-1);
	}



	search = {1, 1, 1, 1};
	search[4 - head->dir] = 0;
	dir = best_way(&coord, game, &cycle, search);
	if (crash_snake(game, &coord, &cycle, head, snake))
		search[dir] = 0;
	else
		return (dir);
	dir = best_way(&coord, game, &cycle, search);
	if (crash_snake(game, &coord, &cycle, head, snake))
		search[dir] = 0;
	else
		return (dir);
	return (best_way(&coord, game, &cycle, search));
}
