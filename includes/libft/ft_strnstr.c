/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 12:38:56 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/12 16:30:05 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n_len;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i])
	{
		n_len = 0;
		while (needle[n_len] && i + n_len < len
			&& needle[n_len] == haystack[i + n_len])
			n_len++;
		if (needle[n_len] == '\0')
			return ((char *) &haystack[i]);
		i++;
	}
	return (NULL);
}
/*------------------------testing part---------------------------
#include <stdio.h>
#include <string.h>
int main ()
{
    const char *haystack = NULL;
    const char *needle = "ee";
    size_t haystacklen = 0;
    char *result;

    result = strnstr(haystack, needle, haystacklen);
    if (result)
        printf("%s\n", result);
    return (0);
}
//---------------------------------------------------------------i--*/
