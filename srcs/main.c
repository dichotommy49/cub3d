/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:21:25 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/30 17:54:02 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void			init_map_info(t_param *p)
{
	p->map_info.north_tex_path = 0;
	p->map_info.south_tex_path = 0;
	p->map_info.east_tex_path = 0;
	p->map_info.west_tex_path = 0;
	p->map_info.sprite_path = 0;
	p->map_info.floor_color = 0;
	p->map_info.ceiling_color = 0;
	p->res_w = -1;
	p->res_h = -1;
	reset_keys(p);
}

int				exit_cub3d(t_param *p)
{
	if (p->mlx_ptr && p->win_ptr)
	{
		mlx_clear_window(p->mlx_ptr, p->win_ptr);
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
	}
	printf("Cub3d terminated successfully.");
	exit(0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_param		p;
	int			save_bmp;

	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		save_bmp = 1;
	}
	if (argc >= 2)
	{
		init_map_info(&p);
		if (!(p.map_info.cub_path = ft_strdup(argv[1])))
			return (1);
		parse_cub(&p);
	}
	if (!(p.mlx_ptr = mlx_init()))
		return (1);
	if (!(p.win_ptr = mlx_new_window(p.mlx_ptr, p.res_w, p.res_h, "cub3d")))
		return (1);
	var_init(&p);
	mlx_hook(p.win_ptr, 2, (1L<<0), key_press_hook, &p);
	mlx_hook(p.win_ptr, 3, (1L<<1), key_release_hook, &p);
	mlx_hook(p.win_ptr, 17, 0L, exit_cub3d, &p);
	mlx_loop_hook(p.mlx_ptr, loop_hook, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
