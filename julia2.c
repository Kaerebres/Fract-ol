/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:23:00 by csimon            #+#    #+#             */
/*   Updated: 2017/06/13 11:23:01 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx_macos/mlx.h"
#include "fractol.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "cudju.h"
#include <string.h>
#include <math.h>
#define MOTIONNOTIFY 6
#define POINTERMOTIONMASK (1L<<6)
#include <stdio.h>

int		my_mouse(int x, int y, void *data)
{
	t_data		*swp;
	char		*str;

	swp = data;
	if (swp->stop == 1)
	{
		str = swp->img_str;
		callcuda_ju(data, x, y);
		mlx_clear_window(swp->mlx, swp->win);
		mlx_put_image_to_window(swp->mlx, swp->win, swp->ptr_img, 0, 0);
	}
	return (0);
}

int		my_mouse5(int button, int x, int y, void *data)
{
	t_data	*swp;
	char	*str;

	swp = data;
	if (button == 1)
		swp->stop = 1;
	if (button == 2)
	{
		swp->stop = 0;
		swp->xs = x;
		swp->ys = y;
	}
	if (button == 5)
		make_zoom(x, y, data);
	if (button == 4)
		make_dezoom(x, y, data);
	str = swp->img_str;
	if (swp->stop == 0)
		callcuda_ju(data, (swp->xs), (swp->ys));
	else
		callcuda_ju(data, (x), (y));
	mlx_clear_window(swp->mlx, swp->win);
	mlx_put_image_to_window(swp->mlx, swp->win, swp->ptr_img, 0, 0);
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
	fctptr[1] = &(my_mouse5);
	mlx = mlx_init();
	win = mlx_new_window(mlx, LEN, LEN, "fract");
	data = fill_data(mlx, win, create_img(mlx, &img_str), img_str);
	data->img_str = callcuda_ju(data, (LEN / 2), (LEN / 2));
	mlx_put_image_to_window(mlx, win, data->ptr_img, 0, 0);
	mlx_key_hook(win, my_key_ft, data);
	mlx_mouse_hook(win, fctptr[1], data);
	mlx_hook(win, MOTIONNOTIFY, POINTERMOTIONMASK, fctptr[0], data);
	mlx_loop(mlx);
	return (0);
}
