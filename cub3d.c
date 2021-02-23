/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:56:04 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/12 16:17:14 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
** List data->security possible errors
** security 0 : Resolution
** security 1 : Floor
** security 2 : Ceiling
** security 3 : Sprite
** security 4 : NO
** security 5 : SO
** security 6 : WE
** security 7 : EA
** security 8 : Starting Direction in the map
** security 9 : If there is a missing wall
** security 10 : Wrong character
** security 11 : Texture opening check
*/

/*
** List of textures
** no_0 so_1 ea_2 we_3 sprite_4
*/

void	raycasting_calculation(t_data *data)
{
	int i;

	i = 0;
	while (i < data->x_screen_size)
	{
		raycasting_initialize(data, &i);
	    raycasting_move_until_wall(data);
		raycasting_line_position(data);
		put_column_image(data, i);
		data->buff[i] = data->dist_wall;
		data->hit = 0;
		i++;
	}
	i = -1;
	while (++i < data->sprite_num)
		data->sprite[i][3] = ((data->x_pos - data->sprite[i][0]) * (data->x_pos - data->sprite[i][0]) + (data->y_pos - data->sprite[i][1]) * (data->y_pos - data->sprite[i][1]));
	sort_sprite(data);
	i = 0;
	int j;
	int k;
	int d;
	while (i < data->sprite_num)
	{
		data->x_sprite = data->sprite[i][0] - data->x_pos;
		data->y_sprite = data->sprite[i][1] - data->y_pos;
		data->matrice = 1 / (data->x_plane * data->y_dir - data->x_dir * data->y_plane);
		data->x_trans = data->matrice * (data->y_dir * data->x_sprite - data->x_dir * data->y_sprite);
		data->y_trans = data->matrice * (-data->y_plane * data->x_sprite + data->x_plane * data->y_sprite);
		data->x_sprscr = (int)((data->x_screen_size / 2) * (1 + data->x_trans / data->y_trans));
		data->h_sprite = abs((int)(data->y_screen_size / data->y_trans));
		data->y_drawstart = -data->h_sprite / 2 + data->y_screen_size / 2;
		if (data->y_drawstart < 0)
			data->y_drawstart = 0;
		data->y_drawend = data->h_sprite / 2 + data->y_screen_size / 2;
		if (data->y_drawend >= data->y_screen_size)
			data->y_drawend = data->y_screen_size;
		data->w_sprite = abs((int)(data->y_screen_size / data->y_trans));
		data->x_drawstart = -data->w_sprite / 2 + data->x_sprscr;
		if (data->x_drawstart < 0)
			data->x_drawstart = 0;
		data->x_drawend = data->w_sprite / 2 + data->x_sprscr;
		if (data->x_drawend >= data->x_screen_size)
			data->x_drawend = data->x_screen_size;
		j = data->x_drawstart;
		while(j < data->x_drawend)
		{
			data->x_tex = (int)(256 * (j - (-data->w_sprite / 2 + data->x_sprscr)) * data->text[4].width / data->w_sprite) / 256;
			if (data->y_trans > 0 && j >= 0 && j < data->x_screen_size && data->y_trans < data->buff[j])
			{
				k = data->y_drawstart;
				while (k < data->y_drawend)
				{
					d = k * 256 - data->y_screen_size * 128 + data->h_sprite * 128;
					data->y_tex = ((d * data->text[4].height) / data->h_sprite) / 256;
					if (*(unsigned int *)(data->text[4].add + data->text[4].line_length * data->y_tex + data->x_tex * 4) != 0)
						*(unsigned int *)(data->addr + (k * data->line_length + j * 4)) = *(unsigned int *)(data->text[4].add + data->text[4].line_length * data->y_tex + data->x_tex * 4);
					k++;
				}
			}
			j++;
		}
		i++;
	}
	save_image(data);
}

int		render_next_frame(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	move_according_to_key_press(data);
	raycasting_calculation(data);
	if (MINIMAP_SIZE * data->x_map <= data->x_screen_size && MINIMAP_SIZE * data->y_map <= data->y_screen_size)
		add_map_top_left(data);
	data->frame++;
	return (0);
}

void	run_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->x_screen_size, data->y_screen_size, "Among Us in cub3D - A 42 Paris Project - by bmerchin");
	mlx_loop_hook(data->mlx, render_next_frame, data);
	mlx_hook(data->win, 2, 1L<<0, ft_key_hook, data);
	mlx_hook(data->win, 3, 1L<<1, ft_key_unhook, data);
	data->img = mlx_new_image(data->mlx, data->x_screen_size, data->y_screen_size);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
	data->text[0].img = mlx_xpm_file_to_image(data->mlx, data->text[0].path, &data->text[0].width, &data->text[0].height);
	data->text[1].img = mlx_xpm_file_to_image(data->mlx, data->text[1].path, &data->text[1].width, &data->text[1].height);
	data->text[2].img = mlx_xpm_file_to_image(data->mlx, data->text[2].path, &data->text[2].width, &data->text[2].height);
	data->text[3].img = mlx_xpm_file_to_image(data->mlx, data->text[3].path, &data->text[3].width, &data->text[3].height);
	data->text[4].img = mlx_xpm_file_to_image(data->mlx, data->text[4].path, &data->text[4].width, &data->text[4].height);
	data->text[0].add = mlx_get_data_addr(data->text[0].img, &data->text[0].bits_per_pixel, &data->text[0].line_length, &data->text[0].endian);
	data->text[1].add = mlx_get_data_addr(data->text[1].img, &data->text[1].bits_per_pixel, &data->text[1].line_length, &data->text[1].endian);
	data->text[2].add = mlx_get_data_addr(data->text[2].img, &data->text[2].bits_per_pixel, &data->text[2].line_length, &data->text[2].endian);
	data->text[3].add = mlx_get_data_addr(data->text[3].img, &data->text[3].bits_per_pixel, &data->text[3].line_length, &data->text[3].endian);
	data->text[4].add = mlx_get_data_addr(data->text[4].img, &data->text[4].bits_per_pixel, &data->text[4].line_length, &data->text[4].endian);
	mlx_loop(data->mlx);
}

int main(int ac, char **av)
{
	int fd;
	char *line;
	t_data data;

	line = NULL;
	fd = open(av[1], O_RDONLY);
	if (security_cub(ac, av, &data, fd) == 1)
		return (0);
	store_info(fd, &data, line);
	if (security_data(&data) == 1)
		return (free_struct(&data, 0));
	store_map(fd, &data);
	check_map(&data);
	if (security_check(&data) == 1)
		return (free_struct(&data, 1));
	fill_map_one(&data);
	texture_check(&data);
	if (data.security[11] == 1)
		return (free_struct(&data, 1));
	print_info(&data);
	set_vector_dir(&data);
	print_map(&data);
	run_mlx(&data);
	return (free_struct(&data, 1));
}
