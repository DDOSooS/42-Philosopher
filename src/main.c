/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:01:35 by aghergho          #+#    #+#             */
/*   Updated: 2024/07/08 00:34:44 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	free_ressoueces(t_table *table)
{
	if (table)
	{
		if (table->philo)
			free(table->philo);
		if (table->forks)
			free(table->forks);
		free(table);
	}
}

void	*start_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	synchronise_threads(&philo->data);
	pthread_mutex_lock(&philo->meals_mx);
	philo->last_meal = get_current_time_ms();
	pthread_mutex_unlock(&philo->meals_mx);
	while (!check_end_simulation(&philo->data)
		&& !check_set_end_simulation(philo))
	{
		eating_routine(&philo);
		sleeping_routine(&philo);
		print_status(3, &philo->data, philo->id);
	}
	return (NULL);
}

void	*supervisor_routine(void *data)
{
	int		i;
	t_table	*table;

	table = (t_table *)data;
	synchronise_threads(&table);
	ft_usleep(100);
	while (!check_end_simulation(&table))
	{
		i = -1;
		while (++i < table->n_philo && !check_end_simulation(&table))
		{
			if (check_set_end_simulation(&table->philo[i]))
				return (NULL);
		}
	}
	return (NULL);
}

void	launch_simulation(t_table **table)
{
	pthread_t	supervisor;
	int			i;

	i = -1;
	pthread_create(&supervisor, NULL, &supervisor_routine, (void *)*table);
	while (++i < (*table)->n_philo)
		pthread_create(&(*table)->philo[i].thread, NULL, &start_routine,
			(void *)&(*table)->philo[i]);
	pthread_mutex_lock(&(*table)->start_smx);
	(*table)->start_simulation = 1;
	(*table)->start_timing = get_current_time_ms();
	pthread_mutex_unlock(&(*table)->start_smx);
	i = -1;
	while (++i < (*table)->n_philo)
		pthread_join((*table)->philo[i].thread, NULL);
	pthread_join(supervisor, NULL);
}

int	main(int ac, char **av)
{
	t_table	*simulation;

	if (ac == 5 || ac == 6)
	{
		if (!ft_check_args(ac, av) || !ft_validate_args(av))
			return (printf("args aren't valid ;( \n"), 1);
		simulation = ft_init_data(av);
		if (!simulation)
			return (printf("args aren't valid ;( \n"), 2);
		if (simulation->n_philo == 1)
			launch_one_philo(simulation->philo);
		else
			launch_simulation(&simulation);
		free_ressoueces(simulation);
	}
	else
		printf("try this format ./exe <n_of_philo> <time_to_die> <t_teat> <t_tsleep> \
		each_philo_must_eat>\n");
	return (0);
}
