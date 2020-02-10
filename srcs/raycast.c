/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:01:52 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/10 13:27:37 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	init_textures(t_param *p)
{
	p->texture[0].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.north_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[1].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.south_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[2].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.east_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[3].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.west_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[4].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.sprite_path, &p->map_info.tex_w, &p->map_info.tex_h);

	p->texture[0].addr = mlx_get_data_addr(p->texture[0].img, &p->texture[0].bpp
			, &p->texture[0].line_length, &p->texture[0].endian);
	p->texture[1].addr = mlx_get_data_addr(p->texture[1].img, &p->texture[1].bpp
			, &p->texture[1].line_length, &p->texture[1].endian);
	p->texture[2].addr = mlx_get_data_addr(p->texture[2].img, &p->texture[2].bpp
			, &p->texture[2].line_length, &p->texture[2].endian);
	p->texture[3].addr = mlx_get_data_addr(p->texture[3].img, &p->texture[3].bpp
			, &p->texture[3].line_length, &p->texture[3].endian);
	p->texture[4].addr = mlx_get_data_addr(p->texture[4].img, &p->texture[4].bpp
			, &p->texture[4].line_length, &p->texture[4].endian);
}

void	raycast_calculations(t_param *p, t_raycast_info *i)
{
	int		hit;

	i->map_x = (int)p->player.pos.x;
	i->map_y = (int)p->player.pos.y;
	i->delta_dist.x = fabs(1 / i->ray_dir.x);
	i->delta_dist.y = fabs(1 / i->ray_dir.y);
	hit = 0;
	if (i->ray_dir.x < 0)
	{
		i->step_x = -1;
		i->side_dist.x = (p->player.pos.x - i->map_x) * i->delta_dist.x;
	}
	else
	{
		i->step_x = 1;
		i->side_dist.x = (i->map_x + 1.0 - p->player.pos.x) * i->delta_dist.x;
	}
	if (i->ray_dir.y < 0)
	{
		i->step_y = -1;
		i->side_dist.y = (p->player.pos.y - i->map_y) * i->delta_dist.y;
	}
	else
	{
		i->step_y = 1;
		i->side_dist.y = (i->map_y + 1.0 - p->player.pos.y) * i->delta_dist.y;
	}
	while (hit == 0)
	{
		if (i->side_dist.x < i->side_dist.y)
		{
			i->side_dist.x += i->delta_dist.x;
			i->map_x += i->step_x;
			i->side = 0;
		}
		else
		{
			i->side_dist.y += i->delta_dist.y;
			i->map_y += i->step_y;
			i->side = 1;
		}
		if (p->map_info.level_map[i->map_x][i->map_y] == 1)
			hit = 1;
	}
	if (i->side == 0)
		i->perp_wall_dist = (i->map_x - p->player.pos.x + (1 - i->step_x) / 2) / i->ray_dir.x;
	else
		i->perp_wall_dist = (i->map_y - p->player.pos.y + (1 - i->step_y) / 2) / i->ray_dir.y;
	i->line_height = (int)(p->res_h / i->perp_wall_dist);
	i->draw_start = -i->line_height / 2 + p->res_h / 2;
	if (i->draw_start < 0)
		i->draw_start = 0;
	i->draw_end = i->line_height / 2 + p->res_h / 2;
	if (i->draw_end >= p->res_h)
		i->draw_end = p->res_h - 1;
	//texturing calculations
	if (i->side == 1 && i->ray_dir.y > 0)
		i->tex_num = 0;
	else if (i->side == 1 && i->ray_dir.y < 0)
		i->tex_num = 1;
	else if (i->side == 0 && i->ray_dir.x > 0)
		i->tex_num = 2;
	else if (i->side == 0 && i->ray_dir.x < 0)
		i->tex_num = 3;

	//calculate value of wall_x
	if (i->side == 0)
		i->wall_x = p->player.pos.y + i->perp_wall_dist * i->ray_dir.y;
	else
		i->wall_x = p->player.pos.x + i->perp_wall_dist * i->ray_dir.x;
	i->wall_x -= floor(i->wall_x);

	//x coordinate on the texture
	i->tex_x = (int)(i->wall_x * (double)p->map_info.tex_w);
	if (i->side == 0 && i->ray_dir.x > 0)
		i->tex_x = p->map_info.tex_w - i->tex_x - 1;
	if (i->side == 1 && i->ray_dir.y < 0)
		i->tex_x = p->map_info.tex_w - i->tex_x - 1;

	//how much to increase the texture coordinate per screen pixel
	i->step = 1.0 * p->map_info.tex_h / i->line_height;
	//starting texture coordinate
	i->tex_pos = (i->draw_start - p->res_h / 2 + i->line_height / 2) * i->step;
}

void	draw_world(t_param *p)
{
	t_raycast_info	i;
	int				x;
	int 			y;
	double			camera_x;
	unsigned int	color;
	
	x = -1;
	while (++x < p->res_w)
	{
		camera_x = 2 * x / (double)p->res_w - 1;
		i.ray_dir.x = p->player.dir.x + p->cam_plane.x * camera_x;
		i.ray_dir.y = p->player.dir.y + p->cam_plane.y * camera_x;
		raycast_calculations(p, &i);
		//drawing ceiling
		y = 0;
		while (y < i.draw_start)
		{
			my_mlx_pixel_put(p, x, y, p->map_info.ceiling_color);
			y++;
		}
		//draw vertical stripe of wall
		while (y < i.draw_end)
		{
			//cast the texture coordinate to integer
			i.tex_y = (int)i.tex_pos & (p->map_info.tex_h - 1);
			i.tex_pos += i.step;
			color = my_mlx_pixel_get(p->texture[i.tex_num], i.tex_x, i.tex_y);
			if (i.side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(p, x, y, color);
			y++;
		}
		//draw floor
		while (y < p->res_h)
		{
			my_mlx_pixel_put(p, x, y, p->map_info.floor_color);
			y++;
		}
		p->zbuffer[x] = i.perp_wall_dist;
	}
}
