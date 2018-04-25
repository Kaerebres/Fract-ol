/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/13 11:22:22 by csimon            #+#    #+#             */
/*   Updated: 2017/06/13 11:22:26 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cudju.h"
#include "fractol.h"
#include "minilibx_macos/mlx.h"
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

void	img_fill_pixel(char *img_str, int x, int y, int color)
{
	int		pixel;

	pixel = x * 4 + (y * LEN * 4) * 2;
	img_str[pixel] = color;
	img_str[pixel + 1] = color / 3;
	img_str[pixel + 2] = 0;
}

int		my_mouse2(int button, int x, int y, void *data)
{
	t_data	*swp;
	char	*str;

	swp = data;
	if (button == 5)
		swp->zoom *= 1.1;
	if (button == 4)
		swp->zoom *= 0.9;
	str = swp->img_str;
	callcuda_ju(data, (x), (y));
	mlx_clear_window(swp->mlx, swp->win);
	mlx_put_image_to_window(swp->mlx, swp->win, swp->ptr_img, 0, 0);
	return (0);
}

t_data	*fill_data(void *mlx, void *win, void *ptr_img, char *img_str)
{
	t_data	*new;

	new = NULL;
	new = (t_data*)malloc(sizeof(t_data));
	new->mlx = mlx;
	new->win = win;
	new->ptr_img = ptr_img;
	new->img_str = img_str;
	new->zoom = 250;
	new->iter_max = 150;
	new->x1 = -2.1;
	new->y1 = -2.1;
	new->stop = 1;
	new->xs = 500;
	new->ys = 500;
	return (new);
}

int		my_key_ft(int keycode, void *param)
{
	t_data	*tmp;

	tmp = param;
	if (keycode == 53)
	{
		mlx_destroy_window(tmp->mlx, tmp->win);
		free(param);
		exit(0);
	}
	return (0);
}

void	*create_img(void *mlx, char **img_str)
{
	void	*ptr_img;
	int		bpp;
	int		s_l;
	int		endian;

	ptr_img = mlx_new_image(mlx, LEN * 2, LEN * 2);
	*img_str = mlx_get_data_addr(ptr_img, &(bpp), &(s_l), &(endian));
	return (ptr_img);
}
