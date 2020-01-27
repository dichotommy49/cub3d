/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:39:50 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/27 15:30:54 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/img.h"

void            my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char    *dst;

	dst = img.addr + (y * img.line_length + x * (img.bpp / 8));
	*(unsigned int *)dst = color;
}

unsigned int	my_mlx_pixel_get(t_img img, int x, int y)
{
	unsigned int	color;
	char			*ptr;

	ptr = img.addr + (y * img.line_length + x * (img.bpp / 8));
	color = *(unsigned int *)ptr;
	return (color);
}
