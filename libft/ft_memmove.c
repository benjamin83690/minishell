/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 14:52:19 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/17 15:14:17 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char *d;
	char *s;
	char *lasts;
	char *lastd;

	d = (char *)dest;
	s = (char *)src;
	lasts = s + (len - 1);
	lastd = d + (len - 1);
	if ((s == NULL) && (d == NULL))
		return (0);
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
		while (len--)
			*lastd-- = *lasts--;
	return (dest);
}
