/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 13:48:47 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/12 15:32:13 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_info(t_data *data)
{
	printf("\nYour Map is Correct\n");
	printf("------------------------------\n");
	printf("Screen Size x : %hu\n", data->x_screen_size);
	printf("Screen Size y : %hu\n", data->y_screen_size);
	printf("Floor Color : %d\n", data->floor);
	printf("Ceiling Color : %d\n", data->ceiling);
	printf("------------------------------\n");
	printf("Sprite Texture Path : %s\n", data->sprite.path);
	printf("NO Texture Path : %s\n", data->no.path);
	printf("SO Texture Path : %s\n", data->so.path);
	printf("WE Texture Path : %s\n", data->we.path);
	printf("EA Texture Path : %s\n", data->ea.path);
	printf("------------------------------\n");
	printf("X Position : %f\n", data->x_pos);
	printf("Y Position : %f\n", data->y_pos);
	printf("Starting Direction : %c\n", data->start_dir);
	printf("X Map Size : %d\n", data->x_map);
	printf("Y Map Size : %d\n", data->y_map);
}

int free_struct(t_data *data, int m)
{
	int i;

	i = 0;
	free(data->sprite.path);
	free(data->no.path);
	free(data->so.path);
	free(data->we.path);
	free(data->ea.path);
	if (m == 1)
	{
		while (i < data->y_map)
		{
			free(data->map[i]);
			i++;
		}
	}
	return (0);
}
