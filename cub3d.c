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

void store_map(int fd, t_data *data)
{
	(void)fd;
	int retour;
	int i;
	
	data->y_map = 0;
	while ((retour = get_next_line(fd, &data->map[0])) == 1)
	{
		ft_putstr_bn(data->map[0]);
		i = 0;
		while (i < ft_strlen(data->map[0]))
		{
			if (data->map[0][i] == '1')
			{
				data->y_map = 1;
				break ;
			}
			i++;
		}
		if (data->map[0][i] == '1')
			break ;
		free(data->map[0]);
	}
	while ((retour = get_next_line(fd, &data->map[data->y_map])) == 1 || data->map[data->y_map][0] != '\0')
	{
		ft_putstr_bn(data->map[data->y_map]);
		data->y_map = data->y_map + 1;
		if (data->y_map == 1024)
		{
			ft_putstr_bn("Error\nYour Map Is Too Long");
			break ;
		}
	}
}

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
** security 11 : 
** security 12 : 
** security 13 : //check ici si les ouvertures de textures sont valides 
** security 14 : //check si le deuxieme sprite est valide
** security 15 : 
** security 16 : 
*/

/*
** List of textures
** no_0 so_1 ea_2 we_3 sprite_4
*/

void	print_map(t_data *data)
{
	int i;

	i = 0;
	printf("---------------------------------\n");
	while(i < data->y_map)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("---------------------------------\n");
}

//	Pour imprimer des lignes arc en ciel a l'ecran.
//	i++;
//	ft_mlx_pixel_put(data, i % 800, (5*i/800) % 500, i*1000);

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

    dst = data->addr + (y * data->line_length + x * 4);
    *(unsigned int*)dst = color;
}

void	add_player(t_data *data)
{
	int a;

	a = 0;
	ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE, data->y_pos * MINIMAP_SIZE, 16711680);
	if (MINIMAP_SIZE > 5)
	{
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE - 1, data->y_pos * MINIMAP_SIZE - 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE, data->y_pos * MINIMAP_SIZE - 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + 1, data->y_pos * MINIMAP_SIZE - 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE - 1, data->y_pos * MINIMAP_SIZE, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + 1, data->y_pos * MINIMAP_SIZE, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE - 1, data->y_pos * MINIMAP_SIZE + 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE, data->y_pos * MINIMAP_SIZE + 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + 1, data->y_pos * MINIMAP_SIZE + 1, 16711680);
		while (a < MINIMAP_SIZE)
		{
			ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + data->x_dir * a, data->y_pos * MINIMAP_SIZE + data->y_dir * a, 16777215);
			a++;
		}
	}
}

void	add_map_top_left(t_data *data)
{
	int i;
	int j;
	int k;
	int pixel;

	i = 0;
	pixel = MINIMAP_SIZE * MINIMAP_SIZE;
	while (i < data->y_map && i * MINIMAP_SIZE < data->y_screen_size)
	{
		j = 0;
		while (j < data->x_map && j * MINIMAP_SIZE < data->x_screen_size)
		{
			k = -1;
			while (++k < pixel)
				ft_mlx_pixel_put(data, j * MINIMAP_SIZE + k / MINIMAP_SIZE, i * MINIMAP_SIZE + k % MINIMAP_SIZE, (data->map[i][j] - '0') * 100000);
			j++;
		}
		i++;
	}
	add_player(data);
}

//remplacer la starting position par un 0

