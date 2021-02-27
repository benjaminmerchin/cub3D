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

void	put_sprite_id(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	(void)data;
	while (i < data->sprite_num)
	{
		if (data->map[(int)data->sprite[i][1]][(int)data->sprite[i][0]] == 'j')
			data->sprite[i][4] = 12;
		i++;
	}
}

void	init_images_bonus(t_data *data)
{
	int i;
	
	if (!BONUS)
		return ;
	i = 5;
	while (i < 5 + NUM_SPRITE_BOMUS) //NUM_SPRITE_BOMUS = 4 pour l'instant
	{
		data->text[i].img = mlx_xpm_file_to_image(data->mlx, data->text[i].path,
		&data->text[i].width, &data->text[i].height);
		data->text[i].add = mlx_get_data_addr(data->text[i].img,
		&data->text[i].bits_per_pixel, &data->text[i].line_length,
		&data->text[i].endian);
		i++;
	}
	put_sprite_id(data);
}
