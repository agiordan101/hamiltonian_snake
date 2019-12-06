/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lltoa.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 20:39:44 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 18:53:32 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_lltoa(long long n)
{
	char	*str;
	int		i;

	i = ft_nbrlen(n) + (n < 0 ? 1 : 0);
	if (!(str = ft_strnew(i)))
		return (NULL);
	if (n < 0)
	{
		n *= -1;
		str[0] = '-';
	}
	while (n)
	{
		str[--i] = n % 10 + '0';
		n = (n - n % 10) / 10;
	}
	return (str);
}
