/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   magic_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/03 14:29:12 by rsticks           #+#    #+#             */
/*   Updated: 2019/08/15 14:30:13 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int			scale(t_pixel **pixel, t_pixel_data xyz, t_angle angle)
{
	t_max_cords	max_cords;
	t_angle		cord;
	int			i;
	int			scale[2];

	CRD_P(max_cords.max_x, max_cords.max_x, max_cords.min_x, max_cords.min_y);
	i = 0;
	while (i < ((xyz.x) * (xyz.y)))
	{
		cord.x = pixel[i]->x;
		cord.y = pixel[i]->y;
		iso(&cord.x, &cord.y, pixel[i]->z, angle);
		cord.x = 960 - xyz.x + cord.x;
		cord.y = 540 - xyz.y / 2 + cord.y;
		max_cords.max_x = max_cords.max_x < cord.x ? cord.x : max_cords.max_x;
		max_cords.max_y = max_cords.max_y < cord.y ? cord.y : max_cords.max_y;
		max_cords.min_x = max_cords.min_x > cord.x ? cord.x : max_cords.min_x;
		max_cords.min_y = max_cords.min_y > cord.y ? cord.y : max_cords.min_y;
		i++;
	}
	scale[0] = 1536 / (max_cords.max_x - max_cords.min_x);
	scale[1] = 810 / (max_cords.max_y - max_cords.min_y);
	return (scale[0] > scale[1] ? scale[1] : scale[0]);
}

double		percent(int start, int end, int avr)
{
	double	placement;
	double	distance;

	placement = avr - start;
	distance = end - start;
	return ((distance == 0) ? 1.0 : (placement / distance));
}

int			get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}

int			get_cur_color(t_pixel current, t_data_cords cor)
{
	int		r;
	int		g;
	int		b;
	double	percen;
	t_pixel	delta;

	delta.x = ft_abs(cor.start_x - cor.end_x);
	delta.y = ft_abs(cor.start_y - cor.end_y);
	if (current.color == cor.end_c)
		return (current.color);
	if (delta.x > delta.y)
		percen = percent(cor.start_x, cor.end_x, current.x);
	else
		percen = percent(cor.start_y, cor.end_y, current.y);
	r = get_light((cor.start_c >> 16) & 0xFF, (cor.end_c >> 16) & 0xFF, percen);
	g = get_light((cor.start_c >> 8) & 0xFF, (cor.end_c >> 8) & 0xFF, percen);
	b = get_light(cor.start_c & 0xFF, cor.end_c & 0xFF, percen);
	return ((r << 16) | (g << 8) | b);
}
