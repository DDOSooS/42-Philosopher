/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_simulation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:56:58 by aghergho          #+#    #+#             */
/*   Updated: 2024/07/08 00:30:15 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_full_eating(t_table **table, int philo_id)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&(*table)->meals_mx);
	if ((*table)->meals == (*table)->n_philo)
	{
		status = 1;
		set_end_simulation(table, philo_id);
	}
	pthread_mutex_unlock(&(*table)->meals_mx);
	return (status);
}

int	check_die_philo(t_philo *philo)
{
	int		status;
	size_t	curr_time;

	status = 0;
	pthread_mutex_lock(&(philo)->lastml_mx);
	curr_time = get_current_time_ms();
	if (curr_time - (philo)->last_meal > (philo)->time_tdie)
	{
		print_status(4, &philo->data, philo->id);
		set_end_simulation(&philo->data, philo->id);
		status = 1;
	}
	pthread_mutex_unlock(&(philo)->lastml_mx);
	return (status);
}

void	set_end_simulation(t_table **table, int philo_id)
{
	pthread_mutex_lock(&(*table)->done_mx);
	(*table)->done_flag = philo_id + 1;
	pthread_mutex_unlock(&(*table)->done_mx);
}

int	check_set_end_simulation(t_philo *philo)
{
	if (check_die_philo(philo) || check_full_eating(&philo->data, philo->id))
		return (1);
	return (0);
}

int	check_end_simulation(t_table **data)
{
	int		status;

	status = 0;
	pthread_mutex_lock(&(*data)->done_mx);
	if ((*data)->done_flag)
		status = 1;
	pthread_mutex_unlock(&(*data)->done_mx);
	return (status);
}
