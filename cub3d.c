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

typedef struct  s_mlx {
    void	*img;
    char	*addr;
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}               t_mlx;

typedef struct  s_vars {
	void	*mlx;
	void	*win;
}               t_vars;

int             key_hook(int keycode, t_vars *vars)
{
    printf("Hello from key_hook nubber %d !\n", keycode);
	(void)vars;
	(void)keycode;
	return (0);
}

void            my_mlx_pixel_put(t_mlx *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int             my_close(int keycode, t_vars *data)
{
    if (keycode == 5)
		mlx_destroy_window(data->mlx, data->win);
	printf("Hello from key_hook nubber %d !\n", keycode);
	return (0);
}
/*
// img->line_length = (img->bits_per_pixel / 8) * data->x_length
int				main(void)
{
//    void    *mlx;
//   void    *window;
//    t_mlx	img;
	t_vars	vars;
//	int color = 0x00FF0000;
//	int i = -1;

//	printf("\n\n%d\n\n", color);

//	mlx = mlx_init();
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 300, 200, "Hello world!");
//	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_hook(vars.win, 3, 1L<<1, my_close, &vars);
//	window = mlx_new_window(mlx, 256, 256, "First Window");
//	img.img = mlx_new_image(mlx, 256, 256);
//	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
//	while (++i < 256*256)
//		my_mlx_pixel_put(&img, i%256, i/256, 256*256*i + i*255 - 1);
//	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
//	mlx_loop(mlx);
	mlx_loop(vars.mlx);
//	free(mlx);
//	free(window);
//	free(img.img);
//	free(img.addr);
}
*/


//	Pour imprimer des lignes arc en ciel a l'ecran.
//	i++;
//	ft_mlx_pixel_put(data, i % 800, (5*i/800) % 500, i*1000);

void	ft_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

    dst = data->addr + (y * data->line_length + x * 4);
    *(unsigned int*)dst = color;
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
	ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE, data->y_pos * MINIMAP_SIZE, 16711680);
	if (MINIMAP_SIZE > 3)
	{
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + 1, data->y_pos * MINIMAP_SIZE, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE, data->y_pos * MINIMAP_SIZE + 1, 16711680);
		ft_mlx_pixel_put(data, data->x_pos * MINIMAP_SIZE + 1, data->y_pos * MINIMAP_SIZE + 1, 16711680);
	}
}

void	move_according_to_key_press(t_data *data)
{
	if (data->forward == 1 && data->y_pos >= 0 + MOVING_SPEED)
		data->y_pos -= MOVING_SPEED;
	if (data->backward == 1 && data->y_pos < data->y_map - MOVING_SPEED)
		data->y_pos += MOVING_SPEED;
	if (data->right == 1 && data->x_pos < data->x_map - MOVING_SPEED)
		data->x_pos += MOVING_SPEED;
	if (data->left == 1 && data->x_pos >= 0 + MOVING_SPEED)
		data->x_pos -= MOVING_SPEED;
//	printf("X%f_Y%f\n", data->x_pos, data->y_pos);
}

void	raycasting_calculation(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->x_screen_size)
	{
		data->pos_plane = 2 * i / data->x_screen_size - 1;
		data->x_ray_dir = data->x_dir + data->x_plane * data->pos_plane;
		data->y_ray_dir = data->y_dir + data->y_plane * data->pos_plane;
		data->x_raymap = (int)data->x_pos;
		data->y_raymap = (int)data->y_pos;
		data->x_delta_dist = (data->x_ray_dir == 0) ? 0 : ((data->x_ray_dir == 0) ? 1 : fabs(1 / data->x_ray_dir));
		data->y_delta_dist = (data->y_ray_dir == 0) ? 0 : ((data->y_ray_dir == 0) ? 1 : fabs(1 / data->y_ray_dir));
		if (data->x_ray_dir < 0)
		{
			data->x_step = -1;
			data->x_delta_dist = (data->x_pos - data->x_raymap) * data->x_delta_dist;
		}
		else
		{
			data->x_step = 1;
			data->x_delta_dist = (data->x_raymap + 1.0 - data->x_pos) * data->x_delta_dist;
		}
		if (data->y_ray_dir < 0)
		{
			data->y_step = -1;
			data->y_delta_dist = (data->y_pos - data->y_raymap) * data->y_delta_dist;
		}
		else
		{
			data->y_step = 1;
			data->y_delta_dist = (data->y_raymap + 1.0 - data->y_pos) * data->y_delta_dist;
		}
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
			if (data->map[data->x_raymap][data->y_raymap] > 0)
				data->hit = 1;
		}
		if (data->side == 0)i++;
	}
}

int		render_next_frame(t_data *data)
{
	move_according_to_key_press(data);
	raycasting_calculation(data);
	if (MINIMAP_SIZE * data->x_map <= data->x_screen_size && MINIMAP_SIZE * data->y_map <= data->y_screen_size)
		add_map_top_left(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
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
	printf("Hello from key_hook nubber %d !\n", keycode);
	printf("F%d_B%d_R%d_L%d_TL%d_TR%d\n", data->forward, data->backward, data->right, data->left, data->turn_left, data->turn_right);
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
	printf("Goodby from key_hook nubber %d !\n", keycode);
	printf("F%d_B%d_R%d_L%d_TL%d_TR%d\n", data->forward, data->backward, data->right, data->left, data->turn_left, data->turn_right);
	return (0);
}

void	run_mlx(t_data *data)
{
	data->mlx = mlx_init();
	data->win = mlx_new_window(data->mlx, data->x_screen_size, data->y_screen_size, "The cub3D Labyrinth - A 42_Paris Project - by bmerchin");
	mlx_loop_hook(data->mlx, render_next_frame, data);
//	mlx_key_hook(data->win, ft_key_hook, data);
	mlx_hook(data->win, 2, 1L<<0, ft_key_hook, data);
	mlx_hook(data->win, 3, 1L<<1, ft_key_unhook, data);
	data->img = mlx_new_image(data->mlx, data->x_screen_size, data->y_screen_size);
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
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
	open_then_read(data->no, data);
	open_then_read(data->so, data);
	open_then_read(data->we, data);
	open_then_read(data->ea, data);
	open_then_read(data->sprite, data);
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
