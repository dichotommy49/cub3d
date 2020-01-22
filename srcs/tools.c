/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:11:07 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/22 15:43:13 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	cub3d_atoi(char **str)
{
	int	r;
	int	sign;

	sign = 1;
	r = 0;
	while (**str == ' ')
		*str = *str + 1;
	if (**str == '-')
	{
		sign = -1;
		*str = *str + 1;
	}
	while (ft_isdigit(**str))
	{
		r = r * 10 + **str - 48;
		*str = *str + 1;
	}
	return (r * sign);
}

unsigned int	cub3d_atoui(char **str)
{
	unsigned int	r;

	r = 0;
	while (**str == ' ')
		*str = *str + 1;
	while (ft_isdigit(**str))
	{
		r = r * 10 + **str - 48;
		*str = *str + 1;
	}
	return (r);
}

char	*cub3d_strjoin(char *s1, char *s2)
{
	char	*output;
	int		i;
	int		j;

	if (!(output = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		output[i + j] = s2[j];
		j++;
	}
	output[i + j] = 0;
	free(s1);
	return (output);
}
