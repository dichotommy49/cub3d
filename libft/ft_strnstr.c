/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 12:40:21 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/27 15:53:44 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int		i;
	size_t	needle_len;

	i = 0;
	if (haystack == NULL || needle == NULL)
		return (NULL);
	needle_len = ft_strlen(needle);
	if (needle_len == 0)
		return ((char *)haystack);
	if (len == 0)
		return (NULL);
	while (i++ <= (int)(len - needle_len))
	{
		if (*haystack == *needle &&
				(0 == ft_strncmp(haystack, needle, needle_len)))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
