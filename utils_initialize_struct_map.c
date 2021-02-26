/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_initialize_struct_map.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 15:47:55 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/26 15:47:57 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	intialize_struct(t_data *data)
{
	int i;

	i = -1;
	data->forward = 0;
	data->backward = 0;
	data->right = 0;
	data->left = 0;
	data->turn_right = 0;
	data->turn_left = 0;
	data->hit = 0;
	data->frame = 0;
	data->crouch = 0;
	data->escape = 0;
	data->exit = 0;
	data->time = 0;
	data->life = 30;
	data->sprint = 0;
	data->door = 0;
	data->v_bool_print_score = 0;
	initialize_the_end(data);
	while (++i < 500)
		data->sprite[i][4] = 0;
	i = -1;
	if (BONUS)
	{
		while (++i < 500)
			data->sprite[i][4] = (i + 11) % 12;
		initialize_heart(data);
	}
}

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

void	set_vector_dir(t_data *data)
{
	if (data->start_dir == 'N')
	{
		data->x_dir = 0;
		data->y_dir = -1;
		data->x_plane = 0.66;
		data->y_plane = 0;
	}
	if (data->start_dir == 'S')
	{
		data->x_dir = 0;
		data->y_dir = 1;
		data->x_plane = -0.66;
		data->y_plane = 0;
	}
	if (data->start_dir == 'E')
	{
		data->x_dir = 1;
		data->y_dir = 0;
		data->x_plane = 0;
		data->y_plane = 0.66;
	}
	set_vector_dir_extension(data);
	intialize_struct(data);
}

char	*str_fill(char *str, int len, t_data *data)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = -1;
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + len + 1))))
	{
		data->security[11] = 1;
		ft_putstr_bn("Error\nA malloc failed");
		return (str);
	}
	while (str[i])
	{
		if (str[i] == ' ')
			new[i] = '1';
		else
			new[i] = str[i];
		i++;
	}
	while (++j < len)
		new[i + j] = '1';
	new[i + j] = '\0';
	free(str);
	return (new);
}

void	fill_map_one(t_data *data)
{
	int i;

	i = 0;
	data->x_map = 0;
	while (i < data->y_map)
	{
		if (ft_strlen(data->map[i]) > data->x_map)
			data->x_map = ft_strlen(data->map[i]);
		i++;
	}
	i = 0;
	while (i < data->y_map)
	{
		data->map[i] = str_fill(data->map[i],
		data->x_map - ft_strlen(data->map[i]), data);
		i++;
	}
}
