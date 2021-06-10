/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:50:26 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/09 19:04:39 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	alive_loop(int i)
{
	if (g_alive)
		philo_sleep(i);
	if (g_alive)
		philo_think(i);
}

void	*philo_thread(void *id_philo)
{
	int				i;
	int				eat;
	int				fork_1;
	int				fork_2;
	struct timeval	last_eat;

	i = *(int *)id_philo;
	eat = 0;
	set_forks(&fork_1, &fork_2, i);
	gettimeofday(&last_eat, NULL);
	while (g_alive)
	{
		if (g_alive)
		{
			last_eat = philo_eat(fork_1, fork_2, i, last_eat);
			eat++;
		}
		if (g_args.time_each_eat > 0 && eat == g_args.time_each_eat)
			break ;
		alive_loop(i);
	}
	free(id_philo);
	return (NULL);
}

int	thread_join_loop(pthread_t *philo)
{
	int	i;

	i = 0;
	while (i < g_args.nb_philo)
	{
		if (pthread_join(philo[i], NULL) != 0)
			return (system_error("pthread_join", i));
		i++;
	}
	return (0);
}

int	thread_loop(void)
{
	int			i;
	int			ret;
	int			*id_philo;
	pthread_t	*philo;

	i = 0;
	philo = malloc(sizeof(pthread_t) * g_args.nb_philo);
	if (!philo)
		system_error("malloc", 0);
	while (i < g_args.nb_philo)
	{
		usleep(20);
		id_philo = malloc(sizeof(int));
		*id_philo = i + 1;
		if (pthread_create(&philo[i], NULL, &philo_thread, id_philo) != 0)
			return (system_error("pthread_create", i));
		i++;
	}
	i = 0;
	ret = thread_join_loop(philo);
	free(philo);
	return (ret);
}
