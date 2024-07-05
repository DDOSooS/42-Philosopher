/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 20:12:30 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/11 19:06:46 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_count_len(int n)
{
	int		len;
	long	nb;

	nb = n;
	len = 0;
	if (n == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nb;
	int		s;

	s = 1;
	len = ft_count_len(n);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	nb = n;
	if (n < 0)
	{
		nb = -nb;
		s = 0;
	}
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len--] = nb % 10 + '0';
		nb /= 10;
	}
	if (s == 0)
		str[0] = '-';
	return (str);
}
/*====================== TESTING PART =================
int main ()
{
	printf("\t%s\n", ft_itoa(-1005521));
	return (0);
}
===================================================*/
