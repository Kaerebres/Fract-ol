/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 12:34:19 by csimon            #+#    #+#             */
/*   Updated: 2017/05/14 12:34:20 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define LEN 1024

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	char	*img_str;
	void	*ptr_img;
	double	zoom;
	double	x1;
	double	y1;
	int		iter_max;
	int		stop;
	int		xs;
	int		ys;
}				t_data;

void			make_zoom(double x, double y, t_data *data);
void			make_dezoom(double x, double y, t_data *data);
int				parse_input(char **argv);
int				julia();
int				mandel();
int				ship();
int				arrow();
int				shroom();
int				parse_shroom(char **argv);
void			img_fill_pixel(char *img_str, int x, int y, int color);
int				my_mouse2(int button, int x, int y, void *data);
t_data			*fill_data(void *mlx, void *win, void *ptr_img, char *img_str);
int				my_key_ft(int keycode, void *param);
void			*create_img(void *mlx, char **img_str);
void			jul_foo(t_data *data, float x, float y, char *img_str);

#endif