void	move_according_to_key_press(t_data *data)
{
	if (data->forward == 1)
	{
		if (data->map[(int)data->y_pos][(int)(data->x_pos + data->x_dir * MOVING_SPEED* 2)] != '1')
			data->x_pos += data->x_dir * MOVING_SPEED;
		if (data->map[(int)(data->y_pos + data->y_dir * MOVING_SPEED * 2)][(int)(data->x_pos)] != '1')
			data->y_pos += data->y_dir * MOVING_SPEED;
	}
	if (data->backward == 1)
	{
		if (data->map[(int)data->y_pos][(int)(data->x_pos - data->x_dir * MOVING_SPEED * 2)] != '1')
			data->x_pos -= data->x_dir * MOVING_SPEED;
		if (data->map[(int)(data->y_pos - data->y_dir * MOVING_SPEED * 2)][(int)(data->x_pos)] != '1')
			data->y_pos -= data->y_dir * MOVING_SPEED;
	}
	if (data->right == 1)
	{
		if (data->map[(int)(data->y_pos)][(int)(data->x_pos - data->y_dir * MOVING_SPEED * 2)] != '1')
			data->x_pos -= data->y_dir * MOVING_SPEED;
		if (data->map[(int)(data->y_pos + data->x_dir * MOVING_SPEED * 2)][(int)(data->x_pos)] != '1')
			data->y_pos += data->x_dir * MOVING_SPEED;
	}
	if (data->left == 1)
	{
		if (data->map[(int)(data->y_pos)][(int)(data->x_pos + data->y_dir * MOVING_SPEED * 2)] != '1')
			data->x_pos += data->y_dir * MOVING_SPEED;
		if (data->map[(int)(data->y_pos - data->x_dir * MOVING_SPEED * 2)][(int)(data->x_pos)] != '1')
			data->y_pos -= data->x_dir * MOVING_SPEED;
	}
	if (data->turn_right == 1)
	{
		data->temp = data->x_dir;
		data->x_dir = data->x_dir * cos(-ROTATION_SPEED) - data->y_dir * sin(-ROTATION_SPEED);
		data->y_dir = data->temp * sin(-ROTATION_SPEED) + data->y_dir * cos(-ROTATION_SPEED);
		data->temp = data->x_plane;
		data->x_plane = data->x_plane * cos(-ROTATION_SPEED) - data->y_plane * sin(-ROTATION_SPEED);
		data->y_plane = data->temp * sin(-ROTATION_SPEED) + data->y_plane * cos(-ROTATION_SPEED);
	}
	if (data->turn_left == 1)
	{
		data->temp = data->x_dir;
		data->x_dir = data->x_dir * cos(ROTATION_SPEED) - data->y_dir * sin(ROTATION_SPEED);
		data->y_dir = data->temp * sin(ROTATION_SPEED) + data->y_dir * cos(ROTATION_SPEED);
		data->temp = data->x_plane;
		data->x_plane = data->x_plane * cos(ROTATION_SPEED) - data->y_plane * sin(ROTATION_SPEED);
		data->y_plane = data->temp * sin(ROTATION_SPEED) + data->y_plane * cos(ROTATION_SPEED);
	}
//	printf(">>>>>x_dir:%f<<<<<, >>>>>y_dir:%f<<<<<\n", data->x_dir, data->y_dir);
//	printf("X%f_Y%f\n", data->x_pos, data->y_pos);
}

void determine_id(t_data *data, int *id)
{
	if (data->side == 0)
	{
		if (data->x_ray_dir > 0)
			*id = 3;
		else
			*id = 2;
	}
	else
	{
		if (data->y_ray_dir < 0)
			*id = 0;
		else
			*id = 1;
	}
}

