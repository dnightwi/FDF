/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 16:58:39 by dnightwi          #+#    #+#             */
/*   Updated: 2019/08/14 17:42:24 by dnightwi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void	draw_1(t_braz *inf, t_data_cords cord, t_mlx mlx, t_pixel_data max_cords)
{
	t_pixel	current;

	while (inf->x != inf->x1 || inf->y != inf->y1)
	{
		inf->f += inf->a * inf->signa;
		if (ft_abs(inf->f) > ft_abs(inf->f - ft_abs(inf->b)))
		{
			inf->f -= inf->b * inf->signb;
			inf->y += inf->signa;
		}
		inf->x -= inf->signb;
		current.x = inf->x;
		current.y = inf->y;
		current.color = inf->color;
		inf->color = get_cur_color(current, cord);
		mlx_pixel_put(mlx.ptr, mlx.window, ((960 -
		(max_cords.x * max_cords.scale / 4) + inf->x) + mlx.mv_x), (540 -
		(max_cords.y * max_cords.scale / 2) + inf->y) + mlx.mv_y, inf->color);
	}
}

static void	draw_2(t_braz *inf, t_data_cords cord, t_mlx mlx, t_pixel_data max_cords)
{
	t_pixel	current;

	while (inf->x != inf->x1 || inf->y != inf->y1)
	{
		inf->f += inf->b * inf->signb;
		if (ft_abs(inf->f) > ft_abs(inf->f - ft_abs(inf->a)))
		{
			inf->f -= inf->a * inf->signa;
			inf->x -= inf->signb;
		}
		inf->y += inf->signa;
		current.x = inf->x;
		current.y = inf->y;
		current.color = inf->color;
		inf->color = get_cur_color(current, cord);
		mlx_pixel_put(mlx.ptr, mlx.window, ((960 -
		(max_cords.x * max_cords.scale / 4) + inf->x) + mlx.mv_x), (540 -
		(max_cords.y * max_cords.scale / 2) + inf->y) + mlx.mv_y, inf->color);
	}
}

void		braz(t_data_cords cord, t_pixel_data max_cords, t_mlx mlx)
{
	t_braz	inf;

	inf.x1 = cord.end_x * max_cords.scale;
	inf.y1 = cord.end_y * max_cords.scale;
	inf.x = cord.start_x * max_cords.scale;
	inf.y = cord.start_y * max_cords.scale;
	inf.a = inf.y1 - inf.y;
	inf.b = inf.x - inf.x1;
	inf.f = 0;
	inf.color = cord.start_c;
	inf.sign = (ft_abs(inf.a) > ft_abs(inf.b)) ? 1 : -1;
	inf.signa = (inf.a < 0) ? -1 : 1;
	inf.signb = (inf.b < 0) ? -1 : 1;
	cord.start_x = inf.x;
	cord.end_x = inf.x1;
	cord.start_y = inf.y;
	cord.end_y = inf.y1;
	mlx_pixel_put(mlx.ptr, mlx.window, ((960 -
	(max_cords.x * max_cords.scale / 4) + inf.x) + mlx.mv_x), (540 -
	(max_cords.y * max_cords.scale / 2) + inf.y) + mlx.mv_y, inf.color);
	if (inf.sign == -1)
		draw_1(&inf, cord, mlx, max_cords);
	else
		draw_2(&inf, cord, mlx, max_cords);
}
