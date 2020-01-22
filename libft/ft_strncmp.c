/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:52:28 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/27 16:41:22 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	uc1;
	unsigned char	uc2;

	if (s1 == NULL || s2 == NULL)
		return (0);
	while (n && *s1 && *s2)
	{
		uc1 = (unsigned char)*s1++;
		uc2 = (unsigned char)*s2++;
		if (uc1 != uc2)
			return (uc1 - uc2);
		n--;
	}
	if (n != 0)
		return ((unsigned char)*s1 - (unsigned char)*s2);
	return (0);
}
