/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:26:45 by bfichot           #+#    #+#             */
/*   Updated: 2021/09/26 03:28:42 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		s1len;
	int		s2len;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	i = -1;
	j = -1;
	if (!(str = malloc(sizeof(char) * (s1len + s2len) + 2)))
		return (NULL);
	while (s1[++i])
		str[i] = s1[i];
	str[i] = ' ';
	while (s2[++j])
		str[i++] = s2[j];
	str[i] = '\0';
	return (str);
}
