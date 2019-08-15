/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 13:59:34 by rsticks           #+#    #+#             */
/*   Updated: 2019/07/12 18:03:54 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	move_z(t_dta **data)
{
	int i;

	i = -1;
	while (++i < (*data)->xyz.x * (*data)->xyz.y)
		(*data)->pixel[i]->z = (*data)->angle.moves_count
		* (*data)->pixel[i]->z1;
}

void	menu(t_mlx mlx)
{
	mlx_string_put(mlx.ptr, mlx.window, 75, 10, 3328900, "Menu");
	mlx_string_put(mlx.ptr, mlx.window, 5, 25, 3328900,
	"Move image-arrows up, down, left, right");
	mlx_string_put(mlx.ptr, mlx.window, 5, 40, 3328900, "1 - raise, 2 - lower");
	mlx_string_put(mlx.ptr, mlx.window, 5, 55, 3328900,
	"+, -: zoom in, zoom out");
	mlx_string_put(mlx.ptr, mlx.window, 5, 70, 3328900,
	"Rotate by axis: W, S, A, D, 9, 0");
	mlx_string_put(mlx.ptr, mlx.window, 5, 85, 3328900,
	"Change view angle - I, O");
}

int		key_hook(int key, t_dta *data)
{
	if (key == 53)
		exit(1);
	else if (key == 24 || key == 27)
		data->xyz.scale += (key == 24) ? 1 : -1;
	else if (key == 18 || key == 19)
	{
		data->angle.moves_count += (key == 18) ? 0.03 : -0.03;
		move_z(&data);
	}
	else if (key == 126 || key == 125)
		data->mlx.mv_y += (key == 126) ? -5 : 5;
	else if (key == 123 || key == 124)
		data->mlx.mv_x += (key == 123) ? -5 : 5;
	else if (key == 13 || key == 1)
		data->angle.x -= (key == 13) ? 0.01 : -0.01;
	else if (key == 0 || key == 2)
		data->angle.y -= (key == 0) ? 0.01 : -0.01;
	else if (key == 25 || key == 29)
		data->angle.z += (key == 25) ? 0.01 : -0.01;
	else if (key == 34 || key == 31)
		data->angle.projection = (key == 34) ? 0.523599 : 0;
	mlx_clear_window(data->mlx.ptr, data->mlx.window);
	menu(data->mlx);
	draw_horizontal(data->pixel, data->xyz, data->mlx, data->angle);
	return (0);
}

void	data_def(t_dta **data, int fd)
{
	(*data) = (t_dta*)malloc(sizeof(t_dta));
	(*data)->xyz.max_z = 0;
	(*data)->xyz.min_z = 0;
	(*data)->pixel = init_pixel(fd);
	(*data)->angle.x = 0;
	(*data)->angle.y = 0;
	(*data)->angle.z = 0;
	(*data)->mlx.mv_x = 0;
	(*data)->mlx.mv_y = 0;
	(*data)->angle.moves_count = 1;
	(*data)->angle.projection = 0.523599;
	(*data)->xyz.weight = 0;
	(*data)->xyz.y = 0;
	(*data)->xyz.x = 0;
}

int		main(int argc, char **argv)
{
	t_pixel				**pixel;
	t_dta				*data;
	struct s_size		size;
	int					fd;

	if (argc != 2)
		ft_putendl("Usage: ./fdf [file]");
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		ft_putendl("Invalid file");
		return (1);
	}
	data_def(&data, fd);
	fd = open(argv[1], O_RDONLY);
	get_pixels(fd, &(data->xyz), data->pixel);
	data->xyz.scale = scale(data->pixel, data->xyz, data->angle);
	data->mlx.ptr = mlx_init();
	data->mlx.window = mlx_new_window(data->mlx.ptr, 1920, 1080, argv[1]);
	menu(data->mlx);
	draw_horizontal(data->pixel, data->xyz, data->mlx, data->angle);
	mlx_hook(data->mlx.window, 2, 0, (int (*)())key_hook, data);
	mlx_loop(data->mlx.ptr);
	return (0);
}
