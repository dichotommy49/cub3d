/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 15:01:52 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/13 17:45:02 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


void	dda(t_cub3d *p, t_raycast_info *i)
{
	int	map_x;
	int	map_y;
	int	hit;

	hit = 0;
	map_x = i->map_x;
	map_y = i->map_y;
	while (hit == 0)
	{
		if (i->side_dist.x < i->side_dist.y && !(i->side = 0))
		{
			i->side_dist.x += i->delta_dist.x;
			map_x += i->step_x;
		}
		else
		{
			i->side_dist.y += i->delta_dist.y;
			map_y += i->step_y;
			i->side = 1;
		}
		if (p->map_info.level_map[map_x][map_y] == 1)
			hit = 1;
	}
	i->perp_wall_dist = (i->side == 0) ? (map_x - p->player.pos.x +
		(1 - i->step_x) / 2) / i->ray_dir.x : (map_y - p->player.pos.y +
		(1 - i->step_y) / 2) / i->ray_dir.y;
}

void	raycast_calculations1(t_cub3d *p, t_raycast_info *i)
{
	i->delta_dist.x = fabs(1 / i->ray_dir.x);
	i->delta_dist.y = fabs(1 / i->ray_dir.y);
	i->step_x = (i->ray_dir.x < 0) ? -1 : 1;
	i->side_dist.x = (i->ray_dir.x < 0) ? (p->player.pos.x - i->map_x) *
		i->delta_dist.x : (i->map_x + 1.0 - p->player.pos.x) * i->delta_dist.x;		
	i->step_y = (i->ray_dir.y < 0) ? -1 : 1;
	i->side_dist.y = (i->ray_dir.y < 0) ? (p->player.pos.y - i->map_y) *
		i->delta_dist.y : (i->map_y + 1.0 - p->player.pos.y) * i->delta_dist.y;		
	dda(p, i);
	i->line_height = (int)(p->res_h / i->perp_wall_dist);
	i->draw_start = -i->line_height / 2 + p->res_h / 2;
	if (i->draw_start < 0)
		i->draw_start = 0;
	i->draw_end = i->line_height / 2 + p->res_h / 2;
	if (i->draw_end >= p->res_h)
		i->draw_end = p->res_h - 1;
	if (i->side == 1 && i->ray_dir.y > 0)
		i->tex_num = 0;
	else if (i->side == 1 && i->ray_dir.y < 0)
		i->tex_num = 1;
	else if (i->side == 0 && i->ray_dir.x > 0)
		i->tex_num = 2;
	else if (i->side == 0 && i->ray_dir.x < 0)
		i->tex_num = 3;
}

void	raycast_calculations2(t_cub3d *p, t_raycast_info *i)
{
	if (i->side == 0)
		i->wall_x = p->player.pos.y + i->perp_wall_dist * i->ray_dir.y;
	else
		i->wall_x = p->player.pos.x + i->perp_wall_dist * i->ray_dir.x;
	i->wall_x -= floor(i->wall_x);
	i->tex_x = (int)(i->wall_x * (double)p->map_info.tex_w);
	if (i->side == 0 && i->ray_dir.x > 0)
		i->tex_x = p->map_info.tex_w - i->tex_x - 1;
	if (i->side == 1 && i->ray_dir.y < 0)
		i->tex_x = p->map_info.tex_w - i->tex_x - 1;
	i->step = 1.0 * p->map_info.tex_h / i->line_height;
	i->tex_pos = (i->draw_start - p->res_h / 2 + i->line_height / 2) * i->step;
}

void	draw_ceiling_wall_floor(t_cub3d *p, t_raycast_info *i, int x)
{
		int				y;
		unsigned int	color;

		//draw ceiling
		y = 0;
		while (y < i->draw_start)
		{
			my_mlx_pixel_put(p, x, y++, p->map_info.ceiling_color);
		}
		//draw vertical stripe of wall
		while (y < i->draw_end)
		{
			//cast the texture coordinate to integer
			i->tex_y = (int)i->tex_pos & (p->map_info.tex_h - 1);
			i->tex_pos += i->step;
			color = my_mlx_pixel_get(p->texture[i->tex_num], i->tex_x, i->tex_y);
			if (i->side == 1)
				color = (color >> 1) & 8355711;
			my_mlx_pixel_put(p, x, y++, color);
		}
		//draw floor
		while (y < p->res_h)
		{
			my_mlx_pixel_put(p, x, y++, p->map_info.floor_color);
		}
}

void	draw_world(t_cub3d *p)
{
	t_raycast_info	i;
	int 			x;
	double			camera_x;
	
	i.map_x = (int)p->player.pos.x;
	i.map_y = (int)p->player.pos.y;
	x = -1;
	while (++x < p->res_w)
	{
		camera_x = 2 * x / (double)p->res_w - 1;
		i.ray_dir.x = p->player.dir.x + p->player.cam_plane.x * camera_x;
		i.ray_dir.y = p->player.dir.y + p->player.cam_plane.y * camera_x;
		raycast_calculations1(p, &i);
		raycast_calculations2(p, &i);
		draw_ceiling_wall_floor(p, &i, x);
		p->zbuffer[x] = i.perp_wall_dist;
	}
}
