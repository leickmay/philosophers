/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:34:27 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/03 15:35:05 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi(char *str)
{
	long	nb;

	nb = 0;
	while (*str)
	{
		nb = *str - '0' + (nb * 10);
		str++;
		if (nb > 2147483647 || nb < 0)
			return (-1);
	}
	return (nb);
}

int	check_args(char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < 48 || av[i][j] > 57)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_args(int ac, char **av, t_args *args)
{
	args->nb_philo = ft_atoi(av[1]);
	args->time_die = ft_atoi(av[2]);
	args->time_eat = ft_atoi(av[3]);
	args->time_sleep = ft_atoi(av[4]);
	if (ac == 6)
		args->time_each_eat = ft_atoi(av[5]);
	else
		args->time_each_eat = 0;
	if (args->nb_philo < 0 || args->time_die < 0 || args->time_eat < 0 || \
	args->time_sleep < 0 || args->time_each_eat < 0)
		return (1);
	return (0);
}
