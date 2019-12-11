#include "snake.h"

//static int		last_chance(t_game *game, t_hamiltonian *cycle, t_node *head, t_node *snake)
//{
//}

static int		is_a_choice(t_game *game, int x, int y)
{
	if (x == -1 || x == WIDTH ||\
		y == -1 || y == HEIGHT ||\
		(game->map[x][y] == 1 &&\
		 &(game->cycle.cycle_tab[x][y]) != game->snake))	//Le dernier membre est a 1 mais est un choix possible !
		return (0);
	/*
	while (snake->next->next)								//avance jusqua la nuque (avant head)
		snake = snake->next;
	if (x == snake->x && y == snake->y)
		return (0);
	*/
	return (1);
}

static int	dist_in_cycle(t_hamiltonian *cycle, int x, int y, int x2, int y2)
{
	//printf("dist btw : %d %d\n", cycle->cycle_tab[x][y].index, cycle->cycle_tab[x2][y2].index);
	return (cycle->cycle_tab[x2][y2].index - cycle->cycle_tab[x][y].index +\
			(cycle->cycle_tab[x][y].index > cycle->cycle_tab[x2][y2].index ?\
			WIDTH * HEIGHT : 0));
}

static int	best_way(t_game *game, t_hamiltonian *cycle, t_node *head, int search[4])
{
	int		best_choice;
	int		choice;
	int		tmp;

	//printf("Lest find best way...\n");
	best_choice = -1;
	if (search[0] &&\
		is_a_choice(game, head->x, head->y - 1))
	{
		//printf("Dist %d %d");
		choice = 1;
		best_choice = dist_in_cycle(cycle, head->x, head->y - 1, game->apple_x, game->apple_y);
		//*coord = (t_coord){head->x, head->y - 1};
	}
	if (search[1] &&\
		is_a_choice(game, head->x - 1, head->y) &&\
		((tmp = dist_in_cycle(cycle, head->x - 1, head->y, game->apple_x, game->apple_y)) < best_choice ||\
		best_choice == -1))
	{
		choice = 2;
		best_choice = tmp;
		//*coord = (t_coord){head->x - 1, head->y};
	}
	if (search[2] &&\
		is_a_choice(game, head->x + 1, head->y) &&\
		((tmp = dist_in_cycle(cycle, head->x + 1, head->y, game->apple_x, game->apple_y)) < best_choice ||\
		 best_choice == -1))
	{
		choice = 3;
		best_choice = tmp;
		//*coord = (t_coord){head->x + 1, head->y};
	}
	if (search[3] &&\
		is_a_choice(game, head->x, head->y + 1) &&\
		(dist_in_cycle(cycle, head->x, head->y + 1, game->apple_x, game->apple_y) < best_choice ||\
		best_choice == -1))
	{
		choice = 4;
		//*coord = (t_coord){head->x, head->y + 1};
	}
	//printf("Current best way is %d\n", choice);
	return (choice);
}

static t_node		*find_member(t_game *game, t_hamiltonian *cycle, t_node *new_head, int *n_member, int *dist_member)
{
	t_node		*member;
	t_node		*tmp;					//Node qui parcourt le cycle
	int			count = 0;

	//printf("Lets find new member (already %d)\n", *n_member);	
	tmp = cycle->cycle_tab[new_head->x][new_head->y].next;
	//printf("Debut : %d, %d %d\n", tmp->index, tmp->x, tmp->y);
	if (game->map[tmp->x][tmp->y] == 1)
		count++;
	while (count <= *n_member)
	{
		tmp = tmp->next;
		if (game->map[tmp->x][tmp->y] == 1)
			count++;
		//printf("Node x y %d %d - > %d\n", tmp->x, tmp->y, game->map[tmp->x][tmp->y]);
	}
	(*n_member)++;
	*dist_member = dist_in_cycle(cycle, new_head->x, new_head->y, tmp->x, tmp->y);
	printf("Find new member %d %d index cycle %d\tdist %d\n", tmp->x, tmp->y, tmp->index, *dist_member);
	member = game->snake;
	while (member->x != tmp->x || member->y != tmp->y)
		member = member->next;
	return (member);
}

static int		crash_snake(t_game *game, t_hamiltonian *cycle, t_node *head, t_node *snake, int dir)
{
	t_node	*member;
	t_node	*new_head;
	int		n_member = 0;
	int		dist_member;

	//printf("Debut crash snake\n");
	if (dir == 1)
		new_head = &(cycle->cycle_tab[head->x][head->y - 1]);
	else if (dir == 2)
		new_head = &(cycle->cycle_tab[head->x - 1][head->y]);
	else if (dir == 3)
		new_head = &(cycle->cycle_tab[head->x + 1][head->y]);
	else
		new_head = &(cycle->cycle_tab[head->x][head->y + 1]);

	member = find_member(game, cycle, new_head, &n_member, &dist_member);			//Trouve le membre du corps le plus proche
	while (dist_member < snake->index)						//Tant que la distance jusquau membre est plus petite que le snake
	{
		printf("Dist member %d, snake len %d, member index %d\n", dist_member, snake->index, member->index);
		member = find_member(game, cycle, new_head, &n_member, &dist_member);		//Trouve la prochaine collision a chaque fois
		if (dist_member <= snake->index - member->index + 1)			//Si la dist pour y aller est plus petite que le nbr de membre jusqua la queue
		{
			printf("Crash ! dist %d, len snake %d, member index %d\n", dist_member, snake->index, member->index);
			return (1);										//de tour pour que la queue s'en aille alors collision
		}
	}
	printf("Crash pas dir %d, dist %d,  snake len %d, member index %d\n", dir, dist_member, snake->index, member->index);
	return (0);
}

int			algo(t_game *game, t_node *head, t_node *snake)
{
	int				search[4];
	int				dir;

	draw_hamiltonian_cycle(game->cycle.cycle_tab, 0);
	ft_memset(search, 1, sizeof(int) * 4);
	search[4 - head->dir] = 0;								//Banni la recherche dans le sens oppose a la dir
	dir = best_way(game, &(game->cycle), head, search);		//Chope la dir la plus rapide vers la pomme
	if (crash_snake(game, &(game->cycle), head, snake, dir))				//Si je m'y crasherai banni la recherche dans cette dir
		search[dir - 1] = 0;
	else
		return (dir);
	//printf("2eme solution\n");
	dir = best_way(game, &(game->cycle), head, search);		//Reitere pour le 2eme et avant dernier meilleur choix
	if (crash_snake(game, &(game->cycle), head, snake, dir))
		search[dir - 1] = 0;
	else
		return (dir);
	//printf("3eme solution\n");
	dir = best_way(game, &(game->cycle), head, search);	//Si les 2 meilleurs ne marche pas prend le plus long
	if (crash_snake(game, &(game->cycle), head, snake, dir))
	{
		//Faire des bails de nouveaux hamiltonian path
		//Le suivant si il est vide
		//Sinon un autre aleat
		//return (last_chance(game, &(game->cycle), head, snake);
		printf("I can't win, I give up\n");
		exit(0);
		return (dir);
	}
	else
		return (dir);
}
//Attention si il ny as plus de place je sg fault ???