void put_column_image(t_data *data, int column)
{
	int i;
	int x_texture;
	int y_texture;
	double step;
	double tex_pos;
	int	id;

	i = 0;
	while (i < data->line_start)
	{
		ft_mlx_pixel_put(data, column, i, 6183820);
		i++;
	}
	determine_id(data, &id);
	if (data->side == 0)
		data->wall_hit = data->y_pos + data->dist_wall * data->y_ray_dir;
	else
		data->wall_hit = data->x_pos + data->dist_wall * data->x_ray_dir;
	data->wall_hit -= floor(data->wall_hit); //retirer les doubles parentheses ?
	x_texture = (int)(data->wall_hit * (double)(data->text[id].width));
	if (data->side == 0 && data->x_ray_dir > 0)
		x_texture = data->text[id].width - x_texture - 1;
	if (data->side == 1 && data->y_ray_dir < 0)
		x_texture = data->text[id].width - x_texture - 1;
	
	step = 1.0 * data->text[id].height / data->line_size;
	tex_pos = (data->line_start - data->y_screen_size / 2 + data->line_size / 2) * step;
	while (i < data->line_end)
	{
		y_texture = (int)tex_pos & (data->text[id].height - 1);
		tex_pos += step;
		//printf(">>>>>x_dir:%d<<<<<, >>>>>y_dir:%d<<<<<\n", x_texture, y_texture);
		*(unsigned int *)(data->addr + (i * data->line_length + column * 4)) = *(unsigned int *)(data->text[id].add + y_texture * data->text[id].line_length + x_texture * 4);
		i++;
	}
	while (i < data->y_screen_size)
	{
		ft_mlx_pixel_put(data, column, i, 6052956);
		i++;
	}
}

void	sort_sprite(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->sprite_num)
	{
		j = i + 1;
		while (j < data->sprite_num)
		{
			if (data->sprite[i][3] < data->sprite[j][3])
			{
				/**data->sprite[500] = *data->sprite[i]; // Cool de l'opti
				*data->sprite[i] = *data->sprite[j];
				*data->sprite[j] = *data->sprite[500];*/
				data->sprite[500][0] = data->sprite[i][0];
				data->sprite[500][1] = data->sprite[i][1];
				data->sprite[500][2] = data->sprite[i][2];
				data->sprite[500][3] = data->sprite[i][3];
				data->sprite[i][0] = data->sprite[j][0];
				data->sprite[i][1] = data->sprite[j][1];
				data->sprite[i][2] = data->sprite[j][2];
				data->sprite[i][3] = data->sprite[j][3];
				data->sprite[j][0] = data->sprite[500][0];
				data->sprite[j][1] = data->sprite[500][1];
				data->sprite[j][2] = data->sprite[500][2];
				data->sprite[j][3] = data->sprite[500][3];
			}
			j++;
		}
		i++;
	}
	//printf("%f, %f, %f, %f, %f, %f\n", data->sprite[0][3], data->sprite[1][3], data->sprite[2][3], data->sprite[3][3], data->sprite[4][3], data->sprite[5][3]);
}

