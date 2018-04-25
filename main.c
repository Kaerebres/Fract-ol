/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 12:33:12 by csimon            #+#    #+#             */
/*   Updated: 2017/10/14 13:16:37 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fractol.h"
#include <unistd.h>
#include <stdlib.h>

void	call_fraktal(int type)
{
	if (type == 1)
		julia();
	if (type == 2)
		mandel();
	if (type == 3)
		ship();
	if (type == 4)
		arrow();
	if (type == 5)
		shroom();
}

int		parse_shroom(char **argv)
{
	int		index;
	char	*str;

	str = "Shroom";
	index = 1;
	while (argv[1][index] != '\0')
	{
		if (argv[1][index] != str[index])
			return (0);
		index++;
	}
	return ((ft_strlen(str) == ft_strlen(argv[1]) ? 5 : 0));
}

void	ft_error(int code)
{
	if (code == 0)
		write(1, "Error: no input paramater.\n", 27);
	if (code == 1)
		write(1, "Error: name not recognized.\n", 28);
	write(1, "Usage : ./fractol [Julia/Mandelbrot/Bship/Tricorn/Shroom]\n", 58);
}

int		main(int argc, char **argv)
{
	int		type;

	if (argc < 2)
	{
		ft_error(0);
		return (0);
	}
	type = parse_input(argv);
	if (type == 0)
	{
		ft_error(1);
		return (0);
	}
	call_fraktal(type);
	return (0);
}
