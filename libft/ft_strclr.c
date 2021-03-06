/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csimon <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/15 14:36:44 by csimon            #+#    #+#             */
/*   Updated: 2016/11/15 14:36:47 by csimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_strclr(char *s)
{
	int		index;

	index = 0;
	if (!s)
		return ;
	while (s[index] != '\0')
	{
		s[index] = '\0';
		index++;
	}
}
