/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:33:56 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/27 19:07:08 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_resolution(char **cub, t_param *p)
{
	*cub = *cub + 1;
	p->res_w = cub3d_atoi(cub);
	p->res_h = cub3d_atoi(cub);	
}

void	get_texture_path(char **cub, t_map *map_info, char c)
{
	int		i;
	char	**target;

	i = 0;
	while(ft_isalpha(**cub))
		*cub = *cub + 1;
	while (**cub == ' ')
		*cub = *cub + 1;
	if (c == 'N')
		target = &map_info->north_tex_path;
	else if (c == 'W')
		target = &map_info->west_tex_path;
	else if (c == 'E')
		target = &map_info->east_tex_path;
	else if (c == 'S')
		target = &map_info->south_tex_path;
	while ((*cub)[i] != ' ' && (*cub)[i] != '\n')
		i++;
	if (!(*target = malloc(i + 1)))
		return ;
	i = 0;
	while (**cub != ' ' && **cub != '\n')
	{
		(*target)[i++] = **cub;
		*cub = *cub + 1;
	}
	(*target)[i] = 0;
}

void	get_sprite_path(char **cub, t_map *map_info)
{
	int		i;

	i = 0;
	*cub = *cub + 1;
	while (**cub == ' ')
		*cub = *cub + 1;
	while ((*cub)[i] != ' ' && (*cub)[i] != '\n')
		i++;
	if (!(map_info->sprite_path = malloc(i + 1)))
		return ;
	i = 0;
	while (**cub != ' ' && **cub != '\n')
	{
		map_info->sprite_path[i++] = **cub;
		*cub = *cub + 1;
	}
	map_info->sprite_path[i] = 0;
}

void	get_color(char **cub, t_map *map_info, int ceiling)
{
	int		r;
	int		g;
	int		b;
	unsigned int	color;
	
	*cub = *cub + 1;
	r = cub3d_atoui(cub);
	*cub = *cub + 1;
	g = cub3d_atoui(cub);
	*cub = *cub + 1;
	b = cub3d_atoui(cub);
	*cub = *cub + 1;
	color = (r << 16 | g << 8 | b);
	if (!ceiling)
		map_info->floor_color = color;
	else
		map_info->ceiling_color = color;
}

int		get_map_width(char *cub)
{
	int	i;
	
	i = 0;
	while (cub[i] && cub[i] != '\n')
	{
		i++;
	}
	return (i);
}

int		get_map_height(char *cub)
{
	int	i;

	i = 0;
	while (*cub)
	{
		if (!ft_isdigit(*cub))
			break ;
		while (*cub && (ft_isdigit(*cub) || *cub == 'N' || *cub == 'S' || *cub == 'E' || *cub == 'W'))
			cub++;
		if (*cub == '\n')
		{
			i++;
			cub++;
		}
	}
	return (i);
}

int		read_cub(t_map *map_info)
{
	int		fd;
	int		r;
	char	buf[32];
	char	*cub;
	
	if ((fd = open(map_info->cub_path, O_RDONLY)) < 0)
		return (-1);
	if (!(cub = malloc(1)) || (cub[0] = 0))
		return (-1);
	while ((r = read(fd, buf, 31)) > 0)
	{
		buf[r] = 0;
		if (!(cub = cub3d_strjoin(cub, buf)))
			return (-1);
	}
	map_info->cub_content = cub;
	return (0);
}

void	zero_level_map(t_map *map_info)
{
	int x;
	int y;
	
	x = 0;
	y = 0;
	while (x < map_info->map_w)
	{
		y = 0;
		while (y < map_info->map_h)
		{
			map_info->level_map[x][y] = 0;
			y++;
		}
		x++;
	}
}

void	print_level_map(t_map *map_info)
{
	int x;
	int y;
	
	printf("map_w: %d\nmap_h: %d\n", map_info->map_w, map_info->map_h);
	x = 0;
	y = 0;
	while (x < map_info->map_w)
	{
		y = 0;
		while (y < map_info->map_h)
		{
			printf("%d", map_info->level_map[x][y]);
			y++;
		}
		printf("\n");
		x++;
	}
}

int		parse_cub(t_param *p)
{
	char	*cub;
	int		x;
	int		y;
	t_map 	*map_info;

	map_info = &p->map_info;
	if (read_cub(map_info) < 0)
		return (-1);
	cub = map_info->cub_content;
	while (*cub)
	{
		while (*cub == ' ' || *cub == '\n')
			cub++;
		if (*cub == 'R')
			get_resolution(&cub, p);
		if (*cub == 'N' || *cub == 'W' || *cub == 'E' || (*cub == 'S' && *(cub + 1) == 'O'))
			get_texture_path(&cub, map_info, *cub);
		if (*cub == 'S')
			get_sprite_path(&cub, map_info);
		if (*cub == 'F')
			get_color(&cub, map_info, 0);
		if (*cub == 'C')
			get_color(&cub, map_info, 1);
		if (ft_isdigit(*cub) && *(cub - 1) == '\n')
			break ;
	}
	map_info->map_w = get_map_width(cub);
	map_info->map_h = get_map_height(cub);
	map_info->level_map = malloc(sizeof(int *) * map_info->map_w);
	x = 0;
	while (x < map_info->map_w)
		map_info->level_map[x++] = malloc(sizeof(int) * map_info->map_h);
	zero_level_map(map_info);
	x = 0;
	y = 0;
	while (y < map_info->map_h)
	{
		x = 0;
		while (x < map_info->map_w)
		{
			if (*cub == '\n')
			{
				cub++;
			}
			else
			{
				if (*cub == 'N' || *cub == 'S' || *cub == 'W' || *cub == 'E')
				{
					p->player.pos.x = x; 
					p->player.pos.y = y + 0.5;
					if (*cub == 'N')
					{
						p->player.dir.x = -1;
						p->player.dir.y = 0;
					}
					else if (*cub == 'S')
					{
						p->player.dir.x = 1;
						p->player.dir.y = 0;
					}
					else if (*cub == 'W')
					{
						p->player.dir.x = 0;
						p->player.dir.y = -1;
					}
					else if (*cub == 'E')
					{
						p->player.dir.x = 0;
						p->player.dir.y = 1;
					}
					map_info->level_map[x][y] = 0;
				}
				else
					map_info->level_map[x][y] = *cub - '0';
				cub++;
				x++;
			}
		}
		y++;
	}
	free(map_info->cub_content);
	map_info->cub_content = NULL;
	free(map_info->cub_path);
	map_info->cub_path = NULL;
	map_info->tex_w = TEX_W;
	map_info->tex_h = TEX_H;
	return (0);
}
