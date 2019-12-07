#include "snake.h"

static int				backtracking(t_hamiltonian *cycle, t_node *node, int x, int y, int dir)
{
	for (int i = 0; i < 100000000; i++);
	if (x == -1 || x == WIDTH ||\
		y == -1 || y == HEIGHT ||\
		cycle->cycle_tab[x][y].index)
		return (0);
	//printf("New coord %d %d\n", x, y);
	cycle->cycle_tab[x][y].index = cycle->i++;
	node->next = &(cycle->cycle_tab[x][y]);
	//draw(cycle->cycle, 0);
	if (cycle->i == WIDTH * HEIGHT + 1 &&\
			(cycle->cycle_tab[x][y - 1].index == 1 ||
			 cycle->cycle_tab[x - 1][y].index == 1 ||\
			 cycle->cycle_tab[x + 1][y].index == 1 ||\
			 cycle->cycle_tab[x][y + 1].index == 1))
	{
		printf("Find issue : %d %d\n", x, y);
		return (1);
	}
	if (dir == 1)
	{
		if (backtracking(cycle, node->next, x + 1, y, 3))
			return (1);
		if (backtracking(cycle, node->next, x - 1, y, 2))
			return (1);
		if (backtracking(cycle, node->next, x, y - 1, 1))
			return (1);
	}
	else if (dir == 2)
	{
		if (backtracking(cycle, node->next, x, y - 1, 1))
			return (1);
		if (backtracking(cycle, node->next, x, y + 1, 4))
			return (1);
		if (backtracking(cycle, node->next, x - 1, y, 2))
			return (1);
	}
	else if (dir == 3)
	{
		if (backtracking(cycle, node->next, x, y - 1, 1))
			return (1);
		if (backtracking(cycle, node->next, x, y + 1, 4))
			return (1);
		if (backtracking(cycle, node->next, x + 1, y, 3))
			return (1);
	}
	else
	{
		if (backtracking(cycle, node->next, x - 1, y, 2))
			return (1);
		if (backtracking(cycle, node->next, x + 1, y, 3))
			return (1);
		if (backtracking(cycle, node->next, x, y + 1, 4))
			return (1);
	}
	//printf("Back...\n");
	cycle->cycle_tab[x][y].index = 0;
	cycle->i--;
	node->next = NULL;
	return (0);
}

void			init_hamiltonian_cycle(t_hamiltonian *cycle, t_node *snake, t_node *head)
{
	t_node		*tmp;

	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
			cycle->cycle_tab[i][j].index = 0;
	//ft_bzero(cycle.cycle[i], sizeof(int) * HEIGHT);
	cycle->i = 1;
	cycle->cycle_lst = &(cycle->cycle_tab[snake->x][snake->y]);
	tmp = cycle->cycle_lst;
	while (snake->next)		//Oublie la tete pour quil se fasse a la 1ere iteratino du backtracking
	{
		cycle->cycle_tab[snake->x][snake->y].index = cycle->i++;
		tmp->next = &(cycle->cycle_tab[snake->x][snake->y]);
		//printf("Snake n%d -> %d %d\n", snake->index, snake->x, snake->y);
		snake = snake->next;
		tmp = tmp->next;
	}
	draw_hamiltonian_cycle(cycle->cycle_tab, 0); //Sans la tete
	cycle->cycle_lst = &(cycle->cycle_tab[head->x][head->y]);
	cycle->exist = backtracking(cycle, tmp, head->x, head->y, head->dir);
	draw_hamiltonian_cycle(cycle->cycle_tab, 0); //Sans la tete
	if (cycle->exist)
		printf("Hamiltonian cycle ->\n");
	else
		printf("Existe pas ...\n");	
}
