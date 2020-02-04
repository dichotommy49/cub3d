/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:55:42 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/03 10:42:21 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		reset_keys(t_param *p)
{
	p->keys.up_arrow = 0;
	p->keys.down_arrow = 0;
	p->keys.left_arrow = 0;
	p->keys.right_arrow = 0;
	p->keys.w = 0;
	p->keys.a = 0;
	p->keys.s = 0;
	p->keys.d = 0;
	p->keys.space = 0;
}

void		update_player(t_param *p)
{
	if (p->keys.w)
	{
		if (!p->map_info.level_map[(int)(p->player.pos.x + p->player.dir.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x += p->player.dir.x * p->player.move_speed;
		if (!p->map_info.level_map[(int)p->player.pos.x][(int)(p->player.pos.y + p->player.dir.y * p->player.move_speed)])
			p->player.pos.y += p->player.dir.y * p->player.move_speed;
	}
	if (p->keys.s)
	{
		if (!p->map_info.level_map[(int)(p->player.pos.x - p->player.dir.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x -= p->player.dir.x * p->player.move_speed;
		if (!p->map_info.level_map[(int)p->player.pos.x][(int)(p->player.pos.y - p->player.dir.y * p->player.move_speed)])
			p->player.pos.y -= p->player.dir.y * p->player.move_speed;
	}
	if (p->keys.a)
	{
		if (!p->map_info.level_map[(int)(p->player.pos.x - p->cam_plane.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x -= p->cam_plane.x * p->player.move_speed;
		if (!p->map_info.level_map[(int)p->player.pos.x][(int)(p->player.pos.y - p->cam_plane.y * p->player.move_speed)])
			p->player.pos.y -= p->cam_plane.y * p->player.move_speed;
	}
	if (p->keys.d)
	{
		if (!p->map_info.level_map[(int)(p->player.pos.x + p->cam_plane.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x += p->cam_plane.x * p->player.move_speed;
		if (!p->map_info.level_map[(int)p->player.pos.x][(int)(p->player.pos.y + p->cam_plane.y * p->player.move_speed)])
			p->player.pos.y += p->cam_plane.y * p->player.move_speed;
	}
	if (p->keys.left_arrow)
	{
		double old_dir_x = p->player.dir.x;
		p->player.dir.x = p->player.dir.x * cos(p->player.rot_speed) - p->player.dir.y * sin(p->player.rot_speed);
		p->player.dir.y = old_dir_x * sin(p->player.rot_speed) + p->player.dir.y * cos(p->player.rot_speed);
		double old_plane_x = p->cam_plane.x;
		p->cam_plane.x = p->cam_plane.x * cos(p->player.rot_speed) - p->cam_plane.y * sin(p->player.rot_speed);
		p->cam_plane.y = old_plane_x * sin(p->player.rot_speed) + p->cam_plane.y * cos(p->player.rot_speed);
	}
	if (p->keys.right_arrow)
	{
		double old_dir_x = p->player.dir.x;
		p->player.dir.x = p->player.dir.x * cos(-p->player.rot_speed) - p->player.dir.y * sin(-p->player.rot_speed);
		p->player.dir.y = old_dir_x * sin(-p->player.rot_speed) + p->player.dir.y * cos(-p->player.rot_speed);
		double old_plane_x = p->cam_plane.x;
		p->cam_plane.x = p->cam_plane.x * cos(-p->player.rot_speed) - p->cam_plane.y * sin(-p->player.rot_speed);
		p->cam_plane.y = old_plane_x * sin(-p->player.rot_speed) + p->cam_plane.y * cos(-p->player.rot_speed);
	}
}

void		draw_screen(t_param *p)
{
	if (p->current_screen == 1)
	{
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->screen2.img, 0, 0);
		p->current_screen = 2;
	}
	else
	{
		mlx_put_image_to_window(p->mlx_ptr, p->win_ptr, p->screen1.img, 0, 0);
		p->current_screen = 1;
	}
}

void		update(t_param *p)
{
	update_player(p);
	reset_keys(p);
}

void		draw(t_param *p)
{
	draw_world(p);
	draw_sprites(p);
	draw_screen(p);
}