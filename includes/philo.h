/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 19:57:23 by aghergho          #+#    #+#             */
/*   Updated: 2024/07/07 19:19:03 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "libft/libft.h"
# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <time.h>
# include <unistd.h>

#define COLOR_GREEN "\033[0;32m"
#define COLOR_RESET "\033[0m"
#define COLOR_RED "\033[0;31m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"

typedef struct philo
{
	int				id;
	pthread_t		thread;
	int				n_meals_eat;
	size_t			last_meal;
	size_t			time_teat;
	size_t			time_tdie;
	size_t			time_tsleep;
	pthread_mutex_t	lastml_mx;
	pthread_mutex_t	meals_mx;
	pthread_mutex_t	*fst_fork;
	pthread_mutex_t	*scd_fork;
	struct table	*data;
}					t_philo;

typedef struct table
{
	int				done_flag;
	int				meals;
	int				n_philo;
	int				start_simulation;
	int				n_meals_teat;
	size_t			start_timing;
	size_t			time_teat;
	pthread_mutex_t	start_smx;
	pthread_mutex_t	done_mx;
	pthread_mutex_t	meals_mx;
	pthread_mutex_t	write_mx;
	pthread_mutex_t	*forks;
	t_philo			*philo;
}					t_table;
void set_end_simulation(t_table **table, int philo_id);
int					check_end_game(t_philo **philo);
int check_set_end_simulation(t_philo *philo);
#endif