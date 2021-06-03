/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:14:41 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/03 15:34:58 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"



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
