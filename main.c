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

int				main(void)
{
	t_param		p;

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