void	raycasting_calculation(t_data *data)
{
	int i;

	i = 0;
	while (i < data->x_screen_size)
	{
		//printf(">>>>>x_pos:%f<<<<<, >>>>>y_pos:%f<<<<<\n", data->x_pos, data->y_pos);
		data->pos_plane = 2 * i / (double)data->x_screen_size - 1;
		//printf(">>>>>pos_plane:%f<<<<<, >>>>>i:%d<<<<<, >>>>>x_screen_size:%d<<<<<\n", data->pos_plane, i, data->x_screen_size);
		data->x_ray_dir = data->x_dir + data->x_plane * data->pos_plane;
		data->y_ray_dir = data->y_dir + data->y_plane * data->pos_plane;
		//printf(">>>>>x_dir:%f<<<<<, >>>>>y_dir:%f<<<<<\n", data->x_dir, data->y_dir);
		//printf(">>>>>x_ray_dir:%f<<<<<, >>>>>y_ray_dir:%f<<<<<\n", data->x_ray_dir, data->y_ray_dir);
		data->x_raymap = (int)data->x_pos;
		data->y_raymap = (int)data->y_pos;
		//printf(">>>>>x_raymap:%d<<<<<, >>>>>y_raymap:%d<<<<<\n", data->x_raymap, data->y_raymap);
		data->x_delta_dist = (data->x_ray_dir == 0) ? 1000000 : ((data->x_ray_dir == 0) ? 1 : fabs(1 / data->x_ray_dir));
		data->y_delta_dist = (data->y_ray_dir == 0) ? 1000000 : ((data->y_ray_dir == 0) ? 1 : fabs(1 / data->y_ray_dir));
		//printf(">>>>>x_delta_dist:%f<<<<<, >>>>>y_delta_dist:%f<<<<<\n", data->x_delta_dist, data->y_delta_dist);
		// Split ici
		if (data->x_ray_dir < 0)
		{
			data->x_step = -1;
			data->x_side_dist = (data->x_pos - data->x_raymap) * data->x_delta_dist;
		}
		else
		{
			data->x_step = 1;
			data->x_side_dist = (data->x_raymap + 1.0 - data->x_pos) * data->x_delta_dist;
		}
		if (data->y_ray_dir < 0)
		{
			data->y_step = -1;
			data->y_side_dist = (data->y_pos - data->y_raymap) * data->y_delta_dist;
		}
		else
		{
			data->y_step = 1;
			data->y_side_dist = (data->y_raymap + 1.0 - data->y_pos) * data->y_delta_dist;
		}
		// Split ici
		//printf(">>>>>x_step:%d<<<<<, >>>>>y_step:%d<<<<<\n", data->x_step, data->y_step);
		//printf(">>>>>x_delta_dist:%f<<<<<, >>>>>y_delta_dist:%f<<<<<\n", data->x_delta_dist, data->y_delta_dist);
		while (data->hit == 0)
		{
			if (data->x_side_dist < data->y_side_dist)
			{
				data->x_side_dist += data->x_delta_dist;
				data->x_raymap += data->x_step;
				data->side = 0;
			}
			else
			{
				data->y_side_dist += data->y_delta_dist;
				data->y_raymap += data->y_step;
				data->side = 1;
			}
			//printf(">>>>>x_raymap:%d<<<<<, >>>>>y_raymap:%d<<<<<\n", data->x_raymap, data->y_raymap);
			if (data->map[data->y_raymap][data->x_raymap] == '1')
				data->hit = 1;
		}
		// Split ici
		if (data->side == 0)
			data->dist_wall = (data->x_raymap - data->x_pos + (1 - data->x_step) / 2) / data->x_ray_dir;
		else
			data->dist_wall = (data->y_raymap - data->y_pos + (1 - data->y_step) / 2) / data->y_ray_dir;
		// Possible split ici.
		//printf(">>>>>dist_wall:%f<<<<<\n", data->dist_wall);
		data->line_size = (int)(data->y_screen_size / data->dist_wall);
		//printf(">>>>>Lenght:%d<<<<<, >>>>>End:%f<<<<<\n", data->line_size, data->dist_wall);
		data->line_start = - data->line_size / 2 + data->y_screen_size / 2;
		if (data->line_start < 0)
			data->line_start = 0;
		data->line_end = data->line_size / 2 + data->y_screen_size / 2;
		if (data->line_end >= data->y_screen_size)
			data->line_end = data->y_screen_size - 1;
		put_column_image(data, i);
		data->buff[i] = data->dist_wall;
		//printf(">>>>>Start:%d<<<<<, >>>>>End:%d<<<<<\n", data->line_start, data->line_end);
		data->hit = 0;
/*		if (i == 404)
			break ;*/
		i++;
	}
	i = -1;
	while (++i < data->sprite_num)
		data->sprite[i][3] = ((data->x_pos - data->sprite[i][0]) * (data->x_pos - data->sprite[i][0]) + (data->y_pos - data->sprite[i][1]) * (data->y_pos - data->sprite[i][1]));
	sort_sprite(data);
	/*i = 0;
	while (i < data->sprite_num)
	{
		printf(">>>%f<<<\n", data->sprite[i][3]);
		i++;
	}*/
	i = 0; // on draw juste le sprite le plus proche afin de debug
	int j; // stripe
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
			data->y_drawend = data->y_screen_size/* - 1*/;
		data->w_sprite = abs((int)(data->y_screen_size / data->y_trans));
		data->x_drawstart = -data->w_sprite / 2 + data->x_sprscr;
		if (data->x_drawstart < 0)
			data->x_drawstart = 0;
		data->x_drawend = data->w_sprite / 2 + data->x_sprscr;
		if (data->x_drawend >= data->x_screen_size)
			data->x_drawend = data->x_screen_size/* - 1*/;
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
					//write(1, "a", 1);
					//printf(">>>>%u<<<<", *(unsigned int *)(data->text[4].add + data->text[4].line_length * data->y_tex + data->x_tex * 4));
					//return;
					k++;
				}
				//printf(">>>>>y_drawstart:%d<<<<<, >>>>>y_drawend:%d<<<<<\n", data->y_drawstart, data->y_drawend);
				//printf(">>>>>x_drawstart:%d<<<<<, >>>>>x_drawend:%d<<<<<, >>>>>y_trans:%f<<<<<, >>>>>sprite[i][3]:%f<<<<<\n", data->x_drawstart, data->x_drawend, data->y_trans, data->sprite[i][3]);
			}
			/*if (data->y_trans > 0)
				write(1, "1", 1);
			else 
				write(1, "0", 1);
			if (j >= 0)
				write(1, "1", 1);
			else 
				write(1, "0", 1);
			if (j < data->x_screen_size)
				write(1, "1", 1);
			else 
				write(1, "0", 1);
			if (data->y_trans < data->sprite[i][3])
				write(1, "1\n", 2);
			else 
				write(1, "0\n", 2);*/
			j++;
		}
		i++;
	}
	//printf(">>>>>x_drawstart:%d<<<<<, >>>>>x_drawend:%d<<<<<, >>>>>y_trans:%f<<<<<, >>>>>sprite[i][3]:%f<<<<<\n", data->x_drawstart, data->x_drawend, data->y_trans, data->sprite[i - 1][3]);
}

