#include "../include/snake.h"

static int				backtracking(t_hamiltonian *cycle, t_node *node, int x, int y, int dir)
{
	//for (int i = 0; i < 100000000; i++);
	//Si la case est out of bornes OU deja utilise on stop
	if (x == -1 || x == WIDTH ||\
		y == -1 || y == HEIGHT ||\
		cycle->cycle_tab[x][y].index)
		return (0);
	//printf("New coord %d %d\n", x, y);
	cycle->cycle_tab[x][y].index = cycle->i++;		//Incremente l'index dans le cycle
	node->next = &(cycle->cycle_tab[x][y]);			//Construit le cycle
	//draw(cycle->cycle, 0);
	if (cycle->i == WIDTH * HEIGHT + 1 &&\
			((y - 1 >= 0 && cycle->cycle_tab[x][y - 1].index == 1) ||
			 (x - 1 >= 0 && cycle->cycle_tab[x - 1][y].index == 1) ||\
			 (x + 1 < WIDTH && cycle->cycle_tab[x + 1][y].index == 1) ||\
			 (y + 1 < HEIGHT && cycle->cycle_tab[x][y + 1].index == 1)))
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

int				init_hamiltonian_cycle(t_hamiltonian *cycle, t_node *snake, t_node *head)
{
	t_node		*tmp;

	printf("WH %d %d\n", WIDTH, HEIGHT);
	for (int i = 0; i < WIDTH; i++)
		for (int j = 0; j < HEIGHT; j++)
		{
			cycle->cycle_tab[i][j].index = 0;
			cycle->cycle_tab[i][j].x = i;
			cycle->cycle_tab[i][j].y = j;
			printf("Init case %d %d\n", i, j);
		}
	cycle->i = 1;
	//cycle->cycle_lst = &(cycle->cycle_tab[snake->x][snake->y]); //Commence le cycle part la queue
	//tmp = cycle->cycle_lst;
	//tmp = &(cycle->cycle_tab[snake->x][snake->y]);
	tmp = snake;
	while (tmp->next)		//Oublie la tete pour quil se fasse a la 1ere iteratino du backtracking
	{
		cycle->cycle_tab[tmp->x][tmp->y].index = cycle->i++; //Copie le corps dans le tab cycle avec son numero
		cycle->cycle_tab[tmp->x][tmp->y].next = &(cycle->cycle_tab[tmp->next->x][tmp->next->y]);//Copie le corps dans la lst cycle
		//printf("Snake n%d -> %d %d\n", snake->index, snake->x, snake->y);
		tmp = tmp->next;
	}

	//draw_hamiltonian_cycle(cycle->cycle_tab, 0); //Draw sans la tete
	//cycle->cycle_lst = &(cycle->cycle_tab[head->x][head->y]);		//Reset le pointeur sur le cycle apres la voir construit
	cycle->exist = backtracking(cycle, &(cycle->cycle_tab[head->x][head->y]), head->x, head->y, head->dir);
	
	tmp = &(cycle->cycle_tab[snake->x][snake->y]);
	while (tmp->next)										//Va jusqu'au dernier
	{
		printf("Index : %d\n", tmp->index);
		tmp = tmp->next;
	}
	tmp->next = &(cycle->cycle_tab[snake->x][snake->y]);	//Pour le link au premier

	while (snake)
	{
		printf("snake : %p\n", snake);
		snake = snake->next;
	}

	if (cycle->exist)
		draw_hamiltonian_cycle(cycle->cycle_tab, 0);
	else
		printf("Existe pas ...\n");	
	return (cycle->exist ? 1 : 0);
}
