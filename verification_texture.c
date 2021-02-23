/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 11:05:36 by bmerchin          #+#    #+#             */
/*   Updated: 2021/02/23 11:05:38 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	open_then_read(char *str, t_data *data)
{
	int fd;

	fd = open(str, O_RDONLY); //attention aux ouvertures multiples ?
	if (fd == -1)
	{
		ft_putstr_bn("Error\nWrong texture path");
		data->security[11] = 1;
		return ;
	}
	if (read(fd, NULL, 0) == -1)
	{
		ft_putstr_bn("Error\nWrong texture path");
		data->security[11] = 1;
		return;
	}
}

void	texture_check(t_data *data)
{
	open_then_read(data->text[0].path, data);
	open_then_read(data->text[1].path, data);
	open_then_read(data->text[3].path, data);
	open_then_read(data->text[2].path, data);
	open_then_read(data->text[4].path, data);
	if (data->sprite_num > 499)
	{
		ft_putstr_bn("Error\nToo many sprites (more than 500)");
		data->security[11] = 1;
		return ;
	}
}
