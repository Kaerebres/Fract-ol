/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cudju.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/16 17:14:12 by csimon            #+#    #+#             */
/*   Updated: 2017/06/16 17:14:16 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUDJU_H
# define CUDJU_H
# include "fractol.h"

char	*callcuda_ju(t_data *data, float x, float y);
char	*callcuda_mand(t_data *data, float x, float y);
char	*callcuda_ship(t_data *data, float x, float y);
char	*callcuda_arrow(t_data *data, float x, float y);
char	*callcuda_shroom(t_data *data, float x, float y);

#endif
