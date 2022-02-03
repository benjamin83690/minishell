/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 15:17:54 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/17 15:15:43 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char *src;

	src = (unsigned char *)s;
	while (n-- > 0)
	{
		if (*src == (unsigned char)c)
			return (src);
		src++;
	}
	return (NULL);
}
