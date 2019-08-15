/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iso.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 19:08:41 by rsticks           #+#    #+#             */
/*   Updated: 2019/08/14 20:30:19 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void		iso(double *x, double *y, double z, t_angle angle)
{
	t_angle	previous;

	previous.x = *x;
	previous.y = *y;
	previous.z = z;
	z = iso_iso(&y, &y, &previous, angle);
	if (angle.z != 0)
	{
		*x = previous.x * cos(angle.z) - previous.y * sin(angle.z);
		*y = previous.x * sin(angle.z) + previous.y * cos(angle.z);
		previous.x = *x;
		previous.y = *y;
	}
	*x = (previous.x - previous.y) * cos(0.523599);
	*y = ((previous.x + previous.y) * sin(0.523599)) - z;
}

double		iso_iso(double **x, double **y, t_angle *previous, t_angle angle)
{
	double	z;

	z = previous->z;
	if (angle.x != 0)
	{
		**y = previous->y * cos(angle.x) + previous->z * sin(angle.x);
		z = -previous->y * sin(angle.x) + previous->z * cos(angle.x);
		previous->y = **y;
		previous->z = z;
	}
	if (angle.y != 0)
	{
		**x = previous->x * cos(angle.y) + previous->z * sin(angle.y);
		z = -previous->x * sin(angle.y) + previous->z * cos(angle.y);
		previous->x = **x;
		previous->z = z;
	}
	return (z);
}

int		from_hex_to_dec(char *hex)
{
	int	tmp[2];
	int	dec;
	int power;

	dec = 0;
	power = strlen(hex);
	power--;
	while (power != -1)
	{
		if (*hex >= 97 && *hex <= 102)
			tmp[1] = 87;
		if (*hex >= 65 && *hex <= 70)
			tmp[1] = 55;
		if (*hex >= '0' && *hex <= '9')
			tmp[1] = 48;
		tmp[0] = (*hex - tmp[1]) * pow(16, power);
		dec = dec + tmp[0];
		hex++;
		power--;
	}
	return (dec);
}