/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:42:00 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/10 15:50:05 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

typedef struct img_s
{
	void        *img;
	char        *addr;
	int         bpp;
	int         line_length;
	int         endian;
}               img_t;

void	my_mlx_pixel_put(img_t img, int x, int y, int color);

#endif
