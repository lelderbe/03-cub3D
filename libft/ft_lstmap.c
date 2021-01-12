/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 11:02:53 by lelderbe          #+#    #+#             */
/*   Updated: 2020/11/11 12:47:07 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*list;
	void	*content;

	list = 0;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
		{
			ft_lstclear(&list, del);
			break ;
		}
		ft_lstadd_back(&list, ft_lstnew(content));
		lst = lst->next;
	}
	return (list);
}
