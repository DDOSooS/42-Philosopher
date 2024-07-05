/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:11:19 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/11 17:21:26 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	len;

	len = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (len);
	while (src[i] != '\0' && i < size - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len);
}

/*=====================testing part===============
int test (char *str)
{
    int len ;

    len = ft_strlen(str);
    return (len);
}
#include<stdio.h>
#include <string.h>
int main(void)
{
    char str[100];

    strcpy(str," abdeeeeeeeee");
    printf("%d\n",test("hello"));
    return (0);
}
=================================================*/
