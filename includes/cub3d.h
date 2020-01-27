/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:59:17 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/27 19:32:16 by tmelvin          ###   ########.fr       */
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
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define TEX_W 1024
# define TEX_H 1024

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct	s_map
{
	char			*cub_path;
	char			*cub_content;
	char			*north_tex_path;
	char			*south_tex_path;
	char			*east_tex_path;
	char			*west_tex_path;
	char			*sprite_path;
	unsigned int	floor_color;
	unsigned int	ceiling_color;
	int				map_w;
	int				map_h;
	int				**level_map;
	int				tex_w;
	int				tex_h;
}				t_map;

typedef struct	s_param
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			res_w;
	int			res_h;
	t_player	player;
	t_vector	cam_plane;
	t_img		screen1;
	t_img		screen2;
	int			current_screen;
	t_img		texture[8];
	t_map		map_info;
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

int				parse_cub(t_param *p);

/*
**	tools (mostly for map processing)
*/

int				cub3d_atoi(char **str);
unsigned int	cub3d_atoui(char **str);
char			*cub3d_strjoin(char *s1, char *s2);

#endif