int		render_next_frame(t_data *data)
{
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	move_according_to_key_press(data);
	raycasting_calculation(data);
	if (MINIMAP_SIZE * data->x_map <= data->x_screen_size && MINIMAP_SIZE * data->y_map <= data->y_screen_size)
		add_map_top_left(data);
	int i = 0;
	while (i < 1)
		i++;
	return (0);
}

int		ft_key_hook(int keycode, t_data *data)
{
	if (keycode == KEY_FORWARD)
		data->forward = 1;
	if (keycode == KEY_BACKWARD)
		data->backward = 1;
	if (keycode == KEY_RIGHT)
		data->right = 1;
	if (keycode == KEY_LEFT)
		data->left = 1;
	if (keycode == KEY_TURN_LEFT)
		data->turn_left = 1;
	if (keycode == KEY_TURN_RIGHT)
		data->turn_right = 1;
	//printf("Hello from key_hook nubber %d !\n", keycode);
	//printf("F%d_B%d_R%d_L%d_TL%d_TR%d\n", data->forward, data->backward, data->right, data->left, data->turn_left, data->turn_right);
	return (0);
}

int		ft_key_unhook(int keycode, t_data *data)
{
	if (keycode == KEY_FORWARD)
		data->forward = 0;
	if (keycode == KEY_BACKWARD)
		data->backward = 0;
	if (keycode == KEY_RIGHT)
		data->right = 0;
	if (keycode == KEY_LEFT)
		data->left = 0;
	if (keycode == KEY_TURN_LEFT)
		data->turn_left = 0;
	if (keycode == KEY_TURN_RIGHT)
		data->turn_right = 0;
	//printf("Goodby from key_hook nubber %d !\n", keycode);
	//printf("F%d_B%d_R%d_L%d_TL%d_TR%d\n", data->forward, data->backward, data->right, data->left, data->turn_left, data->turn_right);
	return (0);
}

void	run_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->x_screen_size, data->y_screen_size, "The cub3D Labyrinth - A 42_Paris Project - by bmerchin");
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

/*
else if ((fd = open(str, O_RDONLY)) < 0)
		return (OPEN_FILE_FAILED);
	else if (fd && read(fd, NULL, 0) == -1)
		return (OPEN_FILE_FAILED);
*/

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
