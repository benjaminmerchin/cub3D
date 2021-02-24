/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:45:12 by bmerchin          #+#    #+#             */
/*   Updated: 2021/02/24 15:45:13 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_images_bonus(t_data *data)
{
	if (!BONUS)
		return ;
	data->text[5].img = mlx_xpm_file_to_image(data->mlx, data->text[5].path,
	&data->text[5].width, &data->text[5].height);
	data->text[6].img = mlx_xpm_file_to_image(data->mlx, data->text[6].path,
	&data->text[6].width, &data->text[1].height);
	data->text[5].add = mlx_get_data_addr(data->text[5].img,
	&data->text[5].bits_per_pixel, &data->text[5].line_length,
	&data->text[5].endian);
	data->text[6].add = mlx_get_data_addr(data->text[6].img,
	&data->text[6].bits_per_pixel, &data->text[6].line_length,
	&data->text[6].endian);
}
