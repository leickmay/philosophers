/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:53:16 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/09 18:53:48 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	system_error(char *err, int i)
{
	char	*str;
	char	c;

	c = i + '0';
	str = "error: ";
	write(2, str, ft_strlen(str));
	write(2, err, ft_strlen(err));
	write(2, " ", 1);
	write(2, &c, 1);
	write(2, ".\n", 2);
	return (1);
}

void	ft_puterr(char *str)
{
	write(2, str, ft_strlen(str));
}
