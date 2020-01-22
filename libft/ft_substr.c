/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:29:56 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/21 12:11:57 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	i;

	if (!(output = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	if (s && start < (unsigned int)ft_strlen(s))
	{
		i = 0;
		while (s[start + i] && i < len)
		{
			output[i] = s[start + i];
			i++;
		}
		output[i] = '\0';
	}
	else
		output[0] = '\0';
	return (output);
}
