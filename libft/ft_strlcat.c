/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 10:46:18 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/16 12:33:14 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t k;

	i = 0;
	j = 0;
	if (size < ft_strlen(dest))
		k = ft_strlen((char *)src) + size;
	else
		k = ft_strlen(dest) + ft_strlen((char *)src);
	while (dest[i] != '\0')
		i++;
	if (size > 0)
	{
		while (src[j] != '\0' && i < size - 1)
		{
			dest[i] = src[j];
			i++;
			j++;
		}
	}
	dest[i] = '\0';
	return (k);
}
