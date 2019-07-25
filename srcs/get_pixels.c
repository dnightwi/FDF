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

int		sizeof_file(int fd)
{
	char				*line;
	int					x;
	int					y;

	y = 0;
	while (get_next_line(fd, &line) == 1)
	{
		x = 0;
		while (*line != '\0')
		{
			while (*line >= '0' && *line <= '9')
				line++;
				/*if (*line == ',')
				{
					
					pixel->color = 
				}*/
				
			while (*line == ' ')
				line++;
			x++;
		}
		y++;
	}
	return (x * y);
}

t_pixel		*get_pixels(int fd, t_pixel_data *xyz, t_pixel *pixel)
{
	char				*line;
	int					i;

	i = 0;
	while (get_next_line(fd, &line) == 1)
	{
		xyz->x = 0;
		printf("%s\n", line);
		while (*line != '\0')
		{
			pixel[i].x = ft_atoi(line);
			while (*line >= '0' && *line <= '9')
				line++;
				/*if (*line == ',')
				{
					
					pixel->color = 
				}*/
				
			while (*line == ' ')
				line++;
			pixel[i].x = xyz->x;
			pixel[i].y = xyz->y;
			xyz->x++;
			i++;
			//(*pixel)->next = (t_pixel*)malloc(sizeof(t_pixel));
			//(*pixel) = (*pixel)->next;
		}
		xyz->y++;
	}
	return (pixel);
}