/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsticks <rsticks@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/27 17:47:01 by rsticks           #+#    #+#             */
/*   Updated: 2019/08/12 17:03:45 by rsticks          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

t_pixel		**init_pixel(int fd)
{
	int			color_id;
	int			size;
	t_pixel		**pixel;

	color_id = 0;
	size = sizeof_file(fd, &color_id);
	printf("size = %d\n", size);
	size++;
	pixel = (t_pixel**)malloc(sizeof(t_pixel*) * size);
	while (size)
		pixel[--size] = (t_pixel*)malloc(sizeof(t_pixel));
	pixel[0]->color = color_id;
	close(fd);
	return (pixel);
}

int			sizeof_file(int fd, int *color)
{
	char				*ptr_line;
	char				*line;
	int					y;

	y = -1;
	while (get_next_line(fd, &line) == 1 && y++)
	{
		ptr_line = (y == 0) ? line : ptr_line;
		while (*line != '\0' && ++y)
		{
			if (ft_isdigit(*line))
				while (ft_isdigit(*line))
					line++;
			if (*line == ',')
			{
				*color = 1;
				while (!(ft_isspace(*line) || *line == '\0'))
					line++;
			}
			while (ft_isspace(*line))
				line++;
		}
	}
	free(ptr_line);
	return (y);
}
