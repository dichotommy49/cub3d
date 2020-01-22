/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:02:42 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/30 16:16:14 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*ch_dst;
	const char	*ch_src;

	ch_dst = dst;
	ch_src = src;
	if (dst == NULL || src == NULL)
		return (dst);
	while (n--)
		*ch_dst++ = *ch_src++;
	return (dst);
}
