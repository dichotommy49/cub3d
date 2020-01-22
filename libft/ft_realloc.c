/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:40:31 by tmelvin           #+#    #+#             */
/*   Updated: 2019/11/22 13:59:38 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t current_size, size_t new_size)
{
	void	*tmp;

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (!ptr)
		return (malloc(new_size));
	if (!(tmp = malloc(new_size)))
	{
		free(ptr);
		return (NULL);
	}
	if (new_size > current_size)
		ft_memcpy(tmp, ptr, current_size);
	else
		ft_memcpy(tmp, ptr, new_size);
	free(ptr);
	return (tmp);
}
