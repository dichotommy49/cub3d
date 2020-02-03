/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:07:37 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/03 12:50:11 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int				key_press_hook(int keycode, t_param *p)
{
	if (keycode == 13)
	{
		p->keys.w = 1;
	}
	if (keycode == 1)
	{
		p->keys.s = 1;
	}
	if (keycode == 0)
	{
		p->keys.a = 1;
	}
	if (keycode == 2)
	{
		p->keys.d = 1;
	}
	if (keycode == 123)
	{
		p->keys.left_arrow = 1;
	}
	if (keycode == 124)
	{
		p->keys.right_arrow = 1;
	}
	if (keycode == 53)
		exit_cub3d(p);
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
//	clock_gettime(CLOCK_REALTIME, &p->time);
	update(p);
	draw(p);
//	p->old_time = p->time;
//	clock_gettime(CLOCK_REALTIME, &p->time);
//	double	frame_time = (p->time.tv_sec - p->old_time.tv_sec) + (p->time.tv_nsec - p->old_time.tv_nsec)/1000000000;
//	frame_time = frame_time / 1000.0;
//	printf("%f\n", 1.0 / frame_time);
//	p->player.move_speed = frame_time * 5.0;
//	p->player.rot_speed = frame_time * 3.0;
	return (0);
}
