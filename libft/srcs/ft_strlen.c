/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlen.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: agiordan <agiordan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 17:36:51 by agiordan     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/30 17:48:10 by agiordan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

/*
**	Ne pas proteger
*/

size_t		ft_strlen(char *str)
{
	char	*save;

	save = str;
	while (*str++)
		;
	return (str - save);
}
