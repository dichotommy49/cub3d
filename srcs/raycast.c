/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:01:52 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/22 15:43:09 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int		starting_map[RES_W][RES_H] = {
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,7,7,7,7,7,7,7,7},
	{4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7},
	{4,0,3,0,0,0,0,0,0,0,0,0,0,0,0,0,7,0,0,0,0,0,0,7},
	{4,0,4,0,0,0,0,5,5,5,5,5,5,5,5,5,7,7,0,7,7,7,7,7},
	{4,0,5,0,0,0,0,5,0,5,0,5,0,5,0,5,7,0,0,0,7,7,7,1},
	{4,0,6,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,7,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,7,7,7,1},
	{4,0,8,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,0,0,0,8},
	{4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5,7,0,0,0,7,7,7,1},
	{4,0,0,0,0,0,0,5,5,5,5,0,5,5,5,5,7,7,7,7,7,7,7,1},
	{6,6,6,6,6,6,6,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4},
	{6,6,6,6,6,6,0,6,6,6,6,0,6,6,6,6,6,6,6,6,6,6,6,6},
	{4,4,4,4,4,4,0,4,4,4,6,0,6,2,2,2,2,2,2,2,3,3,3,3},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,0,0,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,0,0,0,0,5,0,0,0,0,0,0,2},
	{4,0,0,5,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,2,0,2,2},
	{4,0,6,0,6,0,0,0,0,4,6,0,6,2,0,0,5,0,0,2,0,0,0,2},
	{4,0,0,0,0,0,0,0,0,4,6,0,6,2,0,0,0,0,0,2,0,0,0,2},
	{4,4,4,4,4,4,4,4,4,4,1,1,1,2,2,2,2,2,2,3,3,3,3,3}
	};

