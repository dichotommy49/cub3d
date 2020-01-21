/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:59:17 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/20 15:30:40 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>
# include <time.h>
# include "vector.h"
# include "img.h"
# include "mlx/mlx.h"

# define RES_W 1280
# define RES_H 1024
# define TEX_W 64
# define TEX_H 64
# define MAP_W 24
# define MAP_H 24

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct	s_map
{
	char		*cub_path;
	char		*cub_content;
	int			res_w;
	int			res_h;
	char		*north_tex_path;
	char		*south_tex_path;
	char		*east_tex_path;
	char		*west_tex_path;
	char		*sprite_path;
	int			floor_color;
	int			ceiling_color;
}				t_map;

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			world_map[RES_W][RES_H];
	t_player	player;
	t_vector	cam_plane;
	t_img		screen1;
	t_img		screen2;
	int			current_screen;
	int			texture[8][TEX_W * TEX_H];
	t_map		map_info;
	int			floor_color;
	int			ceiling_color;
//	struct timespec	old_time;
//	struct timespec	time;
}				t_param;

typedef struct	s_raycast
{

}				t_raycast;

/*
**	hooks
*/

int				key_press_hook(int keycode, t_param *p);
int				key_release_hook(int keycode, t_param *p);
int				loop_hook(t_param *p);

/*
**	raycasting
*/

void			var_init(t_param *p);
void			draw_screen(t_param *p);

/*
**	map processing
*/

int				parse_cub(t_map *map_info);

#endif
