/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:21:25 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/20 15:16:00 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

static char		*ft_strdup(char *s)
{
	char	*output;
	int		i;

	if (!(output = malloc(ft_strlen(s) + 1)))
		return (NULL);
	i = 0;
	while (*s)
		output[i++] = *s++;
	output[i] = 0;
	return (output);
}

static int		ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 != *s2)
		return (*s1 - *s2);
	return (0);
}

int				main(int argc, char **argv)
{
	t_param		p;
	int			save_bmp;

	if (argc == 3)
	{
		if (ft_strcmp(argv[2], "--save") != 0)
			return (1);
		save_bmp = 1;
	}
	if (argc == 2 || argc == 3)
	{
		p.map_info.cub_path = ft_strdup(argv[1]);
		int d = parse_cub(&p.map_info);
		printf("parse_cub function return: %d\n", d);
	}
	if (!(p.mlx_ptr = mlx_init()))
		return (1);
	if (!(p.win_ptr = mlx_new_window(p.mlx_ptr, RES_W, RES_H, "cub3d")))
		return (1);
	var_init(&p);
	mlx_hook(p.win_ptr, 2, (1L<<0), key_press_hook, &p);
	mlx_hook(p.win_ptr, 3, (1L<<1), key_release_hook, &p);
	mlx_loop_hook(p.mlx_ptr, loop_hook, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
