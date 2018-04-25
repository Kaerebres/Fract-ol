/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ship2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 13:08:15 by csimon            #+#    #+#             */
/*   Updated: 2017/06/16 13:08:16 by csimon           ###   ########.fr       */
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

int		my_mouse4(int button, int x, int y, void *data)
{
	t_data	*swp;
	char	*str;

	swp = data;
	if (button == 5)
		make_zoom(x, y, data);
	if (button == 4)
		make_dezoom(x, y, data);
	str = swp->img_str;
	callcuda_ship(data, (x), (y));
	mlx_clear_window(swp->mlx, swp->win);
	mlx_put_image_to_window(swp->mlx, swp->win, swp->ptr_img, 0, 0);
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
	callcuda_ship(data, (LEN / 2), (LEN / 2));
	mlx_put_image_to_window(mlx, win, data->ptr_img, 0, 10);
	mlx_key_hook(win, my_key_ft, data);
	mlx_mouse_hook(win, fctptr, data);
	mlx_loop(mlx);
	return (0);
}
