/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_pixels.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 18:54:52 by rsticks           #+#    #+#             */
/*   Updated: 2019/07/21 18:55:30 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int		get_pixels(int fd, t_pixel_data *xyz, t_pixel **pixel)
{
	char				*line;

	while (get_next_line(fd, &line) == 1)
	{
		xyz->x = 0;
		printf("%s\n", line);
		while (*line != '\0')
		{
			(*pixel)->z = ft_atoi(line);
			while (*line >= '0' && *line <= '9')
				line++;
				/*if (*line == ',')
				{
					
					pixel->color = 
				}*/
				
			while (*line == ' ')
				line++;
			(*pixel)->x = xyz->x;
			(*pixel)->y = xyz->y;
			xyz->x++;
			(*pixel) = (*pixel)->next;
			(*pixel) = (t_pixel*)malloc(sizeof(t_pixel));
		}
		xyz->y++;
	}
	return (0);
}