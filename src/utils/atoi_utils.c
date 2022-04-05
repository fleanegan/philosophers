/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschlute <fschlute@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 17:45:45 by fschlute          #+#    #+#             */
/*   Updated: 2022/04/04 17:46:39 by fschlute         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_atoi_unsigned(const char *in)
{
	long int	res;
	long int	res_bef;

	res = 0;
	while (ft_isdigit(*in))
	{
		res_bef = res;
		res = 10 * res + (*in++ - '0');
		if (res_bef > res)
		{
			ft_fast_putstr("overflow detected");
			return (0);
		}
	}
	return ((int) res);
}

static void	print_nbr(int i, int fd)
{
	write(1, &i, fd);
}

void	ft_putnbr_fd(int nb, int fd)
{
	unsigned int	nbr;

	if (nb < 0)
	{
		write(1, "-", fd);
		nbr = -nb;
	}
	else
		nbr = nb;
	if (nbr / 10 == 0)
		print_nbr(nbr + '0', fd);
	else
	{
		ft_putnbr_fd(nbr / 10, fd);
		print_nbr(nbr % 10 + '0', fd);
	}
}
