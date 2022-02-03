/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfichot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 11:23:31 by bfichot           #+#    #+#             */
/*   Updated: 2021/02/17 15:16:25 by bfichot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	numb;
	int				a;

	if (n < 0)
	{
		write(fd, "-", 1);
		numb = -n;
	}
	else
		numb = n;
	a = ('0' + (numb % 10));
	numb = numb / 10;
	if (numb > 0)
		ft_putnbr_fd(numb, fd);
	write(fd, &a, 1);
}
