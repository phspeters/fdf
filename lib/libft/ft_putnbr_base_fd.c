/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_fd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pehenri2 <pehenri2@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 15:26:36 by pehenri2          #+#    #+#             */
/*   Updated: 2023/10/12 17:05:08 by pehenri2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base)
{
	int	i;
	int	j;

	if (ft_strlen(base) == 0 || ft_strlen(base) == 1)
		return (1);
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_putnbr_base_fd(long nb, char *base, int fd)
{
	int		counter;
	long	baselen;

	counter = 0;
	baselen = ft_strlen(base);
	if (check_base(base))
		return (0);
	if (nb < 0)
	{
		counter += write(1, "-", 1);
		nb = nb * -1;
	}
	if (nb >= baselen)
		counter += ft_putnbr_base_fd((nb / baselen), base, fd);
	counter += ft_putchar_fd(base[(nb % baselen)], fd);
	return (counter);
}
