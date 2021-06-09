/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:14:41 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/09 18:32:39 by leickmay         ###   ########lyon.fr   */
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

struct timeval	display_eat(int i, int fork_1, int fork_2, struct timeval last_eat)
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

struct timeval	philo_eat(int fork_1, int fork_2, int i, struct timeval last_eat)
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

void	set_forks(int *fork_1, int *fork_2, int i)
{
	if (i != g_args.nb_philo || g_args.nb_philo == 1)
	{
		*fork_1 = i - 1;
		*fork_2 = i;
	}
	else
	{
		*fork_1 = i - 1;
		*fork_2 = 0;
	}
}

void	*philo_thread(void *id_philo)
{
	int	i;
	int	eat;
	int	fork_1;
	int	fork_2;
	struct timeval	last_eat;

	i = *(int*)id_philo;
	eat = 0;
	set_forks(&fork_1, &fork_2, i);
	gettimeofday(&last_eat, NULL);
	while (g_alive)
	{
		if (g_alive)
			last_eat = philo_eat(fork_1, fork_2, i, last_eat);
			eat++;
		if (g_args.time_each_eat > 0 && eat == g_args.time_each_eat)
			break ;
		if (g_alive)
			philo_sleep(i);
		if (g_alive)
			philo_think(i);
	}
	free(id_philo);
	return (NULL);
}

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

void	g_fork_init(void)
{
	int	i;

	i = 0;
	while (i < g_args.nb_philo)
	{
		g_fork_used[i] = 0;
		i++;
	}
	if (g_args.nb_philo == 1)
		g_fork_used[1] = 0;
}

int	main (int ac, char **av)
{
	char		*str;
	int			i;
	int			*id_philo;
	pthread_t	*philo;

	gettimeofday(&g_begin_time, NULL);
	pthread_mutex_init(&g_mutex, NULL);
	g_alive = 1;
	i = 0;
	if (ac != 6 && ac != 5)
	{
		str = "Wrong number of arguments, the program needs 4 or 5.\n";
		write(2, str, ft_strlen(str));
		return (1);
	}
	if (check_args(av) || parse_args(ac, av))
	{
		str = \
		"Wrong type of arguments, the program only accepts positive int numbers.\n";
		write(2, str, ft_strlen(str));
		return (1);
	}
	if (g_args.nb_philo > 1)
		g_fork_used = malloc(sizeof(int) * g_args.nb_philo);
	else
		g_fork_used = malloc(sizeof(int) * 2);
	g_fork_init();
	philo = malloc(sizeof(pthread_t) * g_args.nb_philo);
	if (!philo)
		system_error("malloc", 0);
	while (i < g_args.nb_philo)
	{
		usleep(20);
		id_philo = malloc(sizeof(int));
		*id_philo = i + 1;
		if (pthread_create(&philo[i], NULL, &philo_thread, id_philo) != 0)
			return(system_error("pthread_create", i));
		i++;
	}
	i = 0;
	while (i < g_args.nb_philo)
	{
		if (pthread_join(philo[i], NULL) != 0)
			return(system_error("pthread_join", i));
		i++;
	}
	pthread_mutex_destroy(&g_mutex);
	free(philo);
	pthread_exit(NULL);
}
