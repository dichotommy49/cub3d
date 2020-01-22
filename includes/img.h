/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 15:42:00 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/20 15:17:59 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMG_H
# define IMG_H

typedef struct s_img
{
	void        *img;
	char        *addr;
	int         bpp;
	int         line_length;
	int         endian;
}               t_img;

void	my_mlx_pixel_put(t_img img, int x, int y, int color);

#endif
