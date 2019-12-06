/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strrev.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/09 19:31:07 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/09 19:39:07 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int	len;
	int	i;

	len = ft_strlen(str);
	i = -1;
	while (++i < len / 2)
		ft_swapchar(str + i, str + len - 1 - i);
	return (str);
}
