/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strnext.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 13:48:45 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 14:59:52 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnext(char *str)
{
	char	*next;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] != ' ' && !(str[i] >= 9 && str[i] <= 13))
		i++;
	if (!(next = ft_strsub(str, 0, i)))
		return (NULL);
	return (next);
}
