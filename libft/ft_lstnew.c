/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:42:26 by bfichot           #+#    #+#             */
/*   Updated: 2022/01/31 15:48:02 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstnew(void *content, char *key)
{
	t_list	*element;

	if (!(element = malloc(sizeof(*element))))
		return (NULL);
	element->content = content;
	element->key = key;
	element->next = NULL;
	return (element);
}
