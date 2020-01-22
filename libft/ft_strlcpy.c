/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:40:50 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/30 16:17:56 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	ret;

	if (dst == NULL || src == NULL)
		return (0);
	ret = ft_strlen(src);
	src_len = ret;
	if (size == 0)
		return (ret);
	if (src_len + 1 > size)
		src_len = size - 1;
	ft_memcpy(dst, src, src_len);
	dst[src_len] = '\0';
	return (ret);
}
