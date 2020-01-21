#include "cub3d.h"

static int	is_digit(char c)
{
	return (c >= '0' && c<= '9');	
}

static int	ft_atoi(char **str)
{
	int	r;
	int	sign;

	sign = 1;
	r = 0;
	while (**str == ' ')
		*str = *str + 1;
	if (**str == '-')
	{
		sign = -1;
		*str = *str + 1;
	}
	while (is_digit(**str))
	{
		r = r * 10 + **str - 48;
		*str = *str + 1;
	}
	return (r * sign);
}

static int	ft_strlen(char *s)
{
	int	i;
	
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char	*ft_strjoin(char *s1, char *s2)
{
	char	*output;
	int		i;
	int		j;

	if (!(output = malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
	{
		free(s1);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s1[i])
	{
		output[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		output[i + j] = s2[j];
		j++;
	}
	output[i + j] = 0;
	free(s1);
	return (output);
}

void	get_resolution(char **cub, t_map *map_info)
{
	*cub = *cub + 1;
	map_info->res_w = ft_atoi(cub);
	map_info->res_h = ft_atoi(cub);	
}

void	get_texture_path(char **cub, t_map *map_info, char c)
{
	int		i;

	i = 0;
	*cub = *cub + 1;
	if (c == 'S')
		*cub = *cub + 1;
	while (**cub == ' ')
		*cub = *cub + 1;
	if (c == 'N')
	{
		while (*(cub)[i] != ' ' && *(cub)[i] != '\n')
			i++;
		if (!(map_info->north_tex_path = malloc(i + 1)))
			return ;
		i = 0;
		while (**cub != ' ' && **cub != '\n')
		{
			map_info->north_tex_path[i++] = **cub;
			*cub = *cub + 1;
		}
	}
	else if (c == 'W')
	{
		while (*(cub)[i] != ' ' && *(cub)[i] != '\n')
			i++;
		if (!(map_info->west_tex_path = malloc(i + 1)))
			return ;
		i = 0;
		while (**cub != ' ' && **cub != '\n')
		{
			map_info->west_tex_path[i++] = **cub;
			*cub = *cub + 1;
		}
	}
	else if (c == 'E')
	{
		while (*(cub)[i] != ' ' && *(cub)[i] != '\n')
			i++;
		if (!(map_info->east_tex_path = malloc(i + 1)))
			return ;
		i = 0;
		while (**cub != ' ' && **cub != '\n')
		{
			map_info->east_tex_path[i++] = **cub;
			*cub = *cub + 1;
		}
	}
	else
	{
		while (*(cub)[i] != ' ' && *(cub)[i] != '\n')
			i++;
		if (!(map_info->south_tex_path = malloc(i + 1)))
			return ;
		i = 0;
		while (**cub != ' ' && **cub != '\n')
		{
			map_info->south_tex_path[i++] = **cub;
			*cub = *cub + 1;
		}
	}
}

void	get_sprite_path(char **cub, t_map *map_info)
{
	int		i;

	i = 0;
	*cub = *cub + 1;
	while (**cub == ' ')
		*cub = *cub + 1;
	while (*(cub)[i] != ' ' && *(cub)[i] != '\n')
		i++;
	if (!(map_info->sprite_path = malloc(i + 1)))
		return ;
	i = 0;
	while (**cub != ' ' && **cub != '\n')
	{
		map_info->sprite_path[i++] = **cub;
		*cub = *cub + 1;
	}
}

void	get_color(char **cub, t_map *map_info, int location)
{
	int		r;
	int		g;
	int		b;
	
	*cub = *cub + 1;
	r = ft_atoi(cub);
	*cub = *cub + 1;
	g = ft_atoi(cub);
	*cub = *cub + 1;
	b = ft_atoi(cub);
	*cub = *cub + 1;
	if (location == 0)
		map_info->floor_color = (b << 24 | g << 16 | r << 8);
	else if (location == 1)
		map_info->ceiling_color = (b << 24 | g << 16 | r << 8);
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
		if (!(cub = ft_strjoin(cub, buf)))
			return (-1);
	}
	map_info->cub_content = cub;
	return (0);
}

int		parse_cub(t_map *map_info)
{
	char	*cub;
	
	if (read_cub(map_info) < 0)
		return (-1);
	cub = map_info->cub_content;
	while (*cub)
	{
		while (*cub == ' ' || *cub == '\n')
			cub++;
		if (*cub == 'R')
			get_resolution(&cub, map_info);
		else if (*cub == 'N' || *cub == 'W' || *cub == 'E' || (*cub == 'S' && *(cub + 1) == 'O'))
			get_texture_path(&cub, map_info, *cub);
		else if (*cub == 'S')
			get_sprite_path(&cub, map_info);
		else if (*cub == 'F')
			get_color(&cub, map_info, 0);
		else if (*cub == 'C')
			get_color(&cub, map_info, 1);
		cub++;
	}
	free(map_info->cub_content);
	map_info->cub_content = NULL;
	return (0);
}
