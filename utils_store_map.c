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

	red = ft_atoi_parsing(line, &i);
	i++;
	green = ft_atoi_parsing(line, &i);
	i++;
	blue = ft_atoi_parsing(line, &i);
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
		data->text[0].path = ft_strdup(&line[i]);
		data->security[4] += 1;
	}
	else if (line[0] == 'S')
	{
		data->text[1].path = ft_strdup(&line[i]);
		data->security[5] += 1;
	}
	else if (line[0] == 'W')
	{
		data->text[3].path = ft_strdup(&line[i]);
		data->security[6] += 1;
	}
	else if (line[0] == 'E')
	{
		data->text[2].path = ft_strdup(&line[i]);
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
		data->text[4].path = ft_strdup(&line[i]);
		data->security[3] += 1;
	}
	else if ((is_in(line[0], "TUVWabcdefghklmn")) && line[1] == ' ')
	{
		i = 2;
		while (line[i] == ' ')
			i++;
		data->security[3] += 1;
		//write(1, "AAAAA BBBBB", 11);
		if (line[0] == 'T')
			data->text[5].path = ft_strdup(&line[i]);
		else if (line[0] == 'U')
			data->text[6].path = ft_strdup(&line[i]);
		else if (line[0] == 'V')
			data->text[7].path = ft_strdup(&line[i]);
		else if (line[0] == 'W')
			data->text[8].path = ft_strdup(&line[i]);
		else if (line[0] == 'a')
			data->text[9].path = ft_strdup(&line[i]);
		else if (line[0] == 'b')
			data->text[10].path = ft_strdup(&line[i]);
		else if (line[0] == 'c')
			data->text[11].path = ft_strdup(&line[i]);
		else if (line[0] == 'd')
			data->text[12].path = ft_strdup(&line[i]);
		else if (line[0] == 'e')
			data->text[13].path = ft_strdup(&line[i]);
		else if (line[0] == 'f')
			data->text[14].path = ft_strdup(&line[i]);
		else if (line[0] == 'g')
			data->text[15].path = ft_strdup(&line[i]);
		else if (line[0] == 'h')
			data->text[16].path = ft_strdup(&line[i]);
		else if (line[0] == 'k')
			data->text[17].path = ft_strdup(&line[i]);
		else if (line[0] == 'l')
			data->text[18].path = ft_strdup(&line[i]);
		else if (line[0] == 'm')
			data->text[19].path = ft_strdup(&line[i]);
		else if (line[0] == 'n')
			data->text[20].path = ft_strdup(&line[i]);
	}
	else
		store_nswe(data, line);
}

void	store_info(int fd, t_data *data, char *line)
{
	int retour;

	data->sprite_num = 0;
	while ((retour = get_next_line(fd, &line)) == 1)
	{
		ft_putstr_bn(line);
		if ((line[0] == 'R' || line[0] == 'F' || line[0] == 'C')
			&& line[1] == ' ')
			store_rfc(data, line);
		else if ((line[0] == 'S' && line[1] == ' ') || (is_in(line[0], "TUVWabcdefghklmn") &&
			line[1] == ' ' && BONUS) || (((line[0] == 'N' &&
			line[1] == 'O') || (line[0] == 'S' && line[1] == 'O') ||
			(line[0] == 'W' && line[1] == 'E') || (line[0] == 'E' &&
			line[1] == 'A')) && line[2] == ' '))
			store_path(data, line);
		else
		{
			if (line[0] != 0)
				break ;
		}
		free(line);
		if (data->security[0] == 1 && data->security[1] == 1 &&
		data->security[2] == 1 && data->security[3] == 1 + NUM_SPRITE_BOMUS * BONUS &&
		data->security[4] == 1 && data->security[5] == 1 &&
		data->security[6] == 1 && data->security[7] == 1)
			break ;
	}
}
