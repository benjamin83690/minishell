/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 14:43:27 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/17 15:32:47 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_isin(char c, const char *set)
{
	int		i;

	i = -1;
	while (set[++i])
		if (c == set[i])
			return (1);
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		k;
	int		j;
	int		size;

	size = 0;
	j = ft_strlen((char *)s1) - 1;
	k = 0;
	i = 0;
	while (ft_isin(s1[i], set) == 1)
		i++;
	while (ft_isin(s1[j], set) == 1)
		j--;
	size = i > j ? 2 : (j - i);
	if (!(str = malloc(sizeof(char) * (size + 2))))
		return (NULL);
	while (i <= j)
		str[k++] = s1[i++];
	str[k] = '\0';
	return (str);
}
