/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 12:28:23 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/12 15:59:59 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	store_fc(t_data *data, int i, char *line)
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;

	red = ft_atoi_parsing(&line[i], &i);
	i++;
	green = ft_atoi_parsing(&line[i], &i);
	i++;
	blue = ft_atoi_parsing(&line[i], &i);
	if (line[0] == 'F')
	{
		data->floor = store_color(0, red, green, blue);
		data->security[1] += 1;
	}
	else
	{
		data->ceiling = store_color(0, red, green, blue);
		data->security[2] += 1;
	}
}

void	store_rfc(t_data *data, char *line)
{
	int i;

	i = 1;
	if (line[0] == 'R')
	{
		data->x_screen_size = ft_atoi_parsing(&line[i], &i);
		while (line[i] != ' ')
			i++;
		data->y_screen_size = ft_atoi(&line[i]);
		data->security[0] += 1;
	}
	else
		store_fc(data, i, line);
}

void	store_nswe(t_data *data, char *line)
{
	int i;

	i = 3;
	while (line[i] == ' ')
		i++;
	if (line[0] == 'N')
	{
		data->no = ft_strdup(&line[i]);
		data->security[4] += 1;
	}
	else if (line[0] == 'S')
	{
		data->so = ft_strdup(&line[i]);
		data->security[5] += 1;
	}
	else if (line[0] == 'W')
	{
		data->we = ft_strdup(&line[i]);
		data->security[6] += 1;
	}
	else if (line[0] == 'E')
	{
		data->ea = ft_strdup(&line[i]);
		data->security[7] += 1;
	}
}

void	store_path(t_data *data, char *line)
{
	int i;

	if (line[0] == 'S' && line[1] == ' ')
	{
		i = 2;
		while (line[i] == ' ')
			i++;
		data->sprite = ft_strdup(&line[i]);
		data->security[3] += 1;
	}
	else
		store_nswe(data, line);
}

void	store_info(int fd, t_data *data, char *line)
{
	int retour;

	while ((retour = get_next_line(fd, &line)) == 1)
	{
		ft_putstr_bn(line);
		if ((line[0] == 'R' || line[0] == 'F' || line[0] == 'C')
			&& line[1] == ' ')
			store_rfc(data, line);
		if ((line[0] == 'S' && line[1] == ' ') || (((line[0] == 'N' &&
			line[1] == 'O') || (line[0] == 'S' && line[1] == 'O') ||
			(line[0] == 'W' && line[1] == 'E') || (line[0] == 'E' &&
			line[1] == 'A')) && line[2] == ' '))
			store_path(data, line);
		free(line);
		if (data->security[0] == 1 && data->security[1] == 1 &&
		data->security[2] == 1 && data->security[3] == 1 &&
		data->security[4] == 1 && data->security[5] == 1 &&
		data->security[6] == 1 && data->security[7] == 1)
			break ;
	}
}
