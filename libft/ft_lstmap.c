/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 15:35:38 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/31 16:27:33 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_elem;

	new_elem = NULL;
	new_lst = new_elem;
	if (!lst || !f)
		return (NULL);
	while (lst)
	{
		if (!(new_elem = ft_lstnew(f(lst->content), lst->key)))
		{
			ft_lstclear(&lst, del);
		}
		lst = lst->next;
		ft_lstadd_back(&new_lst, new_elem);
	}
	return (new_lst);
}
