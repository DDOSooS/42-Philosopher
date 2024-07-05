/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aghergho <aghergho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 23:24:35 by aghergho          #+#    #+#             */
/*   Updated: 2023/11/12 21:37:35 by aghergho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*new_node;
	t_list	*temp;

	new = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		temp = f(lst->content);
		if (!temp)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}	
		new_node = ft_lstnew(temp);
		if (!new_node)
		{
			ft_lstclear(&new, del);
			return (NULL);
		}	
		ft_lstadd_back(&new, new_node);
		lst = lst->next;
	}
	return (new);
}

/*=========================TESTING PART=======================
#include <stdio.h>
void	del(void *content)
{
	free(content);
}

void	*square_int(void *a)
{
	int	*result;

	if (a)
	{
		result = (int *)malloc(sizeof(int));
		if (result)
		{
			*result = (*(int *)a) * (*(int *)a);
			// printf("Result: %d\n", *result); // Commented for final code
			return ((void *)result);
		}
	}
	return (NULL);
}

int	main(void)
{
	t_list	*lst;
	t_list	*new_lst;
	t_list	*temp;
	int		*a;
	int		*b;

	a = (int *)malloc(sizeof(int));
	if (!a)
		return (0);
	b = (int *)malloc(sizeof(int));
	if (!b)
		return (0);
	*a = 3;
	*b = 2;
	lst = ft_lstnew((void *)a);
	lst->next = ft_lstnew((void *)b);
	new_lst = ft_lstmap(lst, square_int, del);
	while (new_lst)
	{
		printf("%d\n", *(int *)new_lst->content);
		temp = new_lst;
		new_lst = new_lst->next;
		free(temp->content);
		free(temp);
	}
	return (0);
}
//===========================================================*/
