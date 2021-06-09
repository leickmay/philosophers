/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:55:19 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/09 19:05:29 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	check_eat_time(struct timeval last_eat, int i)
{
	struct timeval	current_time;
	long			timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = ((current_time.tv_sec * 1000000 + current_time.tv_usec) - \
	(last_eat.tv_sec * 1000000 + last_eat.tv_usec)) / 1000;
	if (timestamp >= g_args.time_die)
	{
		printf("\033[0;31m%ld ms %d died\n\033[0m", set_timestamp(), i);
		g_alive = 0;
	}
	return (timestamp);
}

struct timeval	display_eat(int i, int fork_1, int fork_2, \
struct timeval last_eat)
{
	long	timestamp;

	timestamp = set_timestamp();
	printf("\033[0;32m%ld ms %d is eating\n\033[0m", timestamp, i);
	usleep(g_args.time_eat * 1000);
	pthread_mutex_lock(&g_mutex);
	g_fork_used[fork_2] = 0;
	g_fork_used[fork_1] = 0;
	pthread_mutex_unlock(&g_mutex);
	gettimeofday(&last_eat, NULL);
	return (last_eat);
}

struct timeval	philo_eat(int fork_1, int fork_2, int i, \
struct timeval last_eat)
{
	long	timestamp;
	int		state;
	int		fork1_took;
	int		fork2_took;

	state = 0;
	fork1_took = 0;
	fork2_took = 0;
	timestamp = set_timestamp();
	while (state == 0)
	{
		usleep(100);
		if (check_eat_time(last_eat, i) >= g_args.time_die || g_alive == 0)
			break ;
		if (!g_fork_used[fork_1])
			fork1_took = take_forks(fork_1, i);
		if (!g_fork_used[fork_2])
			fork2_took = take_forks(fork_2, i);
		if (fork2_took && fork1_took)
		{
			last_eat = display_eat(i, fork_1, fork_2, last_eat);
			state = 1;
		}
	}
	return (last_eat);
}

int	philo_sleep(int i)
{
	long	timestamp;

	timestamp = set_timestamp();
	printf("%ld ms %d is sleeping\n", timestamp, i);
	usleep(g_args.time_sleep * 1000);
	return (1);
}

int	philo_think(int i)
{
	long	timestamp;

	timestamp = set_timestamp();
	printf("%ld ms %d is thinking\n", timestamp, i);
	return (1);
}
