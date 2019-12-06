/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlenbin.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/30 17:48:21 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/30 17:48:50 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
**	Ne pas proteger
*/

size_t		ft_strlenbin(unsigned long long *str)
{
	size_t	count;

	count = 0;
	while (1)
		if ((++count && !(*str & 0x00000000000000FF)) ||\
			(++count && !(*str & 0x000000000000FF00)) ||\
			(++count && !(*str & 0x0000000000FF0000)) ||\
			(++count && !(*str & 0x00000000FF000000)) ||\
			(++count && !(*str & 0x000000FF00000000)) ||\
			(++count && !(*str & 0x0000FF0000000000)) ||\
			(++count && !(*str & 0x00FF000000000000)) ||\
			(++count && !(*str++ & 0xFF00000000000000)))
			return (count - 1);
}


// size_t		ft_strlenbin(unsigned long long *str)
// {
// 	unsigned long long	*save;
// 	int					tmp;

// 	save = str;
// 	tmp = 0;
// 	while (1)
// 		if ((tmp = !(*str & 0x00000000000000FF) ? 1 : 0) ||\
// 			(tmp = !(*str & 0x000000000000FF00) ? 2 : 0) ||\
// 			(tmp = !(*str & 0x0000000000FF0000) ? 3 : 0) ||\
// 			(tmp = !(*str & 0x00000000FF000000) ? 4 : 0) ||\
// 			(tmp = !(*str & 0x000000FF00000000) ? 5 : 0) ||\
// 			(tmp = !(*str & 0x0000FF0000000000) ? 6 : 0) ||\
// 			(tmp = !(*str & 0x00FF000000000000) ? 7 : 0) ||\
// 			(tmp = !(*str++ & 0xFF00000000000000) ? 8 : 0))
// 			return (str - save + tmp);
// }
