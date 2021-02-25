/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 10:53:02 by bmerchin          #+#    #+#             */
/*   Updated: 2021/02/23 10:53:04 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	add_lifebar(t_data *data)
{
	int i;
	int j;
	int k;
	int a;
	int b;

	k = 0;
	b = 10;
	a = data->y_screen_size - 21;
	if (data->x_screen_size < 200 || data->y_screen_size < 50)
		return ;
	while (k < data->life)
	{
		i = 0;
		while (i < 11)
		{
			j = 0;
			while (j < 11)
			{
				if (data->heart[i][j] != 0)
					ft_mlx_pixel_put(data, j + b, a + i, data->heart[i][j]);
				j++;
			}
			i++;
		}
		b += 15;
		k++;
	}
}

void	add_direction(t_data *data)
{
	int a;

	a = 0;
	while (a < MINIMAP_SIZE)
	{
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + data->x_dir * a,
		data->y_pos * MINIMAP_SIZE + data->y_dir * a, 16777215);
		a++;
	}
}

void	add_player(t_data *data)
{
	ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE,
	data->y_pos * MINIMAP_SIZE, 16711680);
	if (MINIMAP_SIZE > 4)
	{
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE - 1,
		data->y_pos * MINIMAP_SIZE - 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE,
		data->y_pos * MINIMAP_SIZE - 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + 1,
		data->y_pos * MINIMAP_SIZE - 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE - 1,
		data->y_pos * MINIMAP_SIZE, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + 1,
		data->y_pos * MINIMAP_SIZE, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE - 1,
		data->y_pos * MINIMAP_SIZE + 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE,
		data->y_pos * MINIMAP_SIZE + 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + 1,
		data->y_pos * MINIMAP_SIZE + 1, 16711680);
		add_direction(data);
	}
}

void	add_minimap_and_company(t_data *data)
{
	int i;
	int j;
	int k;
	int pixel;

	i = 0;
	pixel = MINIMAP_SIZE * MINIMAP_SIZE;
	while (i < data->y_map && i * MINIMAP_SIZE < data->y_screen_size)
	{
		j = 0;
		while (j < data->x_map && j * MINIMAP_SIZE < data->x_screen_size)
		{
			k = -1;
			while (++k < pixel)
				ft_mlx_pixel_put(data, j * MINIMAP_SIZE + k / MINIMAP_SIZE,
				i * MINIMAP_SIZE + k % MINIMAP_SIZE,
				(data->map[i][j] - '0') * 100000);
			j++;
		}
		i++;
	}
	add_player(data);
	add_lifebar(data);
	//add_hud(data);
}
