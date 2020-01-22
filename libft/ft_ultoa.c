/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:43:53 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/25 15:54:24 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	unsigned long	ft_iterative_power(unsigned long nb, int power)
{
	unsigned long output;

	output = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 1)
	{
		output = output * nb;
		power--;
	}
	return (output);
}

static	int				get_digits(unsigned long nb)
{
	int	digits;

	if (nb == 0)
		return (1);
	digits = 0;
	while (nb > 0)
	{
		nb = nb / 10;
		digits++;
	}
	return (digits);
}

char					*ft_ultoa(unsigned long n)
{
	char	*output;
	int		digits;
	int		i;

	i = 0;
	digits = get_digits(n);
	if (!(output = malloc(sizeof(char) * (digits + 1))))
		return (NULL);
	while (digits > 0)
	{
		output[i++] = (n / ft_iterative_power(10, digits - 1)) + '0';
		n = n % ft_iterative_power(10, digits - 1);
		digits--;
	}
	output[i] = '\0';
	return (output);
}
