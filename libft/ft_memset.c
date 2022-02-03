/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:40:18 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/17 15:25:00 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int val, size_t len)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)dest;
	i = -1;
	while (++i < len)
		ptr[i] = val;
	return (dest);
}
