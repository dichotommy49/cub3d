/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:07:37 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/22 15:43:49 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				key_press_hook(int keycode, t_param *p)
{
	if (keycode == 13)
	{
		if (!p->world_map[(int)(p->player.pos.x + p->player.dir.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x += p->player.dir.x * p->player.move_speed;
		if (!p->world_map[(int)p->player.pos.x][(int)(p->player.pos.y + p->player.dir.y * p->player.move_speed)])
			p->player.pos.y += p->player.dir.y * p->player.move_speed;
	}
	if (keycode == 1)
	{
		if (!p->world_map[(int)(p->player.pos.x - p->player.dir.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x -= p->player.dir.x * p->player.move_speed;
		if (!p->world_map[(int)p->player.pos.x][(int)(p->player.pos.y - p->player.dir.y * p->player.move_speed)])
			p->player.pos.y -= p->player.dir.y * p->player.move_speed;
	}
	if (keycode == 0)
	{
		if (!p->world_map[(int)(p->player.pos.x - p->cam_plane.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x -= p->cam_plane.x * p->player.move_speed;
		if (!p->world_map[(int)p->player.pos.x][(int)(p->player.pos.y - p->cam_plane.y * p->player.move_speed)])
			p->player.pos.y -= p->cam_plane.y * p->player.move_speed;
	}
	if (keycode == 2)
	{
		if (!p->world_map[(int)(p->player.pos.x + p->cam_plane.x * p->player.move_speed)][(int)p->player.pos.y])
			p->player.pos.x += p->cam_plane.x * p->player.move_speed;
		if (!p->world_map[(int)p->player.pos.x][(int)(p->player.pos.y + p->cam_plane.y * p->player.move_speed)])
			p->player.pos.y += p->cam_plane.y * p->player.move_speed;
	}
	if (keycode == 123)
	{
		double old_dir_x = p->player.dir.x;
		p->player.dir.x = p->player.dir.x * cos(p->player.rot_speed) - p->player.dir.y * sin(p->player.rot_speed);
		p->player.dir.y = old_dir_x * sin(p->player.rot_speed) + p->player.dir.y * cos(p->player.rot_speed);
		double old_plane_x = p->cam_plane.x;
		p->cam_plane.x = p->cam_plane.x * cos(p->player.rot_speed) - p->cam_plane.y * sin(p->player.rot_speed);
		p->cam_plane.y = old_plane_x * sin(p->player.rot_speed) + p->cam_plane.y * cos(p->player.rot_speed);
	}
	if (keycode == 124)
	{
		double old_dir_x = p->player.dir.x;
		p->player.dir.x = p->player.dir.x * cos(-p->player.rot_speed) - p->player.dir.y * sin(-p->player.rot_speed);
		p->player.dir.y = old_dir_x * sin(-p->player.rot_speed) + p->player.dir.y * cos(-p->player.rot_speed);
		double old_plane_x = p->cam_plane.x;
		p->cam_plane.x = p->cam_plane.x * cos(-p->player.rot_speed) - p->cam_plane.y * sin(-p->player.rot_speed);
		p->cam_plane.y = old_plane_x * sin(-p->player.rot_speed) + p->cam_plane.y * cos(-p->player.rot_speed);
	}
	return (0);
}

int				key_release_hook(int keycode, t_param *p)
{
	(void)keycode;
	(void)p;
	return (0);
}

int				loop_hook(t_param *p)
{
	draw_screen(p);
	return (0);
}
