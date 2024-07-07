/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/11 20:01:35 by aghergho          #+#    #+#             */
/*   Updated: 2024/07/07 19:35:31 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

long	ft_itol(const char *nptr)
{
	int		i;
	long	sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_check_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0 && (str[0] == '+' || str[0] == '-'))
			continue ;
		if (!ft_isdigit(str[i]))
			return (0);
	}
	return (1);
}

int	ft_check_args(int ac, char **av)
{
	int	i;

	i = 0;
	while (++i < ac)
	{
		if (!ft_check_number(av[i]))
			return (0);
	}
	return (1);
}
void	var_dump_forks(pthread_mutex_t *fork, int number);

/*
	getter of philosofer type
*/
/*
	current routine can be 0 || 1 || 2
	0 for odd philosofers
	1 for even philosofers
	2  if ( number of philosofer
		% 2 != 1) the last even philosofer is being treated lonly as a special case
*/
void	var_dump_forks(pthread_mutex_t *fork, int number)
{
	int	i;

	i = -1;
	printf("------forks address checking:------\n");
	while (++i < number)
	{
		printf("------addr:(%p)------\n", &fork[i]);
	}
	printf("------address checking:------\n");
}

int	ft_validate_args(char **av)
{
	if (ft_itol(av[1]) < 1 || ft_itol(av[2]) < 0 || ft_itol(av[3]) < 0
		|| ft_itol(av[4]) < 0)
		return (0);
	if (ft_itol(av[2]) > INT_MAX || ft_itol(av[3]) > INT_MAX
		|| ft_itol(av[4]) > INT_MAX)
		return (0);
	if (av[5])
		if (ft_itol(av[5]) <= 0)
			return (0);
	return (1);
}

size_t	get_current_time_ms(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(600);
	return (0);
}

/*
	1 => eating4 410 200 200
	2 => thinking
	3 => sleeping
*/

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

void	init_mutexes(t_table **table)
{
	// printf("======(%p)======<<<<<<<<<\n",table);
    int     i;

    i = -1;
	pthread_mutex_init(&(*table)->meals_mx, NULL);
	pthread_mutex_init(&(*table)->done_mx, NULL);
	pthread_mutex_init(&(*table)->write_mx, NULL);
	pthread_mutex_init(&(*table)->start_smx, NULL);
    while (++i < (*table)->n_philo)
        pthread_mutex_init(&(*table)->forks[i], NULL);    
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
	// printf(">>>%p<<<\n", &table);
	while (!start_simulation(table))
		;
}

int	check_end_simulation(t_table **data)
{
	int	status;

	status = 0;
	pthread_mutex_lock(&(*data)->done_mx);
	if ((*data)->done_flag)
		status = 1;
	pthread_mutex_unlock(&(*data)->done_mx);
	return (status);
}

void	print_status(int state, t_table **table, int philo_id)
{
	size_t	curr_time;

	curr_time = get_current_time_ms();
	pthread_mutex_lock(&(*table)->write_mx);
	if (!state && !check_end_simulation(table))
		printf("%ld %d has taken a fork\n", curr_time - (*table)->start_timing, philo_id + 1);
	else if (state == 1 && !check_end_simulation(table))
		printf(COLOR_GREEN "%ld %d is eating 🍪" COLOR_RESET "\n", curr_time - (*table)->start_timing, philo_id + 1);
	else if (state == 2 && !check_end_simulation(table))
		printf(BLUE "%ld %d is slepping 😴"COLOR_RESET"\n", curr_time - (*table)->start_timing, philo_id + 1);
	else if (state == 3 && !check_end_simulation(table))
		printf(YELLOW "%ld %d is thinking 💡"COLOR_RESET"\n", curr_time - (*table)->start_timing, philo_id + 1);
	else if (state == 4 && !check_end_simulation(table))
		printf("%ld %d  died 😵\n", curr_time - (*table)->start_timing, philo_id + 1);
	pthread_mutex_unlock(&(*table)->write_mx);
}
  
void	eating_routine(t_philo **philo)
{
	if (check_end_simulation(&(*philo)->data) && !check_set_end_simulation(*philo))
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
    if (check_end_simulation(&(*philo)->data) && check_set_end_simulation(*philo))
		return ;		
	print_status(2, &(*philo)->data, (*philo)->id);
    ft_usleep((*philo)->time_tsleep);        
}

void	*start_routine(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	synchronise_threads(&philo->data);
	pthread_mutex_lock(&philo->meals_mx);
	philo->last_meal = get_current_time_ms();
	pthread_mutex_unlock(&philo->meals_mx);
	while (!check_end_simulation(&philo->data) && !check_set_end_simulation(philo))
	{
		eating_routine(&philo);
		sleeping_routine(&philo);
        print_status(3, &philo->data, philo->id);
	}
	return (NULL);
}


int	check_die_philo(t_philo *philo)
{
	int		status;
	size_t	curr_time;

	status = 0;
	pthread_mutex_lock(&(philo)->lastml_mx);
	curr_time = get_current_time();
	if (curr_time - (philo)->last_meal > (philo)->time_tdie)
	{
		// printf("%ld ==die time\n", curr_time - philo->ls);
		print_status(4, &philo->data, philo->id);
		set_end_simulation(&philo->data, philo->id);
		status = 1;
	}
	pthread_mutex_unlock(&(philo)->lastml_mx);
	return (status);
}

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

int check_set_end_simulation(t_philo *philo)
{
	if (check_die_philo(philo) || check_full_eating(&philo->data, philo->id))
		return (1);
	return (0);
}
void set_end_simulation(t_table **table, int philo_id)
{
	pthread_mutex_lock(&(*table)->done_mx);
	(*table)->done_flag = philo_id + 1;
	pthread_mutex_unlock(&(*table)->done_mx);
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

void launch_one_philo(t_philo *philo)
{
    philo->data->start_timing = get_current_time_ms();
    print_status(0, &philo->data, 0);
    ft_usleep(philo->time_tdie);
    print_status(4, &philo->data, 0);

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
		printf("Please try running the program again with this format ./exe <number_of_philo> <time_to_die> <time_to_eat> <time_to_sleep> <number_of_times_each_philosopher_must_eat>\n");
	return (0);
}
