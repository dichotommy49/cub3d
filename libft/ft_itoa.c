/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:43:53 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/15 17:21:04 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_iterative_power(int nb, int power)
{
	int output;

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

static	int		get_digits(long nb)
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

char			*ft_itoa(int n)
{
	char	*output;
	int		negative;
	int		digits;
	int		i;
	long	nb;

	negative = 0;
	i = 0;
	if (n < 0)
		negative = 1;
	nb = (n <= 0) ? -(long)n : (long)n;
	digits = get_digits(nb);
	if (!(output = malloc(sizeof(char) * (digits + negative + 1))))
		return (NULL);
	if (negative)
		output[i++] = '-';
	while (digits > 0)
	{
		output[i++] = (nb / ft_iterative_power(10, digits - 1)) + '0';
		nb = nb % ft_iterative_power(10, digits - 1);
		digits--;
	}
	output[i] = '\0';
	return (output);
}
