/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:02:24 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/27 15:35:06 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*ch_dst;
	const char		*ch_src;
	unsigned char	uc;

	ch_dst = dst;
	ch_src = src;
	uc = (unsigned char)c;
	if (dst == NULL || src == NULL)
		return (NULL);
	while (n--)
	{
		*ch_dst++ = *ch_src++;
		if (*(ch_dst - 1) == uc)
			return ((void *)ch_dst);
	}
	return (NULL);
}
