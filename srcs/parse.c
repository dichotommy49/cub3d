/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 15:33:56 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/21 13:03:46 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	get_resolution(char **cub, t_cub3d *p)
{
	*cub = *cub + 1;
	p->res_w = cub3d_atoi(cub);
	p->res_h = cub3d_atoi(cub);
	if (p->res_w > 2560)
		p->res_w = 2560;
	if (p->res_h > 1440)
		p->res_h = 1440;
	if (p->res_w <= 0 || p->res_h <= 0)
		exit_cub3d(p, 1, "Resolution cannot be negative\n");
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
	while (*cub && *cub != '\n')
	{
		while (*cub == ' ')
			cub++;
		if (ft_isdigit(*cub))
		{
			i++;
			cub++;
		}
	}
	return (i);
}

int		get_map_height(char *cub)
{
	int	i;

	i = 0;
	while (*cub)
	{
		while (*cub && (ft_isdigit(*cub) || *cub == 'N' || *cub == 'S' || *cub == 'E' || *cub == 'W' || *cub == ' '))
			cub++;
		if (*cub == '\n')
		{
			i++;
			cub++;
		}
	}
	return (i);
}

int		read_cub(t_map *map_info, char *cub_path)
{
	int		fd;
	int		r;
	char	buf[32];

	if ((fd = open(cub_path, O_RDONLY)) < 0)
		return (-1);
	if (!(map_info->cub_content = ft_strdup("")))
		return (-1);
	while ((r = read(fd, buf, 31)) > 0)
	{
		buf[r] = 0;
		if (!(map_info->cub_content = cub3d_strjoin(map_info->cub_content, buf)))
			return (-1);
	}
	if (r < 0)
		return (-1);
	if (close(fd) < 0)
		return (-1);
	return (0);
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

void	set_player_starting_direction(t_cub3d *p, char c, int x, int y)
{
	if (p->player.starting_pos.x != 0)
		exit_cub3d(p, 1, "Map contains multiple spawn locations\n");	
	p->player.starting_pos.x = x + 0.5;
	p->player.starting_pos.y = y + 0.5;
	if (c == 'N')
	{
		p->player.starting_dir.x = 0;
		p->player.starting_dir.y = -1;
	}
	else if (c == 'S')
	{
		p->player.starting_dir.x = 0;
		p->player.starting_dir.y = 1;
	}
	else if (c == 'W')
	{
		p->player.starting_dir.x = 1;
		p->player.starting_dir.y = 0;
	}
	else if (c == 'E')
	{
		p->player.starting_dir.x = -1;
		p->player.starting_dir.y = 0;
	}
}

char	*process_non_map_info(t_cub3d *p)
{
	char	*cub;

	cub = p->map_info.cub_content;
	while (*cub)
	{
		if (*cub == 'R')
			get_resolution(&cub, p);
		if (*cub == 'N' || *cub == 'W' || *cub == 'E' || (*cub == 'S' && *(cub + 1) == 'O'))
			get_texture_path(&cub, &p->map_info, *cub);
		if (*cub == 'S')
			get_sprite_path(&cub, &p->map_info);
		if (*cub == 'F')
			get_color(&cub, &p->map_info, 0);
		if (*cub == 'C')
			get_color(&cub, &p->map_info, 1);
		if (ft_isdigit(*cub) && *(cub - 1) == '\n')
			break ;
		while (*cub == ' ' || *cub == '\n')
			cub++;
	}
	return (cub);
}

void	check_map_errors(t_cub3d *p, char *cub)
{
	while (*cub)
	{
		if (*cub == ' ')
			if (*(cub + 1) == ' ')
				exit_cub3d(p, 1, "Map contains multiple spaces in a row\n");
		if (*cub == '\n')
			if (*(cub + 1) == '\n')
				exit_cub3d(p, 1, "Map contains an empty line\n");
		if (*cub != 'N' && *cub != 'S' && *cub != 'E' && *cub != 'W' && *cub != ' ' && *cub != '\n' && *cub != '2' && *cub != '1' && *cub != '0')
			exit_cub3d(p, 1, "Map contains unrecognized character\n");
		cub++;
	}
}

//	this function copies the map into an int matrix. also gets number of sprites
//	for allocation. sets player starting location and direction.
void	copy_map(t_cub3d *p, char *cub)
{
	int	x;
	int	y;

	y = 0;
	while (y < p->map_info.map_h)
	{
		x = p->map_info.map_w - 1;
		while (x >= 0)
		{
			if (*cub == '\n' || *cub == ' ')
				cub++;
			else
			{
				if (*cub == '2')
					p->num_sprites++;
				if (ft_isalpha(*cub))
				{
					set_player_starting_direction(p, *cub, x, y);
					*cub = '0';
				}
				p->map_info.level_map[x][y] = *cub - '0';
				cub++;
				x--;
			}
		}
		y++;
	}
}

void	process_map_info(t_cub3d *p, char *cub)
{
	int	x;
	t_map	*map_info;

	map_info = &p->map_info;
	if ((map_info->map_w = get_map_width(cub)) <= 0)
		exit_cub3d(p, 1, "Problem reading map in .cub\n");
	if ((map_info->map_h = get_map_height(cub)) <= 0)
		exit_cub3d(p, 1, "Problem reading map in .cub\n");
	if (!(map_info->level_map = ft_calloc(sizeof(int *), map_info->map_w)))
		exit_cub3d(p, 1, "Malloc for level map failed\n");
	x = 0;
	while (x < map_info->map_w)
	{
		if (!(map_info->level_map[x++] = ft_calloc(sizeof(int), map_info->map_h)))
			exit_cub3d(p, 1, "Malloc for level map failed\n");
	}
}

void	initialize_sprites(t_cub3d *p)
{
	int	x;
	int	y;
	int	i;
	
	if (!(p->sprites = ft_calloc(sizeof(t_sprite), p->num_sprites)))
		exit_cub3d(p, 1, "Malloc for sprites failed\n");
	x = 0;
	i = 0;
	while (x < p->map_info.map_w)
	{
		y = 0;
		while (y < p->map_info.map_h)
		{
			if (p->map_info.level_map[x][y] == 2)
			{
				p->sprites[i].x = x + 0.5;
				p->sprites[i].y = y + 0.5;
				p->sprites[i].texture = 4;
				i++;
			}
			y++;
		}
		x++;
	}
}

void	check_map_enclosed(t_cub3d *p)
{
	int	i;

	i = 0;
	while (i < p->map_info.map_h)
	{
		if (p->map_info.level_map[0][i] == 1 && p->map_info.level_map[p->map_info.map_w - 1][i] == 1)
			i++;
		else
			exit_cub3d(p, 1, "Map is not fully enclosed\n");
	}
	i = 0;
	while (i < p->map_info.map_w)
	{
		if (p->map_info.level_map[i][0] == 1 && p->map_info.level_map[i][p->map_info.map_h - 1] == 1)
			i++;
		else
			exit_cub3d(p, 1, "Map is not fully enclosed\n");
	}
}

void	parse_cub(t_cub3d *p, char *cub_path)
{
	char	*cub;

	if (read_cub(&p->map_info, cub_path) < 0)
		exit_cub3d(p, 1, "Problem reading .cub file\n");
	cub = process_non_map_info(p);
	//	cub is now pointing to start of map element
	process_map_info(p, cub);
	check_map_errors(p, cub);
	copy_map(p, cub);
	check_map_enclosed(p);

	//allocate sprite array and get sprite positions
	initialize_sprites(p);
}
