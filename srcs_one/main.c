/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:14:41 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/04 14:13:43 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	display_args(int ac)
{
	printf("nb_philo : %d\n", g_args.nb_philo);
	printf("time_die : %d\n", g_args.time_die);
	printf("time_eat : %d\n", g_args.time_eat);
	printf("time_sleep : %d\n", g_args.time_sleep);
	if (ac == 6)
		printf("time_each_eat : %d\n", g_args.time_each_eat);
}

int	philo_eat(int i)
{
	struct timeval	current_time;
	int				timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_usec - g_begin_time.tv_usec) / 1000;
	printf("%d ms %d has taken a fork\n", timestamp, i);
	pthread_mutex_lock(&g_mutex);
	g_fork_used = 1;
	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_usec - g_begin_time.tv_usec) / 1000;
	printf("%d ms %d is eating\n", timestamp, i);
	usleep(g_args.time_eat * 1000);
	g_fork_used = 0;
	pthread_mutex_unlock(&g_mutex);
	return (1);
}

int	philo_sleep(int i)
{
	struct timeval	current_time;
	int				timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (current_time.tv_usec - g_begin_time.tv_usec) / 1000;
	printf("%d ms %d is sleeping\n", timestamp, i);
	usleep(g_args.time_sleep * 1000);
	return (1);
}

int	philo_think(int i)
{
	struct timeval	current_time;
	int				timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = (g_begin_time.tv_usec - current_time.tv_usec) / 1000;
	printf("%d ms %d is thinking\n", timestamp, i);
	return (1);
}


void	*philo_thread(void *id_philo)
{
	int				i;

	int				already_eat;
	int				already_sleep;
	int				already_think;

	already_eat = 0;
	already_think = 0;
	already_sleep = 0;
	i = *(int*)id_philo;
	while (g_alive)
	{
		if (!g_fork_used)
		{
			already_eat = philo_eat(i);
			already_think = 0;
		}
		if (already_eat)
		{
			already_sleep = philo_sleep(i);
			already_eat = 0;
		}
		if (already_sleep)
		{
			already_think = philo_think(i);
			already_sleep = 0;
		}
	}
	//printf("bonjour\n");
	//printf("time_die %d\n", g_args.time_die);
	//usleep(g_args.time_sleep * 1000);
	
	
	//sleep(2);
	//printf("id_philo : %d\n", i);
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

int	main (int ac, char **av)
{
	char		*str;
	int			i;
	int			*id_philo;
	pthread_t	*philo;

	gettimeofday(&g_begin_time, NULL);
	printf("seconds : %ld\nmicro seconds : %d\n", 
	g_begin_time.tv_sec, g_begin_time.tv_usec);
	pthread_mutex_init(&g_mutex, NULL);
	g_fork_used = 0;
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
		"Wrong type of arguments, the program only accepts positive numbers.\n";
		write(2, str, ft_strlen(str));
		return (1);
	}
	//display_args(ac);
	philo = malloc(sizeof(pthread_t) * g_args.nb_philo);
	if (!philo)
		system_error("malloc", 0);
	while (i < g_args.nb_philo)
	{
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

	//pthread_exit(NULL);
}
