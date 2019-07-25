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

int		key_exit(int key, void *init)
{
	(void)init;
	if (key == 53)
	{
		exit(1);
	}
	return(0);
}

int		ft_abs(int i)
{
	if (i < 0)
		i *= -1;
	return (i);
}

void	braz(int *start, int *end, t_pixel_data max_cords, t_mlx mlx)
{
	int	a;
	int	b;
	int	sign;
	int	signa;
	int	signb;
	int	f;
	int	x;
	int	y;
	int	x1;
	int	y1;
	int	x0;
	int	y0;

	//printf("corx = %d\ncory = %d\n\n", cords->x, cords->y);
	x0 = start[0] * 30; //30 is zoom
	y0 = start[1] * 30;
	x1 = end[0] * 30;
	y1 = end[1] * 30;
	x = x0;
	y = y0;
	a = y1 - y0;
	b = x0 - x1;
	f = 0;
	if (ft_abs(a) > ft_abs(b))
		sign = 1;
	else
		sign = -1;
	if (a < 0)
		signa = -1;
	else
		signa = 1;
	if (b < 0)
		signb = -1;
	else
		signb = 1;
	mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * 30) + x, 540 - (max_cords.y * 30) + y, 0xFF0000);
	if (sign == -1)
	{
		while (x != x1 || y != y1)
		{
			f += a * signa;
			if (ft_abs(f) > ft_abs(f - ft_abs(b)))
			{
				f -= b * signb;
				y += signa;
			}
			x -= signb;
			mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * 30) + x, 540 - (max_cords.y * 30) + y, 0xFF0000);

		}
	}
	else
	{
		while (x != x1 || y != y1)
		{
			f += b * signb;
			if (ft_abs(f) > ft_abs(f - ft_abs(a)))
			{
				f -= a * signa;
				x -= signb;
			}
			y += signa;
			mlx_pixel_put(mlx.ptr, mlx.window, 960 - (max_cords.x * 30) + x, 540 - (max_cords.y * 30) + y, 0xFF0000);
		}
	}
	
}

int		main(int argc, char **argv)
{
	t_pixel				*pixel;
	struct s_size		size;
	t_pixel_data		xyz;
	t_mlx				mlx;
	int					fd;
	int 				i;
	int					xy0[2];
	int					xy1[2];


	size.height = 0;
	size.width = 0;
	xyz.x = 0;
	xyz.y = 0;
	xyz.z = 0;
	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	//printf("%d\n", sizeof_file(fd));
	pixel = (t_pixel *)malloc(sizeof(t_pixel) * sizeof_file(fd));
	close(fd);
	fd = open(argv[1], O_RDONLY);
	pixel = get_pixels(fd, &xyz, pixel);
	printf("%d", pixel[76].y);

	//xyz.x = xyz.x / 2; //doesnt work properly
	//xyz.y = xyz.y / 2;
	//free(pixel);
	//pixel = NULL;
	mlx.ptr = mlx_init();
	mlx.window = mlx_new_window(mlx.ptr, 1920, 1080, "FDF");
	i = 0;
	//pixel = ptr_pxl;
	/*while (pixel[i])
	{
		xy0[0] = pixel[i]->x;
		xy0[1] = pixel[i]->y;
		xy1[0] = pixel[i + 1]->x;
		xy1[1] = pixel[i + 1]->y;
		if (pixel[i]->x == xyz.x - 1)
		{
			i++;
			continue;
		}
		braz(xy0, xy1, xyz, mlx);
		//mlx_pixel_put(mlx.ptr, mlx.window, 960 - (xyz.x * 30) + (ptr_pxl->x * 30), 540 - (xyz.y * 30) + (ptr_pxl->y * 30), 0xFF0000);
		i++;
	}
	//ptr_pxl = pixel;
	//printf("%d\n%d\n", xyz.x, xyz.y);
	while (ptr_pxl->x != xyz.x - 1)
	{
		xy0[0] = ptr_pxl->x;
		xy0[1] = ptr_pxl->y;
		xy1[0] = ptr_pxl->x;
		xy1[1] = xyz.y;
		braz(xy0, xy1, xyz, mlx);
		ptr_pxl = ptr_pxl->next;
	}*/
	//mlx.ptr_image = mlx_new_image(mlx.ptr, 720, 540);
	//mlx_put_image_to_window(mlx.ptr, mlx.window, mlx.ptr_image, 0, 0);
	//mlx_pixel_put(mlx.ptr, mlx.window, 960 - xyz.x, 540 - xyz.y, 0xFF0000);
	mlx_key_hook(mlx.window, key_exit, mlx.ptr);
	mlx_loop(mlx.ptr);
	return (0);
}
