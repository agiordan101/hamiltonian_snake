/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lltoa_base.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 20:39:44 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 20:52:10 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	convert(int n)
{
	char	*bases;

	bases = "0123456789abcdefghijklmnopqrstuvwxyz";
	return (bases[n]);
}

char		*ft_lltoa_base(long long n, int base)
{
	char	*str;
	char	*tmp;
	int		count;

	count = 0;
	str = NULL;
	if (n < 0)
	{
		if (!(str = ft_strnew(++count)))
			return (NULL);
		n *= -1;
		str[0] = '-';
	}
	while (n)
	{
		tmp = str;
		if (!(str = ft_strnew(++count)))
			return (NULL);
		ft_strcpy(str, tmp);
		ft_strdel(&tmp);
		str[count - 1] = convert(n % base);
		n = (n - n % base) / base;
	}
	ft_strrev(str + (str[0] == '-' ? 1 : 0));
	return (str);
}
