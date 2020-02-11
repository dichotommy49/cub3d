#include "../includes/cub3d.h"

void	init_textures(t_param *p)
{
	p->texture[0].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.north_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[1].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.south_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[2].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.east_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[3].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.west_tex_path, &p->map_info.tex_w, &p->map_info.tex_h);
	p->texture[4].img = mlx_xpm_file_to_image(p->mlx_ptr,
			p->map_info.sprite_path, &p->map_info.tex_w, &p->map_info.tex_h);

	p->texture[0].addr = mlx_get_data_addr(p->texture[0].img, &p->texture[0].bpp
			, &p->texture[0].line_length, &p->texture[0].endian);
	p->texture[1].addr = mlx_get_data_addr(p->texture[1].img, &p->texture[1].bpp
			, &p->texture[1].line_length, &p->texture[1].endian);
	p->texture[2].addr = mlx_get_data_addr(p->texture[2].img, &p->texture[2].bpp
			, &p->texture[2].line_length, &p->texture[2].endian);
	p->texture[3].addr = mlx_get_data_addr(p->texture[3].img, &p->texture[3].bpp
			, &p->texture[3].line_length, &p->texture[3].endian);
	p->texture[4].addr = mlx_get_data_addr(p->texture[4].img, &p->texture[4].bpp
			, &p->texture[4].line_length, &p->texture[4].endian);
}

void	init_game(t_param *p)
{
	if (!(p->zbuffer = malloc(sizeof(double) * p->res_w)))
		return ;
//	clock_gettime(CLOCK_REALTIME, &p->time);
	p->current_screen = 1;
	p->screen1.img = mlx_new_image(p->mlx_ptr, p->res_w, p->res_h);
	p->screen1.addr = mlx_get_data_addr(p->screen1.img, &p->screen1.bpp,
			&p->screen1.line_length, &p->screen1.endian);
	p->screen2.img = mlx_new_image(p->mlx_ptr, p->res_w, p->res_h);
	p->screen2.addr = mlx_get_data_addr(p->screen2.img, &p->screen2.bpp,
			&p->screen2.line_length, &p->screen2.endian);

	//set textures
	init_textures(p);

	p->player.move_speed = 0.1;
	p->player.rot_speed = 0.05;
}

void		init_keys(t_param *p)
{
	p->keys.up_arrow = 0;
	p->keys.down_arrow = 0;
	p->keys.left_arrow = 0;
	p->keys.right_arrow = 0;
	p->keys.w = 0;
	p->keys.a = 0;
	p->keys.s = 0;
	p->keys.d = 0;
	p->keys.space = 0;
}

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
	init_keys(p);
}
