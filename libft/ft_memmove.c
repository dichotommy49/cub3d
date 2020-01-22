/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:39:03 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/27 15:38:38 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*ch_dst;
	const char	*ch_src;

	ch_dst = dst;
	ch_src = src;
	if (dst == NULL || src == NULL)
		return (NULL);
	if (ch_dst < ch_src)
		while (len--)
			*ch_dst++ = *ch_src++;
	else
	{
		ch_dst += len - 1;
		ch_src += len - 1;
		while (len--)
			*ch_dst-- = *ch_src--;
	}
	return (dst);
}
