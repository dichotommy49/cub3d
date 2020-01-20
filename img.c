/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:39:50 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/20 15:18:10 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "img.h"

void            my_mlx_pixel_put(t_img img, int x, int y, int color)
{
	char    *dst;

	dst = img.addr + (y * img.line_length + x * (img.bpp / 8));
	*(unsigned int*)dst = color;
}
