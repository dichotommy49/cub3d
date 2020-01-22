/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:00:11 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/27 15:43:54 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*uch_s1;
	const unsigned char	*uch_s2;

	uch_s1 = s1;
	uch_s2 = s2;
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (n--)
	{
		if (*uch_s1 != *uch_s2)
			return (*uch_s1 - *uch_s2);
		uch_s1++;
		uch_s2++;
	}
	return (0);
}
