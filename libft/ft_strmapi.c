/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:56:47 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/17 15:19:03 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*str;

	i = -1;
	if (!(str = malloc(sizeof(char) * ft_strlen((char *)s) + 1)))
		return (NULL);
	while (s[++i])
		str[i] = f(i, s[i]);
	str[i] = '\0';
	return (str);
}
