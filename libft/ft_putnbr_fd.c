/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macote <macote@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 10:22:07 by macote            #+#    #+#             */
/*   Updated: 2023/02/18 08:08:24 by macote           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	printnb(int nb, int fd)
{
	int	modulo;
	int	printmodulo;
	int	tableau[11];
	int	i;

	i = 0;
	while (nb != 0)
	{
		modulo = nb % 10;
		printmodulo = modulo + 48;
		tableau[i] = printmodulo;
		nb -= modulo;
		nb /= 10;
		i++;
	}
	i--;
	while (i >= 0)
	{
		if (tableau[i])
		{
			write(fd, &tableau[i], 1);
		}
		i--;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	printnb(n, fd);
}

// int main(void)
// {
// 		ft_putnbr_fd(0, 2);
// }
