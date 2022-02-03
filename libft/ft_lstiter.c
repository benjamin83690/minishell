/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/20 14:44:02 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/20 15:35:21 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list *tmp;

	if (!lst)
		return ;
	while (lst)
	{
		f(lst->content);
		tmp = lst->next;
		lst = tmp;
	}
}
