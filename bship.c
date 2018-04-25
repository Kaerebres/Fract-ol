/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bship.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:22:33 by csimon            #+#    #+#             */
/*   Updated: 2017/06/13 11:22:34 by csimon           ###   ########.fr       */
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

void	ship_bar(float x, float y, float *c, t_data *data)
{
	float	zr;
	float	zi;
	int		i;
	float	tmp;

	zr = 0;
	zi = 0;
	i = 0;
	while (sqrtf(zr * zr + zi * zi) < 4 && i < 50)
	{
		tmp = zr;
		zr = zr * zr - zi * zi + c[0];
		zi = 2 * fabsf(zi * tmp) + c[1];
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

void	ship_foo(t_data *data, float x, float y, char *img_str)
{
	float	c[2];
	float	img_x;
	float	img_y;

	img_x = 3.1 - ((3.1 / LEN) * x);
	img_y = 3.1 - ((3.1 / LEN) * y);
	if (!img_str)
		x++;
	c[0] = (x - (LEN / 2)) / (LEN / 2);
	c[1] = (y - (LEN / 2)) / (LEN / 2);
	x = 0;
	y = 0;
	while (y < LEN * 2)
	{
		while (x < LEN * 2)
		{
			c[0] = x / data->zoom - img_x;
			c[1] = y / data->zoom - img_y;
			ship_bar(x, y, c, data);
			x++;
		}
		x = 0;
		y++;
	}
}

int		my_mouse4(int button, int x, int y, void *data)
{
	t_data	*s;
	char	*str;

	s = data;
	if (button == 5)
		s->zoom *= 1.1;
	if (button == 4)
		s->zoom *= 0.9;
	str = s->img_str;
	ship_foo(data, (x), (y), str);
	mlx_clear_window(s->mlx, s->win);
	mlx_put_image_to_window(s->mlx, s->win, s->ptr_img, 0, 0);
	return (0);
}

int		ship(void)
{
	void	*mlx;
	void	*win;
	char	*img_str;
	t_data	*data;
	void	*fctptr;

	fctptr = &(my_mouse4);
	mlx = mlx_init();
	win = mlx_new_window(mlx, LEN, LEN, "fract");
	data = fill_data(mlx, win, create_img(mlx, &img_str), img_str);
	ship_foo(data, (LEN / 2), (LEN / 2), img_str);
	mlx_put_image_to_window(mlx, win, data->ptr_img, 0, 10);
	mlx_key_hook(win, my_key_ft, data);
	mlx_mouse_hook(win, fctptr, data);
	mlx_loop(mlx);
	return (0);
}
