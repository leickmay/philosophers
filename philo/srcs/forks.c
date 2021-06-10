/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 18:57:13 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/10 13:15:12 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	take_forks(int fork, int i)
{
	long	timestamp;

	if (!g_fork_used[fork])
	{
		pthread_mutex_lock(&g_mutex);
		g_fork_used[fork] = 1;
		pthread_mutex_unlock(&g_mutex);
		timestamp = set_timestamp();
		printf("%ld ms %d has taken a fork\n", timestamp, i);
		return (1);
	}
	return (0);
}

void	set_forks(int *fork_1, int *fork_2, int i)
{
	if (i != g_args.nb_philo && g_args.nb_philo != 1)
	{
		*fork_1 = i - 1;
		*fork_2 = i;
	}
	else if (g_args.nb_philo != 1)
	{
		*fork_1 = i - 1;
		*fork_2 = 0;
	}
	else if (g_args.nb_philo == 1)
		fork_1 = 0;
}

void	g_fork_init(void)
{
	int	i;

	if (g_args.nb_philo > 0)
		g_fork_used = malloc(sizeof(int) * g_args.nb_philo);
	i = 0;
	while (i < g_args.nb_philo)
	{
		g_fork_used[i] = 0;
		i++;
	}
}
