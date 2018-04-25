/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:22:51 by csimon            #+#    #+#             */
/*   Updated: 2017/06/13 11:22:52 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fractol.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define MOTIONNOTIFY 6
#define POINTERMOTIONMASK (1L<<6)
#include <stdio.h>

void	jul_bar(float x, float y, float *c, t_data *data)
{
	float	zr;
	float	zi;
	int		i;
	float	tmp;

	zr = x / data->zoom + -1.5;
	zi = y / data->zoom + -1.5;
	i = 0;
	while (sqrtf(zr * zr + zi * zi) < 4 && i < 50)
	{
		tmp = zr;
		zr = zr * zr - zi * zi + c[0];
		zi = 2 * zi * tmp + c[1];
		i++;
		if (i == 50)
		{
			img_fill_pixel(data->img_str, x, y, 255);
			break ;
		}
		else
			img_fill_pixel(data->img_str, x, y, (i * 255 / 50));
	}
}

void	jul_foo(t_data *data, float x, float y, char *img_str)
{
	float	c[2];
	float	img_x;
	float	img_y;

	img_x = 9 * data->zoom;
	img_y = 9 * data->zoom;
	if (!img_str)
		x++;
	c[0] = (x - (LEN / 1)) / (LEN / 1);
	c[1] = (y - (LEN / 1)) / (LEN / 1);
	x = 0;
	y = 0;
	while (y < LEN * 2 && y < img_y)
	{
		while (x < LEN * 2 && x < img_x)
		{
			jul_bar(x, y, c, data);
			x++;
		}
		x = 0;
		y++;
	}
}

int		my_mouse(int x, int y, void *data)
{
	t_data	*s;
	char	*str;
	void	*fctptr2;

	fctptr2 = &(my_mouse2);
	s = data;
	str = s->img_str;
	jul_foo(data, (x), (y), str);
	mlx_clear_window(s->mlx, s->win);
	mlx_put_image_to_window(s->mlx, s->win, s->ptr_img, 0, 0);
	return (0);
}

int		julia(void)
{
	void	*mlx;
	void	*win;
	char	*img_str;
	t_data	*data;
	void	*fctptr[2];

	fctptr[0] = &(my_mouse);
	fctptr[1] = &(my_mouse2);
	mlx = mlx_init();
	win = mlx_new_window(mlx, LEN, LEN, "fract");
	data = fill_data(mlx, win, create_img(mlx, &img_str), img_str);
	jul_foo(data, 1, 2, img_str);
	mlx_put_image_to_window(mlx, win, data->ptr_img, 0, 0);
	mlx_key_hook(win, my_key_ft, data);
	mlx_mouse_hook(win, fctptr[1], data);
	mlx_hook(win, MOTIONNOTIFY, POINTERMOTIONMASK, fctptr[0], data);
	mlx_loop(mlx);
	return (0);
}
