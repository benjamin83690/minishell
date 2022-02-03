/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:10:12 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/16 12:20:47 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*str;

	str = 0;
	if (count == 0 || size == 0)
	{
		size = 1;
		count = 1;
	}
	str = malloc(count * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}
