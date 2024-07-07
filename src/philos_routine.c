/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:49:45 by aghergho          #+#    #+#             */
/*   Updated: 2024/07/08 00:29:52 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	start_simulation(t_table **table)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&(*table)->start_smx);
	if ((*table)->start_simulation)
		status = 1;
	pthread_mutex_unlock(&(*table)->start_smx);
	return (status);
}

void	synchronise_threads(t_table **table)
{
	while (!start_simulation(table))
		;
}

void	eating_routine(t_philo **philo)
{
	if (check_end_simulation(&(*philo)->data)
		&& !check_set_end_simulation(*philo))
		return ;
	pthread_mutex_lock((*philo)->fst_fork);
	print_status(0, &(*philo)->data, (*philo)->id);
	pthread_mutex_lock((*philo)->scd_fork);
	print_status(0, &(*philo)->data, (*philo)->id);
	pthread_mutex_lock(&(*philo)->lastml_mx);
	(*philo)->last_meal = get_current_time_ms();
	pthread_mutex_unlock(&(*philo)->lastml_mx);
	pthread_mutex_lock(&(*philo)->meals_mx);
	(*philo)->n_meals_eat++;
	pthread_mutex_unlock(&(*philo)->meals_mx);
	print_status(1, &(*philo)->data, (*philo)->id);
	if (!check_end_simulation(&(*philo)->data))
		ft_usleep((*philo)->time_teat);
	pthread_mutex_lock(&(*philo)->data->meals_mx);
	if ((*philo)->n_meals_eat == (*philo)->data->n_meals_teat)
		(*philo)->data->meals++;
	pthread_mutex_unlock(&(*philo)->data->meals_mx);
	pthread_mutex_unlock((*philo)->fst_fork);
	pthread_mutex_unlock((*philo)->scd_fork);
}

void	sleeping_routine(t_philo **philo)
{
	if (check_end_simulation(&(*philo)->data)
		&& check_set_end_simulation(*philo))
		return ;
	print_status(2, &(*philo)->data, (*philo)->id);
	ft_usleep((*philo)->time_tsleep);
}

void	launch_one_philo(t_philo *philo)
{
	philo->data->start_timing = get_current_time_ms();
	print_status(0, &philo->data, 0);
	ft_usleep(philo->time_tdie);
	print_status(4, &philo->data, 0);
}
