#include "../includes/cub3d.h"

void	create_bmp_header(t_cub3d *p, unsigned char header[54], unsigned int pixel_bytes_per_row)
{
	unsigned int	*size_of_file;
	unsigned int	*width;
	unsigned int	*height;
	
	header[0] = 66;
	header[1] = 77;
	header[10] = 54;
	header[14] = 40;
	header[26] = 1;
	header[28] = 32;

	size_of_file = (unsigned int *)&header[2];
	*size_of_file = 54 + pixel_bytes_per_row * p->res_h;
	width = (unsigned int *)&header[18];
	*width = p->res_w;
	height = (unsigned int *)&header[22];
	*height = -p->res_h;
}

void	get_img_data(t_cub3d *p, t_pixel img_data[p->res_h][p->res_w])
{
	int	x;
	int	y;
	unsigned int	color;

	y = 0;
	while (y < p->res_h)
	{
		x = 0;
		while (x < p->res_w)
		{
			//not sure about this
			color = my_mlx_pixel_get(p->screen[1 - p->current_screen], x, y);
			img_data[y][x].T = get_t(color);
			img_data[y][x].R = get_r(color);
			img_data[y][x].G = get_g(color);
			img_data[y][x].B = get_b(color);
			x++;
		}
		y++;
	}
}

void	write_bmp(t_cub3d *p)
{
	int						fd;
	static unsigned char	header[54];
	unsigned int			pixel_bytes_per_row;
	int						row;
	t_pixel					img_data[p->res_h][p->res_w];
	
	if ((fd = open("first_image.bmp", O_WRONLY|O_CREAT|O_TRUNC,S_IRUSR|S_IWUSR|S_IRGRP|S_IWGRP|S_IROTH|S_IWOTH)) < 0)
		exit_cub3d(p, 1, "Could not create .bmp file");
	pixel_bytes_per_row = p->res_w * sizeof(t_pixel);
	create_bmp_header(p, header, pixel_bytes_per_row);
	write(fd, header, 54);
	get_img_data(p, img_data);
	row = 0;
	while (row < p->res_h)
	{
		write(fd, img_data[row], pixel_bytes_per_row);
		row++;
	}
	close(fd);
	exit_cub3d(p, 0, "first_image.bmp successfully saved\n");
}
