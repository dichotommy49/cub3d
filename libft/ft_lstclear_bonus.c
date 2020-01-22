/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/12 16:13:07 by tmelvin           #+#    #+#             */
/*   Updated: 2019/10/22 16:54:30 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = NULL;
	if (!lst || !del)
		return ;
	if (*lst)
		ptr = *lst;
	while (ptr)
	{
		tmp = ptr;
		ptr = ptr->next;
		if (del)
			ft_lstdelone(tmp, del);
	}
	*lst = NULL;
}
