/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 14:59:17 by tmelvin           #+#    #+#             */
/*   Updated: 2020/02/13 17:40:04 by tmelvin          ###   ########.fr       */
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
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define TEX_W 64
# define TEX_H 64

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_sprite_info
{
	t_vector	pos;
	t_vector	transform;
	double		inv_det;
	t_vector	screen;
	int			height;
	int			width;
	t_vector	draw_start;
	t_vector	draw_end;
}				t_sprite_info;

typedef struct	s_raycast_info
{
	t_vector	ray_dir;
	int			map_x;
	int			map_y;
	t_vector	side_dist;
	t_vector	delta_dist;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			tex_num;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
}				t_raycast_info;

typedef struct s_img
{
	void        *img;
	char        *addr;
	int         bpp;
	int         line_length;
	int         endian;
}               t_img;

typedef struct	s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	cam_plane;
	double		move_speed;
	double		rot_speed;
}				t_player;

typedef struct	s_keys
{
	int			up_arrow;
	int			down_arrow;
	int			left_arrow;
	int			right_arrow;
	int			w;
	int			a;
	int			s;
	int			d;
	int			space;
}				t_keys;

typedef struct	s_map
{
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

typedef struct	s_cub3d
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			res_w;
	int			res_h;
	t_player	player;
	t_img		screen1;
	t_img		screen2;
	int			current_screen;
	t_img		texture[5];
	t_map		map_info;
	t_keys		keys;
	double		*zbuffer;
	int			num_sprites;
	t_sprite	*sprites;
//	struct timespec	old_time;
//	struct timespec	time;
	int			save_bmp;
}				t_cub3d;

/*
**	initialization
*/

void	init_textures(t_cub3d *p);
void	init_game(t_cub3d *p);

/*
**	core functions
*/

void			update(t_cub3d *p);
void			draw(t_cub3d *p);

/*
**	hooks
*/

int				key_press_hook(int keycode, t_cub3d *p);
int				key_release_hook(int keycode, t_cub3d *p);
int				loop_hook(t_cub3d *p);

/*
**	drawing
*/

void			draw_world(t_cub3d *p);
void			draw_sprites(t_cub3d *p);
void			draw_screen(t_cub3d *p);

/*
**	map processing
*/

int				parse_cub(t_cub3d *p, char *cub_path);

/*
**	tools (mostly for map processing)
*/

int				cub3d_atoi(char **str);
unsigned int	cub3d_atoui(char **str);
char			*cub3d_strjoin(char *s1, char *s2);
int				exit_cub3d(t_cub3d *p);

void			reset_keys(t_cub3d *p);

void			my_mlx_pixel_put(t_cub3d *p, int x, int y, int color);
unsigned int	my_mlx_pixel_get(t_img img, int x, int y);

#endif
