/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 11:26:32 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/17 15:27:07 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	j = 0;
	if (s2[i] == 0)
		return ((char *)s1);
	while (s1[i] && i < len)
	{
		while (s1[i + j] == s2[j] && ((i + j) < len))
		{
			j++;
			if (s2[j] == '\0')
				return ((char *)&s1[i]);
		}
		i++;
		j = 0;
	}
	return (0);
}
