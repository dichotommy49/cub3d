/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:21:25 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/20 13:21:40 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textured_raycaster.h"

int				key_press_hook(int keycode, param_t *p)
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
		double old_dir_x = p->player.dir.x;
		p->player.dir.x = p->player.dir.x * cos(p->player.rot_speed) - p->player.dir.y * sin(p->player.rot_speed);
		p->player.dir.y = old_dir_x * sin(p->player.rot_speed) + p->player.dir.y * cos(p->player.rot_speed);
		double old_plane_x = p->cam_plane.x;
		p->cam_plane.x = p->cam_plane.x * cos(p->player.rot_speed) - p->cam_plane.y * sin(p->player.rot_speed);
		p->cam_plane.y = old_plane_x * sin(p->player.rot_speed) + p->cam_plane.y * cos(p->player.rot_speed);
	}
	if (keycode == 2)
	{
		double old_dir_x = p->player.dir.x;
		p->player.dir.x = p->player.dir.x * cos(-p->player.rot_speed) - p->player.dir.y * sin(-p->player.rot_speed);
		p->player.dir.y = old_dir_x * sin(-p->player.rot_speed) + p->player.dir.y * cos(-p->player.rot_speed);
		double old_plane_x = p->cam_plane.x;
		p->cam_plane.x = p->cam_plane.x * cos(-p->player.rot_speed) - p->cam_plane.y * sin(-p->player.rot_speed);
		p->cam_plane.y = old_plane_x * sin(-p->player.rot_speed) + p->cam_plane.y * cos(-p->player.rot_speed);
	}
	if (keycode == 126)
	{
		p->player.dir = vector_scale(p->player.dir, 1.1);
	}
	if (keycode == 125)
	{
		p->player.dir = vector_scale(p->player.dir, 0.9);
	}
	if (keycode == 123)
	{	
		p->cam_plane = vector_scale(p->cam_plane, 0.9);
	}
	if (keycode == 124)
	{
		p->cam_plane = vector_scale(p->cam_plane, 1.1);
	}
	return (0);
}

int				key_release_hook(int keycode, param_t *p)
{
	(void)keycode;
	(void)p;
	return (0);
}

int				loop_hook(param_t *p)
{
	draw_screen(p);
	return (0);
}

int				main(void)
{
	param_t		p;

	if (!(p.mlx_ptr = mlx_init()))
		return (1);
	if (!(p.win_ptr = mlx_new_window(p.mlx_ptr, RES_W, RES_H, "Textured Raycaster")))
		return (1);
	var_init(&p);
	mlx_hook(p.win_ptr, 2, (1L<<0), key_press_hook, &p);
	mlx_hook(p.win_ptr, 3, (1L<<1), key_release_hook, &p);
	mlx_loop_hook(p.mlx_ptr, loop_hook, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
