/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/14 12:34:30 by csimon            #+#    #+#             */
/*   Updated: 2017/05/14 12:34:31 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "fractol.h"

int		parse_arrow(char **argv)
{
	int		index;
	char	*str;

	str = "Tricorn";
	index = 1;
	while (argv[1][index] != '\0')
	{
		if (argv[1][index] != str[index])
			return (0);
		index++;
	}
	return ((ft_strlen(str) == ft_strlen(argv[1]) ? 4 : 0));
}

int		parse_julia(char **argv)
{
	int		index;
	char	*str;

	str = "Julia";
	index = 1;
	while (argv[1][index] != '\0')
	{
		if (argv[1][index] != str[index])
			return (0);
		index++;
	}
	return ((ft_strlen(str) == ft_strlen(argv[1]) ? 1 : 0));
}

int		parse_mandel(char **argv)
{
	int		index;
	char	*str;

	str = "Mandelbrot";
	index = 1;
	while (argv[1][index] != '\0')
	{
		if (argv[1][index] != str[index])
			return (0);
		index++;
	}
	return ((ft_strlen(str) == ft_strlen(argv[1]) ? 2 : 0));
}

int		parse_ship(char **argv)
{
	int		index;
	char	*str;

	str = "Bship";
	index = 1;
	while (argv[1][index] != '\0')
	{
		if (argv[1][index] != str[index])
			return (0);
		index++;
	}
	return ((ft_strlen(str) == ft_strlen(argv[1]) ? 3 : 0));
}

int		parse_input(char **argv)
{
	int		type;
	int		index;

	index = 0;
	if (argv[1][0] == 'j' || argv[1][0] == 'J')
		type = parse_julia(argv);
	else if (argv[1][0] == 'm' || argv[1][0] == 'M')
		type = parse_mandel(argv);
	else if (argv[1][0] == 'b' || argv[1][0] == 'B')
		type = parse_ship(argv);
	else if (argv[1][0] == 't' || argv[1][0] == 'T')
		type = parse_arrow(argv);
	else if (argv[1][0] == 's' || argv[1][0] == 'S')
		type = parse_shroom(argv);
	else
		type = 0;
	return (type);
}
