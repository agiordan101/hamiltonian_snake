/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_nbrlensign.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 20:44:16 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/30 14:33:39 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int				ft_nbrlensign(long long nbr)
{
	int			count;
	long long	p;

	count = 1;
	p = 10;
	if (nbr < 0)
	{
		nbr *= -1;
		count++;
	}
	while (nbr - p >= 0)
	{
		count++;
		p *= 10;
	}
	return (count);
}
