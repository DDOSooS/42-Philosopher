/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:22:28 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/12 18:15:38 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	j;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	j = 0;
	if (size == 0)
		return (len_src);
	if (size <= len_dest)
		return (len_src + size);
	while (src[j] && (len_dest + j) < (size - 1))
	{
		dest[len_dest + j] = src[j];
		j++;
	}
	dest[len_dest + j] = '\0';
	return (len_src + len_dest);
}

/*===========TESTING PART==================
int	main(void)
{
    char dst[100];
    char src[100];

    
    strcpy(src, "abde");
    strcpy(dst, "gher");
    ft_strlcat(dst, src, 100);
    printf("%s\n", dst);
    return (0);
}
========================================*/
