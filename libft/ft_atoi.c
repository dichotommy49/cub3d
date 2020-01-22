/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:59:07 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/27 16:20:22 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_isspace(char input)
{
	if (input == ' ' || input == '\n' || input == '\t' || input == '\v' ||
			input == '\f' || input == '\r')
		return (1);
	else
		return (0);
}

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	output;

	output = 0;
	i = 0;
	sign = 1;
	if (str == NULL)
		return (0);
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		sign = (str[i++] == '-') ? -1 : 1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (output > LONG_MAX / 10 ||
				(output == LONG_MAX / 10 && str[i] - '0' > 7))
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		output = output * 10 + (str[i++] - '0');
	}
	return ((int)output * sign);
}
