/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ininting_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:46:56 by aghergho          #+#    #+#             */
/*   Updated: 2024/07/08 00:35:13 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	init_mutexes(t_table **table)
{
	int	i;

	i = -1;
	pthread_mutex_init(&(*table)->meals_mx, NULL);
	pthread_mutex_init(&(*table)->done_mx, NULL);
	pthread_mutex_init(&(*table)->write_mx, NULL);
	pthread_mutex_init(&(*table)->start_smx, NULL);
	while (++i < (*table)->n_philo)
		pthread_mutex_init(&(*table)->forks[i], NULL);
}

void	assing_forks(t_table **table, t_philo *philo, int n_philos,
		int philo_id)
{
	(philo)->fst_fork = &(*table)->forks[philo_id];
	(philo)->scd_fork = &(*table)->forks[(philo_id + 1) % n_philos];
	if (philo_id % 2)
	{
		(philo)->fst_fork = &(*table)->forks[(philo_id + 1) % n_philos];
		(philo)->scd_fork = &(*table)->forks[philo_id];
	}
}

void	generate_philos(t_table **table, char **args)
{
	int	i;

	i = -1;
	while (++i < (*table)->n_philo)
	{
		(*table)->philo[i].data = *table;
		(*table)->philo[i].id = i;
		(*table)->philo[i].last_meal = 0;
		(*table)->philo[i].n_meals_eat = 0;
		(*table)->philo[i].time_tdie = ft_itol(args[2]);
		(*table)->philo[i].time_teat = ft_itol(args[3]);
		(*table)->philo[i].time_tsleep = ft_itol(args[4]);
		pthread_mutex_init(&(*table)->philo[i].lastml_mx, NULL);
		pthread_mutex_init(&(*table)->philo[i].meals_mx, NULL);
		assing_forks(table, &(*table)->philo[i], (*table)->n_philo, i);
	}
}

t_table	*ft_init_data(char **av)
{
	t_table	*table;

	table = malloc(sizeof(t_table));
	if (!table)
		return (NULL);
	table->n_philo = ft_itol(av[1]);
	table->done_flag = 0;
	table->meals = 0;
	table->start_simulation = 0;
	table->time_teat = ft_itol(av[3]);
	table->n_meals_teat = -1;
	if (av[5])
		table->n_meals_teat = ft_itol(av[5]);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		return (free_ressoueces(table), NULL);
	table->philo = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philo)
		return (free_ressoueces(table), NULL);
	generate_philos(&table, av);
	init_mutexes(&table);
	return (table);
}
