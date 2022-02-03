/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 12:07:48 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/25 13:40:41 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char *s;
	unsigned char l;
	unsigned char *d;

	d = (unsigned char *)dest;
	l = (unsigned char)c;
	s = (unsigned char *)src;
	while (n && *s != l)
	{
		*d++ = *s++;
		n--;
	}
	if (*s == l && n)
	{
		*d++ = *s++;
		return ((void *)d);
	}
	return (NULL);
}
