/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_bintodec.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/08 18:36:44 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/08 19:23:02 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int		ft_bintodec(int bin)
{
	int	dec;
	int	p;

	dec = 0;
	p = 1;
	while (bin)
	{
		dec += (bin & 1) * p;
		bin = (bin - bin % 10) / 10;
		p *= 2;
	}
	return (dec);
}
