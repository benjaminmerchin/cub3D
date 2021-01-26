/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_initialize_struct.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:47:55 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/26 15:47:57 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    set_vector_dir_extension(t_data *data)
{
    if (data->start_dir == 'W')
	{
		data->x_dir = 0;
		data->y_dir = -1;
		data->x_plane = -0.66;
		data->y_plane = 0;
	}
}

void	set_vector_dir(t_data *data)
{
	if (data->start_dir == 'N')
	{
		data->x_dir = -1;
		data->y_dir = 0;
		data->x_plane = 0;
		data->y_plane = 0.66;
	}
	if (data->start_dir == 'S')
	{
		data->x_dir = 1;
		data->y_dir = 0;
		data->x_plane = 0;
		data->y_plane = -0.66;
	}
	if (data->start_dir == 'E')
	{
		data->x_dir = 0;
		data->y_dir = 1;
		data->x_plane = 0.66;
		data->y_plane = 0;
	}
	set_vector_dir_extension(data);
}
