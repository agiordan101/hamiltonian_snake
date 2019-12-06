/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strdelchar.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/04/10 14:36:37 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/04/10 15:01:03 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdelcarac(char *str, char c)
{
	char	*new;
	int		count;
	int		i;
	int		j;

	if (!str)
		return (NULL);
	count = 0;
	i = -1;
	while (str[++i])
		if (str[i] != c)
			count++;
	if (!(new = ft_strnew(count)))
		return (NULL);
	j = 0;
	i = -1;
	while (str[++i])
		if (str[i] != c)
			new[j++] = str[i];
	return (new);
}
