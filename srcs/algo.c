#include "../include/snake.h"

static int		is_a_choice(t_game *game, int x, int y)
{
	if (x == -1 || x == WIDTH ||\
		y == -1 || y == HEIGHT ||\
		(game->cycle.cycle_tab[x][y].index < game->cycle.cycle_tab[game->head->x][game->head->y].index &&\
		(game->cycle.cycle_tab[x][y].index != 1 ||\
		game->cycle.cycle_tab[game->head->x][game->head->y].index != WIDTH * HEIGHT)) ||\
		(game->map[x][y] == 1 &&\
		(x != game->snake->x || y != game->snake->y)))	//Le dernier membre est un choix possible !
		return (0);
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
	int		best_dist;
	int		choice;
	int		tmp;

	//printf("Lest find best way... %d %d %d %d\n", search[0], search[1], search[2], search[3]);
	best_dist = -1;
	choice = -1;
	if (search[0] &&\
		is_a_choice(game, head->x, head->y - 1))
	{
		choice = 0;
		best_dist = dist_in_cycle(cycle, head->x, head->y - 1, game->apple_x, game->apple_y);
		//printf("Choice 0 is a choice, dist : %d\n", best_dist);
	}
	if (search[1] &&\
		is_a_choice(game, head->x - 1, head->y) &&\
		((tmp = dist_in_cycle(cycle, head->x - 1, head->y, game->apple_x, game->apple_y)) < best_dist ||\
		best_dist == -1))
	{
		choice = 1;
		best_dist = tmp;
		//printf("Choice 1 is a choice, dist : %d\n", best_dist);
	}
	if (search[2] &&\
		is_a_choice(game, head->x + 1, head->y) &&\
		((tmp = dist_in_cycle(cycle, head->x + 1, head->y, game->apple_x, game->apple_y)) < best_dist ||\
		best_dist == -1))
	{
		choice = 2;
		best_dist = tmp;
		//printf("Choice 2 is a choice, dist : %d\n", best_dist);
	}
	if (search[3] &&\
		is_a_choice(game, head->x, head->y + 1) &&\
		((tmp = dist_in_cycle(cycle, head->x, head->y + 1, game->apple_x, game->apple_y)) < best_dist ||\
		best_dist == -1))
	{
		choice = 3;
		best_dist = tmp;
		//printf("Choice 3 is a choice, dist : %d\n", best_dist);
	}
	return (choice);
}

static t_node		*find_member(t_game *game, t_hamiltonian *cycle, t_node *new_head, int *n_find, int *dist_member)
{
	t_node		*member;
	t_node		*tmp;					//Node qui parcourt le cycle
	int			count_find = 0;

	//printf("Lets find new member (already %d)\n", *n_find);	
	tmp = cycle->cycle_tab[new_head->x][new_head->y].next;
	//printf("Debut : %d, %d %d\n", tmp->index, tmp->x, tmp->y);
	if (game->map[tmp->x][tmp->y] == 1)
		count_find++;
	while (count_find <= *n_find)			//count_find = n_find = 0 au debut
	{
		tmp = tmp->next;
		if (game->map[tmp->x][tmp->y] == 1)
			count_find++;
		//printf("Node x y %d %d - > %d\n", tmp->x, tmp->y, game->map[tmp->x][tmp->y]);
	}
	(*n_find)++;
	*dist_member = dist_in_cycle(cycle, new_head->x, new_head->y, tmp->x, tmp->y);
	//printf("Find new member %d %d index cycle %d\tdist %d\n", tmp->x, tmp->y, tmp->index, *dist_member);
	member = game->snake;	//Passe du t_node du cycle au t_node du snake
	while (member->x != tmp->x || member->y != tmp->y)
		member = member->next;
	return (member);
}

static int		apple_on_road(t_game *game, t_node *new_head, int i_snake)
{
	while (new_head->index != i_snake)
	{
		if (game->map[new_head->x][new_head->y] == 2)
			return (1);
		new_head = new_head->next;
	}
	return (0);
}

static int		crash_snake(t_game *game, t_hamiltonian *cycle, t_node *head, t_node *snake, int dir)
{
	t_node	*member;
	t_node	*new_head;
	int		n_find = 0;
	int		dist_member;

	//printf("Debut crash snake\n");
	if (dir == 0)											//Important pour que le find_member parte de la nouvelle case dans le cycle
		new_head = &(cycle->cycle_tab[head->x][head->y - 1]);
	else if (dir == 1)
		new_head = &(cycle->cycle_tab[head->x - 1][head->y]);
	else if (dir == 2)
		new_head = &(cycle->cycle_tab[head->x + 1][head->y]);
	else
		new_head = &(cycle->cycle_tab[head->x][head->y + 1]);

	member = find_member(game, cycle, new_head, &n_find, &dist_member);			//Trouve le membre du corps le plus proche
	while (dist_member < snake->index)						//Tant que la distance jusquau membre est plus petite que le snake
	{
		//printf("Dist member %d, snake len %d, member index %d\n", dist_member, snake->index, member->index);
		member = find_member(game, cycle, new_head, &n_find, &dist_member);		//Trouve la prochaine collision a chaque fois
		//+1 car jenleve 1 de dist en avancant la tete au debut de la ft()
		//Si la tete sera colle a la queue ca ne marche pas lorsqu'il y a une pomme sur la route
		if (dist_member + 1 <= snake->index - member->index ||\
			(dist_member == snake->index - member->index &&\
			apple_on_road(game, new_head, cycle->cycle_tab[member->x][member->y].index)))
		{	
			//printf("Dir %d crash ! Dist member %d, len snake %d, member index %d at %d %d, Apple on road ? %d\n", dir, dist_member, snake->index, member->index, member->x, member->y, apple_on_road(game, new_head, cycle->cycle_tab[member->x][member->y].index));
			return (1);
		}
	}
	//printf("Dir %d crash pas\n", dir);
	return (0);
}

int			algo(t_game *game, t_node *head, t_node *snake)
{
	int				search[4];
	int				dir;

	ft_memset(search, '1', sizeof(int) * 4);
	search[3 - head->dir] = 0;								//Banni la recherche dans le sens oppose a la dir
	//printf("Sens %d banni car sens inverse\n", 3 - head->dir);
	dir = best_way(game, &(game->cycle), head, search);		//Chope la dir la plus rapide vers la pomme
	if (crash_snake(game, &(game->cycle), head, snake, dir))				//Si je m'y crasherai banni la recherche dans cette dir
		search[dir] = 0;
	else
		return (dir);
	//printf("Sens %d banni\n", dir);
	dir = best_way(game, &(game->cycle), head, search);		//Reitere pour le 2eme et avant dernier meilleur choix
	if (crash_snake(game, &(game->cycle), head, snake, dir))
		search[dir] = 0;
	else
		return (dir);
	//printf("Sens %d banni\n", dir);
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
