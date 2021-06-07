/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:15:05 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/07 15:09:00 by leickmay         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_args
{
	int	nb_philo;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	time_each_eat;
}				t_args;

t_args			g_args;
pthread_mutex_t	g_mutex;
int				*g_fork_used;
int				g_alive;
int				g_init_time;
struct timeval	g_begin_time;

int	ft_strlen(char *str);
int	check_args(char **av);
int	parse_args(int ac, char **av);


#endif