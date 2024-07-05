/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 15:54:00 by aghergho          #+#    #+#             */
/*   Updated: 2024/06/12 18:42:22 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*subs;
	size_t			i;
	unsigned int	t_len;

	t_len = ft_strlen(s);
	if (start >= t_len)
		return (ft_strdup(""));
	if (len > t_len - start)
		len = t_len - start;
	i = 0;
	subs = (char *)malloc(sizeof(char) * (len + 1));
	if (!subs)
		return (NULL);
	while (i < len && s[i + start])
	{
		subs[i] = s[i + start];
		i++;
	}
	subs[i] = '\0';
	return (subs);
}

/*==================== TESTING Part ================
int	main(void)
{
	char	*str;
	char	*subs;

	str = "hello, i'm testing my function";
	subs = ft_substr(str, 4, 3);
	printf("%s\n", ft_substr("hola", 0, 18446744073709551615));
	return (0);
}
//===================================================*/
