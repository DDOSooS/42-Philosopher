/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 23:05:17 by aghergho          #+#    #+#             */
/*   Updated: 2024/07/08 00:30:43 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

size_t	get_current_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time_ms();
	while ((get_current_time_ms() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print_status(int state, t_table **table, int philo_id)
{
	size_t	curr_time;

	curr_time = get_current_time_ms();
	pthread_mutex_lock(&(*table)->write_mx);
	if (!state && !check_end_simulation(table))
		printf("%ld %d has taken a fork\n", curr_time - (*table)->start_timing,
			philo_id + 1);
	else if (state == 1 && !check_end_simulation(table))
		printf(COLOR_GREEN "%ld %d is eating 🍪" COLOR_RESET "\n", curr_time
			- (*table)->start_timing, philo_id + 1);
	else if (state == 2 && !check_end_simulation(table))
		printf(BLUE "%ld %d is slepping 😴" COLOR_RESET "\n", curr_time
			- (*table)->start_timing, philo_id + 1);
	else if (state == 3 && !check_end_simulation(table))
		printf(YELLOW "%ld %d is thinking 💡" COLOR_RESET "\n", curr_time
			- (*table)->start_timing, philo_id + 1);
	else if (state == 4 && !check_end_simulation(table))
		printf("%ld %d  died 😵\n", curr_time - (*table)->start_timing, philo_id
			+ 1);
	pthread_mutex_unlock(&(*table)->write_mx);
}
