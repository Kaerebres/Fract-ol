/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandalgo2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:08:08 by csimon            #+#    #+#             */
/*   Updated: 2017/06/16 13:08:10 by csimon           ###   ########.fr       */
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
#include "cudju.h"

void	make_zoom(double x, double y, t_data *data)
{
	double			converted_i;
	double			converted_r;

	if (y > 0)
	{
		converted_r = (x / data->zoom) + data->x1;
		converted_i = (y / data->zoom) + data->y1;
		data->zoom *= 1.1;
		data->iter_max += 5;
		data->x1 = converted_r - (x / data->zoom);
		data->y1 = converted_i - (y / data->zoom);
	}
}

void	make_dezoom(double x, double y, t_data *data)
{
	double			converted_i;
	double			converted_r;

	if (y > 0)
	{
		converted_r = (x / data->zoom) + data->x1;
		converted_i = (y / data->zoom) + data->y1;
		data->zoom /= 1.1;
		data->iter_max -= 5;
		data->x1 = converted_r - (x / data->zoom);
		data->y1 = converted_i - (y / data->zoom);
	}
}

int		my_mouse3(int button, int x, int y, void *data)
{
	t_data	*s;
	char	*str;

	s = data;
	if (button == 5)
		make_zoom(x, y, data);
	if (button == 4)
		make_dezoom(x, y, data);
	str = s->img_str;
	callcuda_mand(s, x, y);
	mlx_clear_window(s->mlx, s->win);
	mlx_put_image_to_window(s->mlx, s->win, s->ptr_img, 0, 0);
	return (0);
}

int		mandel(void)
{
	void	*mlx;
	void	*win;
	char	*img_str;
	t_data	*data;
	void	*fctptr;

	fctptr = &(my_mouse3);
	mlx = mlx_init();
	win = mlx_new_window(mlx, LEN, LEN, "fract");
	data = fill_data(mlx, win, create_img(mlx, &img_str), img_str);
	callcuda_mand(data, (LEN / 3), (LEN / 3));
	mlx_put_image_to_window(mlx, win, data->ptr_img, 0, 0);
	mlx_key_hook(win, my_key_ft, data);
	mlx_mouse_hook(win, fctptr, data);
	mlx_loop(mlx);
	return (0);
}
