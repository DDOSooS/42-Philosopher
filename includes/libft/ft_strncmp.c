/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 22:53:22 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/11 19:41:27 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n - 1 && s1[i] == s2[i])
	{
		if (s1[i] == '\0' || i == n - 1)
			return (0);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*================TESTING PART==============
#include<stdio.h>

int main ()
{
    char s1[100];
    char s2[100];
    strcpy(s1,"adbde");
    strcpy(s2,"abdee");
    printf("%d\n",strncmp("test\200", "test\0", 6));
  	printf("%d", ft_strncmp("test\200", "test\0", 6));
   	return (0);
}
===========================================*/
