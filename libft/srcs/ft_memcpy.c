/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_memcpy.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 20:47:36 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/10/10 21:47:01 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <string.h>
#include "../include/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*castsrc;
	char	*castdest;
	size_t	len1;
	size_t	len2;
	size_t	i;

	castsrc = (char *)src;
	castdest = (char *)dest;
	len1 = ft_strlen(castsrc);
	len2 = ft_strlen(castdest);
	i = 0;
	while (i < n && i < len1 && i < len2)
	{
		castdest[i] = castsrc[i];
		i++;
	}
	return (castdest);
}
