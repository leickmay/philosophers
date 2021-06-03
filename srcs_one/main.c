/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:14:41 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/03 15:27:55 by leickmay         ###   ########lyon.fr   */
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

void	display_args(int ac, t_args *args)
{
	printf("nb_philo : %d\n", args->nb_philo);
	printf("time_die : %d\n", args->time_die);
	printf("time_eat : %d\n", args->time_eat);
	printf("time_sleep : %d\n", args->time_sleep);
	if (ac == 6)
		printf("time_each_eat : %d\n", args->time_each_eat);
}

int	main (int ac, char **av)
{
	char	*str;
	t_args	args;

	if (ac != 6 && ac != 5)
	{
		str = "Wrong number of arguments, the program needs 4 or 5.\n";
		write(2, str, ft_strlen(str));
		return (1);
	}
	if (check_args(av) || parse_args(ac, av, &args))
	{
		str = \
		"Wrong type of arguments, the program only accepts positive numbers.\n";
		write(2, str, ft_strlen(str));
		return (1);
	}
	display_args(ac, &args);
}