void	var_init(t_param *p)
{
	p->player.pos.x = 22, p->player.pos.y = 11.5;
	p->player.dir.x = -1.0, p->player.dir.y = 0.0;
	p->cam_plane.x = 0.0, p->cam_plane.y = 0.66;
//	clock_gettime(CLOCK_REALTIME, &p->time);
	p->current_screen = 1;
	p->screen1.img = mlx_new_image(p->mlx_ptr, RES_W, RES_H);
	p->screen1.addr = mlx_get_data_addr(p->screen1.img, &p->screen1.bpp, &p->screen1.line_length, &p->screen1.endian);
	p->screen2.img = mlx_new_image(p->mlx_ptr, RES_W, RES_H);
	p->screen2.addr = mlx_get_data_addr(p->screen2.img, &p->screen2.bpp, &p->screen2.line_length, &p->screen2.endian);
	p->floor_color = 0xffffff;
	p->ceiling_color = 0x000000;

	//generate textures
	int x = 0;
	int y;
	while (x < TEX_W)
	{
		y = 0;
		while (y < TEX_H)
		{
			int	xorcolor = (x * 256 / TEX_W) ^ (y * 256 / TEX_H);
			//int xcolor = x * 256 / TEX_W;
			int	ycolor = y * 256 / TEX_H;
			int	xycolor = y * 128 / TEX_H + x * 128 / TEX_W;
			p->texture[0][TEX_W * y + x] = 65536 * 254 * (x != y && x != TEX_W - y);
			p->texture[1][TEX_W * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;
			p->texture[2][TEX_W * y + x] = 256 * xycolor + 65536 * xycolor;
			p->texture[3][TEX_W * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor;
			p->texture[4][TEX_W * y + x] = 256 * xorcolor;
			p->texture[5][TEX_W * y + x] = 65536 * 192 * (x % 16 && y % 16);
			p->texture[6][TEX_W * y + x] = 65536 * ycolor;
			p->texture[7][TEX_W * y + x] = 128 + 256 * 128 + 65536 * 128;
			y++;
		}
		x++;
	}
	x = 0;
	while (x < MAP_W)
	{
		y = 0;
		while (y < MAP_H)
		{
			p->world_map[x][y] = starting_map[x][y];
			y++;
		}
		x++;
	}
	p->player.move_speed = 0.5;
	p->player.rot_speed = 0.1;
}

void	draw_screen(t_param *p)
{
	int y;
	int x = -1;
	while (++x < RES_W)
	{
		double camera_x = 2 * x / (double)RES_W - 1;
		double ray_dir_x = p->player.dir.x + p->cam_plane.x * camera_x;
		double ray_dir_y = p->player.dir.y + p->cam_plane.y * camera_x;
		int	map_x = (int)p->player.pos.x;
		int map_y = (int)p->player.pos.y;
		double	side_dist_x;
		double	side_dist_y;
		double	delta_dist_x = fabs(1 / ray_dir_x);
		double	delta_dist_y = fabs(1 / ray_dir_y);
		double perp_wall_dist;
		int	step_x;
		int	step_y;
		int	hit = 0;
		int side;
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (p->player.pos.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - p->player.pos.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (p->player.pos.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - p->player.pos.y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (p->world_map[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - p->player.pos.x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - p->player.pos.y + (1 - step_y) / 2) / ray_dir_y;
		int line_height = (int)(RES_H / perp_wall_dist);
		int draw_start = -line_height / 2 + RES_H / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + RES_H / 2;
		if (draw_end >= RES_H)
			draw_end = RES_H - 1;
		//texturing calculations
		int	tex_num = p->world_map[map_x][map_y] - 1;

		//calculate value of wall_x
		double	wall_x;
		if (side == 0)
			wall_x = p->player.pos.y + perp_wall_dist * ray_dir_y;
		else
			wall_x = p->player.pos.x + perp_wall_dist * ray_dir_x;
		wall_x -= floor((wall_x));

		//x coordinate on the texture
		int	tex_x = (int)(wall_x * (double)TEX_W);
		if (side == 0 && ray_dir_x > 0)
			tex_x = TEX_W - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = TEX_W - tex_x - 1;
		
		//how much to increase the texture coordinate per screen pixel
		double	step = 1.0 * TEX_H / line_height;
		//starting texture coordinate
		double	tex_pos = (draw_start - RES_H / 2 + line_height / 2) * step;
		//start drawing screen
		y = 0;
		while (y < draw_start)
		{
			if (p->current_screen == 1)
				my_mlx_pixel_put(p->screen2, x, y, p->ceiling_color);
			else
				my_mlx_pixel_put(p->screen1, x, y, p->ceiling_color);
			y++;
		}
		while (y < draw_end)
		{
			//cast the texture coordinate to integer
			int	tex_y = (int)tex_pos & (TEX_H - 1);
			tex_pos += step;
			int	color = p->texture[tex_num][TEX_H * tex_y + tex_x];
			//make color darker for y-sides: R, G, and B byte each divided through two with a bitshift and bitwise and
			if (side == 1)
				color = (color >> 1) & 8355711;
			if (p->current_screen == 1)
				my_mlx_pixel_put(p->screen2, x, y, color);
			else
				my_mlx_pixel_put(p->screen1, x, y, color);
			y++;
		}
		while (y < RES_H)
		{
			if (p->current_screen == 1)
				my_mlx_pixel_put(p->screen2, x, y, p->floor_color);
			else
				my_mlx_pixel_put(p->screen1, x, y, p->floor_color);
			y++;
		}
	}
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
//	p->old_time = p->time;
//	clock_gettime(CLOCK_REALTIME, &p->time);
//	double	frame_time = (p->time.tv_sec - p->old_time.tv_sec) + (p->time.tv_nsec - p->old_time.tv_nsec)/1000000000;
//	frame_time = frame_time / 1000.0;
//	printf("%f\n", 1.0 / frame_time);
//	p->player.move_speed = frame_time * 5.0;
//	p->player.rot_speed = frame_time * 3.0;
}
