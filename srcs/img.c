/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:39:50 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/13 16:45:56 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void            my_mlx_pixel_put(t_cub3d *p, int x, int y, int color)
{
	t_img	dst_img;
	char    *dst;

	if (p->current_screen == 1)
		dst_img = p->screen2;
	else
		dst_img = p->screen1;
	dst = dst_img.addr + (y * dst_img.line_length + x * (dst_img.bpp / 8));
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
