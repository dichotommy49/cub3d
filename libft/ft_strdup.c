/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:11:22 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/27 16:33:30 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;
	char	*ptr;

	if (s1 == NULL)
		return (NULL);
	if (!(copy = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	ptr = copy;
	while (*s1)
		*ptr++ = *s1++;
	*ptr = '\0';
	return (copy);
}
