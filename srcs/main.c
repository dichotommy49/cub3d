/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:21:25 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/13 16:46:27 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int				exit_cub3d(t_cub3d *p)
{
	if (p->mlx_ptr && p->win_ptr)
	{
		mlx_clear_window(p->mlx_ptr, p->win_ptr);
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		p->win_ptr = NULL;
	}
	printf("Cub3d terminated successfully.");
	exit(0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_cub3d		p;

	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		p.save_bmp = 1;
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
	init_game(&p);
	mlx_hook(p.win_ptr, 2, (1L<<0), key_press_hook, &p);
	mlx_hook(p.win_ptr, 3, (1L<<1), key_release_hook, &p);
	mlx_hook(p.win_ptr, 17, 0L, exit_cub3d, &p);
	mlx_loop_hook(p.mlx_ptr, loop_hook, &p);
	mlx_loop(p.mlx_ptr);
	return (0);
}
