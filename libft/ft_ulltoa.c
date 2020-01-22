/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:35:38 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 21:15:00 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_iterative_power(unsigned long long n, int power)
{
	unsigned long long output;

	output = n;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 1)
	{
		output = output * n;
		power--;
	}
	return (output);
}

static	int					get_digits(unsigned long long n)
{
	int	digits;

	if (n == 0)
		return (1);
	digits = 0;
	while (n > 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

char						*ft_ulltoa(unsigned long long n)
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
