/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leickmay <leickmay@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 14:15:05 by leickmay          #+#    #+#             */
/*   Updated: 2021/06/03 15:37:25 by leickmay         ###   ########lyon.fr   */
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

int	ft_strlen(char *str);
int	check_args(char **av);
int	parse_args(int ac, char **av, t_args *args);


#endif