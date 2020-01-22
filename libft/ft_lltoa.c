/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 17:28:18 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/17 21:14:02 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	long long		ft_iterative_power(long long n, int power)
{
	long long output;

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

static	int				get_digits(long long n)
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

char					*ft_lltoa(long long n)
{
	char	*output;
	int		negative;
	int		digits;
	int		i;

	negative = 0;
	i = 0;
	if (n == LLONG_MIN)
		return (ft_strdup("-9223372036854775808"));
	n *= (n < 0) ? -(negative = 1) : 1;
	digits = get_digits(n);
	if (!(output = malloc(sizeof(char) * (digits + negative + 1))))
		return (NULL);
	if (negative)
		output[i++] = '-';
	while (digits > 0)
	{
		output[i++] = (n / ft_iterative_power(10, digits - 1)) + '0';
		n = n % ft_iterative_power(10, digits - 1);
		digits--;
	}
	output[i] = '\0';
	return (output);
}
