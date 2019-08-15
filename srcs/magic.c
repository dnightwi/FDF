/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/30 17:42:41 by dnightwi          #+#    #+#             */
/*   Updated: 2019/08/07 18:37:58 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			ft_abs(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

static void	draw_sides2(t_pixel **pixel,
t_pixel_data xyz, t_mlx mlx, t_angle angle)
{
	int				i;
	t_data_cords	cord;

	i = 0;
	while (pixel[i]->x < xyz.x - 1)
	{
		cord.start_x = pixel[i + (xyz.y - 1) * xyz.weight]->x;
		cord.start_y = pixel[i + (xyz.y - 1) * xyz.weight]->y;
		cord.end_x = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->x;
		cord.end_y = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->y;
		iso(&cord.start_x, &cord.start_y,
		pixel[i + (xyz.y - 1) * xyz.weight]->z, angle);
		iso(&cord.end_x, &cord.end_y,
		pixel[i + 1 + (xyz.y - 1) * xyz.weight]->z, angle);
		cord.start_c = pixel[i + (xyz.y - 1) * xyz.weight]->color;
		cord.end_c = pixel[i + 1 + (xyz.y - 1) * xyz.weight]->color;
		braz(cord, xyz, mlx);
		i++;
	}
}

static void	draw_sides1(t_pixel **pixel,
t_pixel_data xyz, t_mlx mlx, t_angle angle)
{
	int				j;
	t_data_cords	cord;

	j = 0;
	while (pixel[j * xyz.weight]->y < xyz.y - 1)
	{
		cord.start_x = pixel[xyz.x - 1 + j * xyz.weight]->x;
		cord.start_y = pixel[xyz.x - 1 + j * xyz.weight]->y;
		cord.end_x = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->x;
		cord.end_y = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->y;
		iso(&cord.start_x, &cord.start_y,
		pixel[xyz.x - 1 + j * xyz.weight]->z, angle);
		iso(&cord.end_x, &cord.end_y,
		pixel[xyz.x - 1 + (j + 1) * xyz.weight]->z, angle);
		cord.start_c = pixel[xyz.x - 1 + j * xyz.weight]->color;
		cord.end_c = pixel[xyz.x - 1 + (j + 1) * xyz.weight]->color;
		braz(cord, xyz, mlx);
		j++;
	}
	draw_sides2(pixel, xyz, mlx, angle);
}

static void	draw_vertical(t_pixel **pixel,
t_pixel_data xyz, t_mlx mlx, t_angle angle)
{
	int				i;
	int				j;
	t_data_cords	cord;

	i = -1;
	while (pixel[++i]->x < xyz.x - 1)
	{
		j = -1;
		while (pixel[++j * xyz.weight]->y < xyz.y - 1)
		{
			cord.start_x = pixel[i + j * xyz.weight]->x;
			cord.start_y = pixel[i + j * xyz.weight]->y;
			cord.end_x = pixel[i + (j + 1) * xyz.weight]->x;
			cord.end_y = pixel[i + (j + 1) * xyz.weight]->y;
			iso(&cord.start_x, &cord.start_y,
			pixel[i + j * xyz.weight]->z, angle);
			iso(&cord.end_x, &cord.end_y,
			pixel[i + (j + 1) * xyz.weight]->z, angle);
			cord.start_c = pixel[i + j * xyz.weight]->color;
			cord.end_c = pixel[i + (j + 1) * xyz.weight]->color;
			braz(cord, xyz, mlx);
		}
	}
	draw_sides1(pixel, xyz, mlx, angle);
}

void		draw_horizontal(t_pixel **pixel,
t_pixel_data xyz, t_mlx mlx, t_angle angle)
{
	int				i;
	t_data_cords	cord;

	i = 0;
	while (pixel[i]->y < xyz.y - 1)
	{
		if (pixel[i]->x == xyz.x - 1)
		{
			i++;
			continue;
		}
		cord.start_x = pixel[i]->x;
		cord.start_y = pixel[i]->y;
		cord.end_x = pixel[i + 1]->x;
		cord.end_y = pixel[i + 1]->y;
		iso(&cord.start_x, &cord.start_y, pixel[i]->z, angle);
		iso(&cord.end_x, &cord.end_y, pixel[i + 1]->z, angle);
		cord.start_c = pixel[i]->color;
		cord.end_c = pixel[i + 1]->color;
		braz(cord, xyz, mlx);
		i++;
	}
	draw_vertical(pixel, xyz, mlx, angle);
}
