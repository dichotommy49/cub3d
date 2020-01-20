/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textured_raycaster.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmelvin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 11:16:49 by tmelvin           #+#    #+#             */
/*   Updated: 2020/01/20 13:25:37 by tmelvin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURED_RAYCASTER_H
# define TEXTURED_RAYCASTER_H

# include <stdio.h>
# include <math.h>
# include <time.h>
# include "vector.h"
# include "img.h"
# include "mlx.h"

# define RES_W 1280
# define RES_H 1024
# define TEX_W 64
# define TEX_H 64
# define MAP_W 24
# define MAP_H 24

typedef struct	player_s
{
	vector_t	pos;
	vector_t	dir;
	double		move_speed;
	double		rot_speed;
}				player_t;

typedef struct	param_s
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			world_map[RES_W][RES_H];
	player_t	player;
	vector_t	cam_plane;
	img_t		screen1;
	img_t		screen2;
	int			current_screen;
	int			texture[8][TEX_W * TEX_H];
	int			background_color;
//	struct timespec	old_time;
//	struct timespec	time;
}				param_t;

void			var_init(param_t *p);
void			draw_screen(param_t *p);

#endif
