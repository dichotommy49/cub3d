/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:01:52 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/03 10:50:58 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	var_init(t_param *p)
{
	if (p->player.dir.x == -1)
		p->cam_plane.x = 0.0, p->cam_plane.y = 0.66;
	else if (p->player.dir.x == 1)
		p->cam_plane.x = 0.0, p->cam_plane.y = -0.66;
	else if (p->player.dir.y == -1)
		p->cam_plane.x = -0.66, p->cam_plane.y = 0;
	else if (p->player.dir.y == 1)
		p->cam_plane.x = 0.66, p->cam_plane.y = 0;
	if (!(p->zbuffer = malloc(sizeof(double) * p->res_w)))
		return ;
//	clock_gettime(CLOCK_REALTIME, &p->time);
	p->current_screen = 1;
	p->screen1.img = mlx_new_image(p->mlx_ptr, p->res_w, p->res_h);
	p->screen1.addr = mlx_get_data_addr(p->screen1.img, &p->screen1.bpp, &p->screen1.line_length, &p->screen1.endian);
	p->screen2.img = mlx_new_image(p->mlx_ptr, p->res_w, p->res_h);
	p->screen2.addr = mlx_get_data_addr(p->screen2.img, &p->screen2.bpp, &p->screen2.line_length, &p->screen2.endian);

	//set textures
	p->texture[0].img = mlx_xpm_file_to_image(p->mlx_ptr, p->map_info.north_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[1].img = mlx_xpm_file_to_image(p->mlx_ptr, p->map_info.south_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[2].img = mlx_xpm_file_to_image(p->mlx_ptr, p->map_info.east_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[3].img = mlx_xpm_file_to_image(p->mlx_ptr, p->map_info.west_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[4].img = mlx_xpm_file_to_image(p->mlx_ptr, p->map_info.sprite_path, &p->map_info.tex_w, &p->map_info.tex_h);
	
	p->texture[0].addr = mlx_get_data_addr(p->texture[0].img, &p->texture[0].bpp, &p->texture[0].line_length, &p->texture[0].endian);
	p->texture[1].addr = mlx_get_data_addr(p->texture[1].img, &p->texture[1].bpp, &p->texture[1].line_length, &p->texture[1].endian);
	p->texture[2].addr = mlx_get_data_addr(p->texture[2].img, &p->texture[2].bpp, &p->texture[2].line_length, &p->texture[2].endian);
	p->texture[3].addr = mlx_get_data_addr(p->texture[3].img, &p->texture[3].bpp, &p->texture[3].line_length, &p->texture[3].endian);
	p->texture[4].addr = mlx_get_data_addr(p->texture[4].img, &p->texture[4].bpp, &p->texture[4].line_length, &p->texture[4].endian);

	p->player.move_speed = 0.5;
	p->player.rot_speed = 0.1;
}

void	sort_sprites(int *order, double *distance, t_param *p)
{
	int	i;
	int	j;
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

void	draw_sprites(t_param *p)
{
	int		i;
	int		sprite_order[p->num_sprites];
	double	sprite_distance[p->num_sprites];

	i = 0;
	while (	i < p->num_sprites)
	{
		sprite_order[i] = i;
		sprite_distance[i] = ((p->player.pos.x - p->sprites[i].x) * (p->player.pos.x - p->sprites[i].x) + (p->player.pos.y - p->sprites[i].y) * (p->player.pos.y - p->sprites[i].y));
		i++;
	}
	sort_sprites(sprite_order, sprite_distance, p);
	i = 0;
	while (i < p->num_sprites)
	{
		double	sprite_x = p->sprites[sprite_order[i]].x - p->player.pos.x;
		double	sprite_y = p->sprites[sprite_order[i]].y - p->player.pos.y;
		double	inv_det = 1.0 / (p->cam_plane.x * p->player.dir.y - p->player.dir.x * p->cam_plane.y);
		double	transform_x = inv_det * (p->player.dir.y * sprite_x - p->player.dir.x * sprite_y);
		double	transform_y = inv_det * (-p->cam_plane.y * sprite_x + p->cam_plane.x * sprite_y);
		int		sprite_screen_x = (int)((p->res_w / 2) * (1 + transform_x / transform_y));

		//calculate the height of the sprite on screen
		int		sprite_height = abs((int)(p->res_h / transform_y));
		//calculate lowest and highest pixel to fill in current stripe
		int		draw_start_y = -sprite_height / 2 + p->res_h / 2;
		if (draw_start_y < 0)
			draw_start_y = 0;
		int		draw_end_y = sprite_height / 2 + p->res_h / 2;
		if (draw_end_y >= p->res_h)
			draw_end_y = p->res_h - 1;

		//calculate width of the sprite
		int	sprite_width = abs((int)(p->res_h / transform_y));
		int	draw_start_x = -sprite_width / 2 + sprite_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		int	draw_end_x = sprite_width / 2 + sprite_screen_x;
		if (draw_end_x >= p->res_w)
			draw_end_x = p->res_w - 1;

		//loop through every vertical stripe of the sprite on screen
		int	stripe = draw_start_x;
		while (stripe < draw_end_x)
		{
			int tex_x = ((int)(256 * (stripe - (-sprite_width / 2 + sprite_screen_x)) * p->map_info.tex_w / sprite_width)) / 256;
			if (transform_y > 0 && stripe > 0 && stripe < p->res_w && transform_y < p->zbuffer[stripe])
			{
				int y = draw_start_y;
				while (y < draw_end_y)
				{
					int d = (y) * 256 - p->res_h * 128 + sprite_height * 128;
					int tex_y = ((d * p->map_info.tex_h) / sprite_height) / 256;
					unsigned int color = my_mlx_pixel_get(p->texture[4], tex_x, tex_y);
					if ((color & 0x00FFFFFF) != 0)
					{
						my_mlx_pixel_put(p, stripe, y, color);
					}
					y++;
				}
			}
			stripe++;
		}
		i++;
	}

}

void	draw_world(t_param *p)
{
	int y;
	int x = -1;
	while (++x < p->res_w)
	{
		double camera_x = 2 * x / (double)p->res_w - 1;
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
			if (p->map_info.level_map[map_x][map_y] == 1)
				hit = 1;
		}
		if (side == 0)
			perp_wall_dist = (map_x - p->player.pos.x + (1 - step_x) / 2) / ray_dir_x;
		else
			perp_wall_dist = (map_y - p->player.pos.y + (1 - step_y) / 2) / ray_dir_y;
		int line_height = (int)(p->res_h / perp_wall_dist);
		int draw_start = -line_height / 2 + p->res_h / 2;
		if (draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + p->res_h / 2;
		if (draw_end >= p->res_h)
			draw_end = p->res_h - 1;
		//texturing calculations
		int	tex_num;
		if (side == 1 && ray_dir_y > 0)
			tex_num = 0;
		else if (side == 1 && ray_dir_y < 0)
			tex_num = 1;
		else if (side == 0 && ray_dir_x > 0)
			tex_num = 2;
		else if (side == 0 && ray_dir_x < 0)
			tex_num = 3;

		//calculate value of wall_x
		double	wall_x;
		if (side == 0)
			wall_x = p->player.pos.y + perp_wall_dist * ray_dir_y;
		else
			wall_x = p->player.pos.x + perp_wall_dist * ray_dir_x;
		wall_x -= floor((wall_x));

		//x coordinate on the texture
		int	tex_x = (int)(wall_x * (double)p->map_info.tex_w);
		if (side == 0 && ray_dir_x > 0)
			tex_x = p->map_info.tex_w - tex_x - 1;
		if (side == 1 && ray_dir_y < 0)
			tex_x = p->map_info.tex_w - tex_x - 1;
		
		//how much to increase the texture coordinate per screen pixel
		double	step = 1.0 * p->map_info.tex_h / line_height;
		//starting texture coordinate
		double	tex_pos = (draw_start - p->res_h / 2 + line_height / 2) * step;
		//start drawing screen
		y = 0;
		while (y < draw_start)
		{
			my_mlx_pixel_put(p, x, y, p->map_info.ceiling_color);
			y++;
		}
		while (y < draw_end)
		{
			//cast the texture coordinate to integer
			int	tex_y = (int)tex_pos & (p->map_info.tex_h - 1);
			tex_pos += step;
			unsigned int color = my_mlx_pixel_get(p->texture[tex_num], tex_x, tex_y);
			if (side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(p, x, y, color);
			y++;
		}
		while (y < p->res_h)
		{
			my_mlx_pixel_put(p, x, y, p->map_info.floor_color);
			y++;
		}
		p->zbuffer[x] = perp_wall_dist;
	}
}
