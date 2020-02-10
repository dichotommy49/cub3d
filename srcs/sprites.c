/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:05:05 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/10 12:42:19 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	sort_sprites(int *order, double *distance, t_param *p)
{
	int		i;
	int		j;
	int		swap_int;
	double	swap_double;

	i = 0;
	while (i < p->num_sprites - 1)
	{
		j = 0;
		while (j < p->num_sprites - i - 1)
		{
			if (distance[j] < distance[j + 1])
			{
				swap_int = order[j];
				swap_double = distance[j];
				order[j] = order[j + 1];
				distance[j] = distance[j + 1];
				order[j + 1] = swap_int;
				distance[j + 1] = swap_double;
			}
			j++;
		}
		i++;
	}
}

void	sprite_drawing_calculations(t_param *p, t_sprite_info *sprite)
{
	sprite->inv_det = 1.0 / (p->cam_plane.x * p->player.dir.y -
			p->player.dir.x * p->cam_plane.y);
	sprite->transform.x = sprite->inv_det * (p->player.dir.y *
			sprite->pos.x - p->player.dir.x * sprite->pos.y);
	sprite->transform.y = sprite->inv_det * (-p->cam_plane.y *
			sprite->pos.x + p->cam_plane.x * sprite->pos.y);
	sprite->screen.x = (int)((p->res_w / 2) *
			(1 + sprite->transform.x / sprite->transform.y));
	sprite->height = abs((int)(p->res_h / sprite->transform.y));
	sprite->draw_start.y = -sprite->height / 2 + p->res_h / 2;
	if (sprite->draw_start.y < 0)
		sprite->draw_start.y = 0;
	sprite->draw_end.y = sprite->height / 2 + p->res_h / 2;
	if (sprite->draw_end.y >= p->res_h)
		sprite->draw_end.y = p->res_h - 1;
	sprite->width = abs((int)(p->res_h / sprite->transform.y));
	sprite->draw_start.x = -sprite->width / 2 + sprite->screen.x;
	if (sprite->draw_start.x < 0)
		sprite->draw_start.x = 0;
	sprite->draw_end.x = sprite->width / 2 + sprite->screen.x;
	if (sprite->draw_end.x >= p->res_w)
		sprite->draw_end.x = p->res_w - 1;
}

void	draw_vertical_stripe(t_param *p, t_sprite_info *sprite, int stripe)
{
	int				y;
	int				tex_x;
	int				tex_y;
	int				d;
	unsigned int	color;

	tex_x = ((int)(256 * (stripe - (-sprite->width / 2 + sprite->screen.x)) *
				p->map_info.tex_w / sprite->width)) / 256;
	if (sprite->transform.y > 0 && stripe > 0 && stripe < p->res_w &&
			sprite->transform.y < p->zbuffer[stripe])
	{
		y = sprite->draw_start.y;
		while (y < sprite->draw_end.y)
		{
			d = (y) * 256 - p->res_h * 128 + sprite->height * 128;
			tex_y = ((d * p->map_info.tex_h) / sprite->height) / 256;
			color = my_mlx_pixel_get(p->texture[4], tex_x, tex_y);
			if ((color & 0x00FFFFFF) != 0)
			{
				my_mlx_pixel_put(p, stripe, y, color);
			}
			y++;
		}
	}
}

void	draw_individual_sprite(t_param *p, int *sprite_order, int i)
{
	t_sprite_info	sprite;
	int				stripe;

	sprite.pos.x = p->sprites[sprite_order[i]].x - p->player.pos.x;
	sprite.pos.y = p->sprites[sprite_order[i]].y - p->player.pos.y;
	sprite_drawing_calculations(p, &sprite);
	stripe = sprite.draw_start.x;
	while (stripe < sprite.draw_end.x)
	{
		draw_vertical_stripe(p, &sprite, stripe);
		stripe++;
	}
}

void	draw_sprites(t_param *p)
{
	int		i;
	int		sprite_order[p->num_sprites];
	double	sprite_distance[p->num_sprites];

	i = 0;
	while (i < p->num_sprites)
	{
		sprite_order[i] = i;
		sprite_distance[i] = (pow(p->player.pos.x - p->sprites[i].x, 2) +
				pow(p->player.pos.y - p->sprites[i].y, 2));
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, p);
	i = 0;
	while (i < p->num_sprites)
	{
		draw_individual_sprite(p, sprite_order, i);
		i++;
	}
}
