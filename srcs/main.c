/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:14:41 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/09 19:05:31 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	set_timestamp(void)
{
	struct timeval	current_time;
	long			timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = ((current_time.tv_sec * 1000000 + current_time.tv_usec) - \
	(g_begin_time.tv_sec * 1000000 + g_begin_time.tv_usec)) / 1000;
	return (timestamp);
}

int	main (int ac, char **av)
{
	int		ret;

	gettimeofday(&g_begin_time, NULL);
	pthread_mutex_init(&g_mutex, NULL);
	g_alive = 1;
	if (ac != 6 && ac != 5)
	{
		ft_puterr("Wrong number of arguments, the program needs 4 or 5.\n");
		return (1);
	}
	if (check_args(av) || parse_args(ac, av))
	{
		ft_puterr("The program only accepts positive int numbers.\n");
		return (1);
	}
	g_fork_init();
	ret = thread_loop();
	pthread_mutex_destroy(&g_mutex);
	pthread_exit(NULL);
	return (ret);
}
