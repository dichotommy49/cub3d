/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 15:55:42 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/13 17:44:07 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void		move_forward_back(t_cub3d *p)
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
}

void		move_strafe(t_cub3d *p)
{
	if (p->keys.a)
	{
		if (!p->map_info.level_map[(int)(p->player.pos.x - p->player.cam_plane.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x -= p->player.cam_plane.x * p->player.move_speed;
		if (!p->map_info.level_map[(int)p->player.pos.x][(int)(p->player.pos.y - p->player.cam_plane.y * p->player.move_speed)])
			p->player.pos.y -= p->player.cam_plane.y * p->player.move_speed;
	}
	if (p->keys.d)
	{
		if (!p->map_info.level_map[(int)(p->player.pos.x + p->player.cam_plane.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x += p->player.cam_plane.x * p->player.move_speed;
		if (!p->map_info.level_map[(int)p->player.pos.x][(int)(p->player.pos.y + p->player.cam_plane.y * p->player.move_speed)])
			p->player.pos.y += p->player.cam_plane.y * p->player.move_speed;
	}
}

void		look_left_right(t_cub3d *p)
{
	if (p->keys.left_arrow)
	{
		double old_dir_x = p->player.dir.x;
		p->player.dir.x = p->player.dir.x * cos(p->player.rot_speed) - p->player.dir.y * sin(p->player.rot_speed);
		p->player.dir.y = old_dir_x * sin(p->player.rot_speed) + p->player.dir.y * cos(p->player.rot_speed);
		double old_plane_x = p->player.cam_plane.x;
		p->player.cam_plane.x = p->player.cam_plane.x * cos(p->player.rot_speed) - p->player.cam_plane.y * sin(p->player.rot_speed);
		p->player.cam_plane.y = old_plane_x * sin(p->player.rot_speed) + p->player.cam_plane.y * cos(p->player.rot_speed);
	}
	if (p->keys.right_arrow)
	{
		double old_dir_x = p->player.dir.x;
		p->player.dir.x = p->player.dir.x * cos(-p->player.rot_speed) - p->player.dir.y * sin(-p->player.rot_speed);
		p->player.dir.y = old_dir_x * sin(-p->player.rot_speed) + p->player.dir.y * cos(-p->player.rot_speed);
		double old_plane_x = p->player.cam_plane.x;
		p->player.cam_plane.x = p->player.cam_plane.x * cos(-p->player.rot_speed) - p->player.cam_plane.y * sin(-p->player.rot_speed);
		p->player.cam_plane.y = old_plane_x * sin(-p->player.rot_speed) + p->player.cam_plane.y * cos(-p->player.rot_speed);
	}
}

void		update_player(t_cub3d *p)
{
	move_forward_back(p);
	move_strafe(p);
	look_left_right(p);
}

void		draw_screen(t_cub3d *p)
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

void		update(t_cub3d *p)
{
	update_player(p);
}

void		draw(t_cub3d *p)
{
	draw_world(p);
	draw_sprites(p);
	draw_screen(p);
}
