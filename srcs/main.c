/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/19 18:21:25 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/13 17:34:36 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"


int				exit_cub3d(t_cub3d *p, int error, char *err_msg)
{
	if (p->mlx_ptr && p->win_ptr)
	{
		mlx_clear_window(p->mlx_ptr, p->win_ptr);
		mlx_destroy_window(p->mlx_ptr, p->win_ptr);
		p->win_ptr = NULL;
	}
	if (error)
	{
		if (p->map_info.cub_content)
			free(p->map_info.cub_content);
		if (p->map_info.north_tex_path)
			free(p->map_info.north_tex_path);
		if (p->map_info.south_tex_path)
			free(p->map_info.south_tex_path);
		if (p->map_info.east_tex_path)
			free(p->map_info.east_tex_path);
		if (p->map_info.west_tex_path)
			free(p->map_info.west_tex_path);
		if (p->map_info.sprite_path)
			free(p->map_info.sprite_path);
		ft_putstr_fd("Error\n", STDERR_FILENO);
		ft_putstr_fd(err_msg, STDERR_FILENO);
	}
	else
	{
		ft_putstr_fd("Cub3d terminated successfully\n", STDOUT_FILENO);
	}
	if (p->zbuffer)
		free(p->zbuffer);
	if (p->sprites)
		free(p->sprites);
	//should free level map as well
	if (p)
		free(p);
	exit(0);
	return (0);
}

int				main(int argc, char **argv)
{
	t_cub3d		*p;

	if (!(p = ft_calloc(sizeof(t_cub3d), 1)))
		exit_cub3d(p, 1, "Malloc failed\n");
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
	{
		p->save_bmp = 1;
	}
	if (argc == 2 || (argc == 3 && p->save_bmp))
	{
		parse_cub(p, argv[1]);
		if (!(p->mlx_ptr = mlx_init()))
			return (1);
		if (!(p->win_ptr = mlx_new_window(p->mlx_ptr, p->res_w, p->res_h, "cub3d")))
			return (1);
		init_game(p);
		mlx_hook(p->win_ptr, 2, (1L<<0), key_press_hook, p);
		mlx_hook(p->win_ptr, 3, (1L<<1), key_release_hook, p);
		mlx_hook(p->win_ptr, 17, 0L, exit_hook, p);
		mlx_loop_hook(p->mlx_ptr, loop_hook, p);
		mlx_loop(p->mlx_ptr);
	}
	else
	{
		exit_cub3d(p, 1, "Incorrect arguments\n");
	}
	return (0);
}
