/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:56:04 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/12 16:17:14 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_wall2(t_data *data, int x, int y, int start_x)
{
	while (x + 1 < ft_strlen(data->map[y]))
	{
		x++;
		if (data->map[y][x] == '1')
			break ;
		else if (data->map[y][x] == ' ' || x + 1 == ft_strlen(data->map[y]))
		{
			data->security[9] = data->security[9] + 1;
			break ;
		}
	}
	x = start_x;
	while (x - 1 >= 0)
	{
		x--;
		if (data->map[y][x] == '1')
			break ;
		else if (data->map[y][x] == ' ' || x == 0)
		{
			data->security[9] = data->security[9] + 1;
			break ;
		}
	}
}

void	find_wall3(t_data *data, int x, int y)
{
	while (y + 1 <= data->y_map)
	{
		y++;
		if (data->map[y][x] == '1')
			break ;
		else if (data->map[y][x] == ' ' || y == data->y_map ||
		ft_strlen(data->map[y + 1]) <= x)
		{
			data->security[9] = data->security[9] + 1;
			break ;
		}
	}
}

void	find_wall(t_data *data, int x, int y)
{
	int start_x;
	int start_y;

	if (data->map[y][x] == '2')
		store_sprite(data, x, y);
	start_x = x;
	start_y = y;
	find_wall2(data, x, y, start_x);
	x = start_x;
	while (y - 1 >= 0)
	{
		y--;
		if (data->map[y][x] == '1')
			break ;
		else if (data->map[y][x] == ' ' || y == 0 ||
		ft_strlen(data->map[y - 1]) <= x)
		{
			data->security[9] = data->security[9] + 1;
			break ;
		}
	}
	y = start_y;
	find_wall3(data, x, y);
}

void	check_map2(t_data *data, int x, int y)
{
	data->start_dir = data->map[y][x];
	data->x_pos = x + 0.5;
	data->y_pos = y + 0.5;
	find_wall(data, x, y);
	data->security[8] = data->security[8] + 1;
}

void	check_map(t_data *data)
{
	int x;
	int y;
	int len;

	y = 0;
	while (y <= data->y_map)
	{
		x = 0;
		len = ft_strlen(data->map[y]);
		while (x < len)
		{
			if (data->map[y][x] == '0' || data->map[y][x] == '2' ||
			data->map[y][x] == '3')
				find_wall(data, x, y);
			else if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
				check_map2(data, x, y);
			else if (data->map[y][x] != ' ' && data->map[y][x] != '1')
				data->security[10] = data->security[10] + 1;
			x++;
		}
		y++;
	}
}
