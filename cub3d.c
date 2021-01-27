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

void run_mlx(t_data *data)
{
	data->mlx = mlx_init();
    data->img = mlx_new_image(data->mlx, data->x_screen_size, data->y_screen_size);
	data->win = mlx_new_window(data->mlx, data->x_screen_size, data->y_screen_size, "The cub3D Labyrinth - A 42_Paris Project - by bmerchin");
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
