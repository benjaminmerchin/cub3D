/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_mlx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:15:14 by bmerchin          #+#    #+#             */
/*   Updated: 2021/02/23 11:15:15 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

    dst = data->addr + (y * data->line_length + x * 4);
    *(unsigned int*)dst = color;
}

void	sort_sprite(t_data *data)
{
	int i;
	int j;

	i = -1;
	while (++i < data->sprite_num)
	{
		j = i;
		while (++j < data->sprite_num)
		{
			if (data->sprite[i][3] < data->sprite[j][3])
			{
				data->sprite[500][0] = data->sprite[i][0];
				data->sprite[500][1] = data->sprite[i][1];
				data->sprite[500][2] = data->sprite[i][2];
				data->sprite[500][3] = data->sprite[i][3];
				data->sprite[i][0] = data->sprite[j][0];
				data->sprite[i][1] = data->sprite[j][1];
				data->sprite[i][2] = data->sprite[j][2];
				data->sprite[i][3] = data->sprite[j][3];
				data->sprite[j][0] = data->sprite[500][0];
				data->sprite[j][1] = data->sprite[500][1];
				data->sprite[j][2] = data->sprite[500][2];
				data->sprite[j][3] = data->sprite[500][3];
			}
		}
	}
}
