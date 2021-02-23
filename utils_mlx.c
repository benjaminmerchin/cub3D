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
	char	*dst;

	dst = data->addr + (y * data->line_length + x * 4);
	*(unsigned int*)dst = color;
}

void	switch_data_sprite(t_data *data, int i, int j)
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
				switch_data_sprite(data, i, j);
		}
	}
}

void	sprite_dist_calc(t_data *data)
{
	int i;

	i = 0;
	while (i < data->sprite_num)
	{
		data->sprite[i][3] = ((data->x_pos - data->sprite[i][0]) *
		(data->x_pos - data->sprite[i][0]) + (data->y_pos - data->sprite[i][1])
		* (data->y_pos - data->sprite[i][1]));
		i++;
	}
}

void	init_images_mlx(t_data *data)
{
	data->text[0].img = mlx_xpm_file_to_image(data->mlx, data->text[0].path,
	&data->text[0].width, &data->text[0].height);
	data->text[1].img = mlx_xpm_file_to_image(data->mlx, data->text[1].path,
	&data->text[1].width, &data->text[1].height);
	data->text[2].img = mlx_xpm_file_to_image(data->mlx, data->text[2].path,
	&data->text[2].width, &data->text[2].height);
	data->text[3].img = mlx_xpm_file_to_image(data->mlx, data->text[3].path,
	&data->text[3].width, &data->text[3].height);
	data->text[4].img = mlx_xpm_file_to_image(data->mlx, data->text[4].path,
	&data->text[4].width, &data->text[4].height);
	data->text[0].add = mlx_get_data_addr(data->text[0].img,
	&data->text[0].bits_per_pixel, &data->text[0].line_length,
	&data->text[0].endian);
	data->text[1].add = mlx_get_data_addr(data->text[1].img,
	&data->text[1].bits_per_pixel, &data->text[1].line_length,
	&data->text[1].endian);
	data->text[2].add = mlx_get_data_addr(data->text[2].img,
	&data->text[2].bits_per_pixel, &data->text[2].line_length,
	&data->text[2].endian);
	data->text[3].add = mlx_get_data_addr(data->text[3].img,
	&data->text[3].bits_per_pixel, &data->text[3].line_length,
	&data->text[3].endian);
	data->text[4].add = mlx_get_data_addr(data->text[4].img,
	&data->text[4].bits_per_pixel, &data->text[4].line_length,
	&data->text[4].endian);
}
