/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 15:45:56 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/27 15:39:03 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char		*uch_s;

	uch_s = s;
	if (s == NULL)
		return (NULL);
	while (n--)
	{
		if (*uch_s == (unsigned char)c)
			return ((void *)uch_s);
		uch_s++;
	}
	return (NULL);
}
