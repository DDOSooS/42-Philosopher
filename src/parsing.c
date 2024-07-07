/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 22:42:02 by aghergho          #+#    #+#             */
/*   Updated: 2024/07/08 00:35:41 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

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

int	ft_check_number(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (i == 0 && (str[0] == '+' || str[0] == '-'))
			continue ;
		if (!isdigit(str[i]))
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
