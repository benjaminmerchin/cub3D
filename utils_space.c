/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_space.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 15:04:59 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/09 18:31:18 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_vector_dir_extension(t_data *data)
{
	if (data->start_dir == 'W')
	{
		data->x_dir = -1;
		data->y_dir = 0;
		data->x_plane = 0;
		data->y_plane = -0.66;
	}
}
