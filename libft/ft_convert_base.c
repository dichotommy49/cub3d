/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 16:32:42 by tmelvin           #+#    #+#             */
/*   Updated: 2019/12/01 13:36:13 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			base_is_invalid(char *base, int base_nbr)
{
	int i;
	int j;

	if (base_nbr <= 1)
		return (1);
	i = 0;
	while (base[i])
	{
		if (base[i] == '+' || base[i] == '-')
			return (1);
		else if (base[i] < 33)
			return (1);
		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int			find_char(char c, char *base_from)
{
	int i;

	i = 0;
	while (base_from[i])
	{
		if (base_from[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

static long long	debase(char *nbr, char *base_from, int base_from_nbr)
{
	int			sign;
	long long	result;

	result = 0;
	sign = 1;
	while (*nbr < 33)
		nbr++;
	while (*nbr == '+' || *nbr == '-')
	{
		if (*nbr == '-')
			sign *= -1;
		nbr++;
	}
	while (*nbr && find_char(*nbr, base_from) > -1)
	{
		result = result * base_from_nbr;
		result = result + find_char(*nbr, base_from);
		nbr++;
	}
	return (result * sign);
}

static char			*rebase(long long debased_nbr, char *base_to,
		int base_to_nbr)
{
	int		negative;
	int		i;
	long	nb;
	char	*output;

	negative = 0;
	i = 0;
	nb = debased_nbr;
	output = malloc(33 * sizeof(char));
	if (nb < 0)
	{
		negative = 1;
		nb = -nb;
	}
	while (nb > 0)
	{
		output[i++] = base_to[nb % base_to_nbr];
		nb /= base_to_nbr;
	}
	if (negative)
		output[i++] = '-';
	output[i] = '\0';
	ft_strrev(output);
	return (output);
}

char				*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	long long		debased_nbr;
	int				base_from_nbr;
	int				base_to_nbr;
	char			*output;

	base_from_nbr = ft_strlen(base_from);
	base_to_nbr = ft_strlen(base_to);
	if (base_is_invalid(base_from, base_from_nbr) ||
			base_is_invalid(base_to, base_to_nbr))
		return (NULL);
	debased_nbr = debase(nbr, base_from, base_from_nbr);
	if (debased_nbr == 0)
	{
		output = malloc(2 * sizeof(char));
		output[0] = base_to[0];
		output[1] = '\0';
	}
	else
		output = rebase(debased_nbr, base_to, base_to_nbr);
	return (output);
}
