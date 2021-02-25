/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:45:12 by bmerchin          #+#    #+#             */
/*   Updated: 2021/02/24 15:45:13 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	heal_at_spawn(t_data *data)
{
	if (!BONUS)
		return ;
	if (data->map[(int)data->y_pos][(int)data->x_pos] == 'N' ||
	data->map[(int)data->y_pos][(int)data->x_pos] == 'S' ||
	data->map[(int)data->y_pos][(int)data->x_pos] == 'W' ||
	data->map[(int)data->y_pos][(int)data->x_pos] == 'E')
	{
		if (data->life < 10 && data->frame % 5 == 0)
			data->life++;
	}
}
