#include "snake.h"

static int		is_a_choice(t_node *snake, int x, int y)
{
	while (snake->next->next)
		snake = snake->next;
	if (x == -1 || x == WIDTH ||\
		y == -1 || y == HEIGHT ||\
		(x == snake->x && y == snake->y))
		return (0);
	return (1);
}

static int	dist_head_apple(t_game *game, t_hamiltonian *cycle, int x, int y)
{
	return (cycle->cycle_tab[game->apple_x][game->apple_y].index - cycle->cycle_tab[x][y].index +\
			(cycle->cycle_tab[x][y].index > cycle->cycle_tab[game->apple_x][game->apple_y].index ?\
			WIDTH * HEIGHT : 0));
}

static int	best_way(t_game *game, t_hamiltonian *cycle, t_node *head, t_node *snake, int search[4])
{
	int		best_choice;
	int		choice;
	int		tmp;

	if (search[0] &&\
		is_a_choice(snake, head->x, head->y - 1))
	{
		choice = 0;
		best_choice = dist_head_apple(game, cycle, head->x, head->y - 1);
		//*coord = (t_coord){head->x, head->y - 1};
	}
	if (search[1] &&\
		is_a_choice(snake, head->x - 1, head->y) &&\
		(tmp = dist_head_apple(game, cycle, head->x - 1, head->y)) < best_choice)
	{
		choice = 1;
		best_choice = tmp;
		//*coord = (t_coord){head->x - 1, head->y};
	}
	if (search[2] &&\
		is_a_choice(snake, head->x + 1, head->y) &&\
		(tmp = dist_head_apple(game, cycle, head->x + 1, head->y)) < best_choice)
	{
		choice = 2;
		best_choice = tmp;
		//*coord = (t_coord){head->x + 1, head->y};
	}
	if (search[3] &&\
		is_a_choice(snake, head->x, head->y + 1) &&\
		(tmp = dist_head_apple(game, cycle, head->x, head->y + 1)) < best_choice)
	{
		choice = 3;
		//*coord = (t_coord){head->x, head->y + 1};
	}
	return (choice);
}

static t_node		*find_member(t_game *game, t_hamiltonian *cycle, t_node *head, int *dist_member)
{
	t_node		*tmp;

	//link le dernier au premier
	tmp = cycle->cycle_tab[head->x][head->y].next;
	while (game->map[tmp->x][tmp->y] != 1)
		tmp = tmp->next;
	*dist_member =	tmp->index - cycle->cycle_tab[head->x][head->y].index +\
					tmp->index < cycle->cycle_tab[head->x][head->y].index ?\
					WIDTH * HEIGHT : 0;
	return (tmp);
}

static int		crash_snake(t_game *game, t_hamiltonian *cycle, t_node *head, t_node *snake)
{
	t_node	*member;
	int		dist_member;

	member = find_member(game, cycle, head, &dist_member);
	while (dist_member <= snake->index &&\
			member != snake)
	{
		member = find_member(game, cycle, head, &dist_member);
		if (dist_member < snake->index - member->index)
			return (1);
	}
	return (0);
}

int			algo(t_game *game, t_node *head, t_node *snake)
{
	t_hamiltonian	cycle;
	int				search[4];
	int				dir;

	ft_memset(search, 1, sizeof(int) * 4);
	search[4 - head->dir] = 0;
	dir = best_way(game, &cycle, head, snake, search);
	if (crash_snake(game, &cycle, head, snake))
		search[dir] = 0;
	else
		return (dir);
	dir = best_way(game, &cycle, head, snake, search);
	if (crash_snake(game, &cycle, head, snake))
		search[dir] = 0;
	else
		return (dir);
	return (best_way(game, &cycle, head, snake, search));
}
