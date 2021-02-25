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

void	initialize_heart(t_data *data)
{
	int i;
	int j;
	int tab[11][11] = {{0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0},
	{0, 1, 2, 2, 1, 0, 1, 2, 2, 1, 0},
	{1, 2, 3, 4, 2, 1, 2, 4, 4, 2, 1},
	{1, 2, 3, 4, 4, 2, 4, 4, 4, 2, 1},
	{1, 2, 4, 4, 4, 4, 4, 4, 4, 2, 1},
	{1, 2, 4, 4, 4, 4, 4, 4, 4, 2, 1},
	{0, 1, 2, 4, 4, 4, 4, 4, 2, 1, 0},
	{0, 0, 1, 2, 4, 4, 4, 2, 1, 0, 0},
	{0, 0, 0, 1, 2, 4, 2, 1, 0, 0, 0},
	{0, 0, 0, 0, 1, 2, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}};

	i = 0;
	j = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 11)
		{
			if (tab[j][i] == 0)
				data->heart[j][i] = 0;
			else if (tab[j][i] == 1)
				data->heart[j][i] = 131072;
			else if (tab[j][i] == 2)
				data->heart[j][i] = 10944515;
			else if (tab[j][i] == 3)
				data->heart[j][i] = 16709366;
			else if (tab[j][i] == 4)
				data->heart[j][i] = 15269892;
			//ft_putnbr_fd(data->heart[j][i], 1);
			j++;
		}
		i++;
	}
}

void	init_images_bonus(t_data *data)
{
	if (!BONUS)
		return ;
	data->text[5].img = mlx_xpm_file_to_image(data->mlx, data->text[5].path,
	&data->text[5].width, &data->text[5].height);
	data->text[6].img = mlx_xpm_file_to_image(data->mlx, data->text[6].path,
	&data->text[6].width, &data->text[6].height);
	data->text[7].img = mlx_xpm_file_to_image(data->mlx, data->text[7].path,
	&data->text[7].width, &data->text[7].height);
	data->text[8].img = mlx_xpm_file_to_image(data->mlx, data->text[8].path,
	&data->text[8].width, &data->text[8].height);
	data->text[5].add = mlx_get_data_addr(data->text[5].img,
	&data->text[5].bits_per_pixel, &data->text[5].line_length,
	&data->text[5].endian);
	data->text[6].add = mlx_get_data_addr(data->text[6].img,
	&data->text[6].bits_per_pixel, &data->text[6].line_length,
	&data->text[6].endian);
	data->text[7].add = mlx_get_data_addr(data->text[7].img,
	&data->text[7].bits_per_pixel, &data->text[7].line_length,
	&data->text[7].endian);
	data->text[8].add = mlx_get_data_addr(data->text[8].img,
	&data->text[8].bits_per_pixel, &data->text[8].line_length,
	&data->text[8].endian);
}
