/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 10:56:04 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/10 18:57:24 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//void check_missing

//void store_data

/*int main(void)
{
//	void *mlx;
//	void *window;
//	t_data	data;
  
	write(1, "124", 3);
//  	mlx = mlx_init();
//	(void)mlx;
//	window = mlx_new_window(mlx, 400, 400, "Title");
//	mlx_loop(mlx);
	
	

	ft_putstr_bn("ok");

//	free(mlx);
  	return (0);
}*/

void store_rfc(t_data *data, int *i, char *line)
{
	unsigned short red;
	unsigned short green;
	unsigned short blue;
	
	*i = *i + 1;
	if (line[0] == 'R')
	{
		data->x_screen_size = ft_atoi_parsing(&line[*i], i);
		while (line[*i] != ' ')
			*i = *i + 1;
		data->y_screen_size = ft_atoi(&line[*i]);
		data->security[0] += 1;
	}
	else
	{
		red = ft_atoi_parsing(&line[*i], i);
		*i = *i + 1;
		green = ft_atoi_parsing(&line[*i], i);
		*i = *i + 1;
		blue = ft_atoi_parsing(&line[*i], i);
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
}

void store_path(t_data *data, char *line)
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
	{
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
}

int free_struct(t_data *data, int m)
{
	int i;
	
	i = 0;
	free(data->sprite);
	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
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

int all_good(t_data *data)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (data->security[i] != 1)
			return (0);
		else
			i++;
	}
	return (1);
}

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
	while ((retour = get_next_line(fd, &data->map[data->y_map])) == 1)
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

void find_wall(t_data *data, int x, int y)
{
	int start_x;
	int start_y;

	start_x = x;
	start_y = y;
	while (x + 1 < ft_strlen(data->map[y]))
	{
		x++;
		if (data->map[y][x] == '1')
			break ;
		else if (data->map[y][x] == ' ' || x + 1 == ft_strlen(data->map[y]))
		{
			data->security[9] = data->security[9] + 1;
			break ;
		}
	}
	x = start_x;
	while (x - 1 >= 0)
	{
		x--;
		if (data->map[y][x] == '1')
			break ;
		else if (data->map[y][x] == ' ' || x == 0)
		{
			data->security[9] = data->security[9] + 1;
			break ;
		}
	}
	x = start_x;
	while (y - 1 >= 0)
	{
		y--;
		if (data->map[y][x] == '1')
			break ;
		else if (data->map[y][x] == ' ' || y == 0 || ft_strlen(data->map[y - 1]) <= x)
		{
			data->security[9] = data->security[9] + 1;
			break ;
		}
	}
	y = start_y;
	while (y + 1 <= data->y_map)
	{
		y++;
		if (data->map[y][x] == '1')
			break ;
		else if (data->map[y][x] == ' ' || y == data->y_map || ft_strlen(data->map[y + 1]) <= x)
		{
			data->security[9] = data->security[9] + 1;
			break ;
		}	
	}
}

void check_map(t_data *data)
{
	int x;
	int y;
	int len;

	y = 0;
	while (y <= data->y_map)
	{
		x = 0;
		len = ft_strlen(data->map[y]);
		while (x < len)
		{
			if (data->map[y][x] == '0' || data->map[y][x] == '2' || data->map[y][x] == '3')
				find_wall(data, x, y);
			else if (data->map[y][x] == 'N' || data->map[y][x] == 'S' || data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				data->starting_direction = data->map[y][x];
				find_wall(data, x, y);
				data->security[8] = data->security[8] + 1;
			}
			else if (data->map[y][x] != ' ')
				data->security[10] = data->security[10] + 1;
			x++;
		}
		y++;
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
** security 13 : 
** security 14 : 
** security 15 : 
** security 16 : 
*/

int main(int ac, char **av)
{
	int fd;
	int retour;
	char *line;
	t_data data;
	int i;

	i = 0;
	while (i < 20)
		data.security[i++] = 0;
	line = NULL;
	if (ac != 2)
	{
		ft_putstr_bn("Error\nWrong number of arguments");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_putstr_bn("Error\nOpen Folder");
		return (0);
	}
	while ((retour = get_next_line(fd, &line)) == 1)
	{
		ft_putstr_bn(line);
		i = 0;
		if ((line[0] == 'R' || line[0] == 'F' || line[0] == 'C') && line[1] == ' ')
			store_rfc(&data, &i, line);
		if ((line[0] == 'S' && line[1] == ' ') || (((line[0] == 'N' && line[1] == 'O') || (line[0] == 'S' && line[1] == 'O') || (line[0] == 'W' && line[1] == 'E') || (line[0] == 'E' && line[1] == 'A')) && line[2] == ' '))
			store_path(&data, line);
		free(line);
		if (all_good(&data) == 1)
		   break ;
	}


/*	if (line[0] != 0)
	{
		ft_putstr_bn(line);
		free(line);
	}*/
	i = 0;
	while (i < 8) // ajuster le nombre de parametres a verifier
	{
		if (data.security[i] == 0)
		{
			ft_putstr_bn("Error\nData Missing in .cub");
			return (free_struct(&data, 0));
		}
		if (data.security[i] > 1)
		{
			ft_putstr_bn("Error\nData Provided Multiple Times in .cub");
			return (free_struct(&data, 0));
		}
		i++;
	}


	if (data.x_screen_size > 10000 || data.y_screen_size > 10000)
	{
		ft_putstr_bn("Error\nYour Map resolution is too big");
		return (free_struct(&data, 0));
	}

	store_map(fd, &data);
	check_map(&data);

	printf("======%d=====", data.security[10]);//

	if (data.security[8] != 1)
	{
		ft_putstr_bn("Error\nThere is not the correct amount of starting directions");
		return (free_struct(&data, 1));
	}
	if (data.security[9] != 0)
	{
		ft_putstr_bn("Error\nThere is at least one missing wall on the map");
		return (free_struct(&data, 1));
	}

	if (data.security[10] != 0)
	{
		ft_putstr_bn("Error\nThere is an invalid character on the map");
		return (free_struct(&data, 1));
	}

	printf("\n\nScreen Size x : %hu\n", data.x_screen_size);
	printf("Screen Size y : %hu\n", data.y_screen_size);
	printf("Floor Color : %d\n", data.floor);
	printf("Ceiling Color : %d\n", data.ceiling);
	printf("Sprite Texture Path : %s\n", data.sprite);
	printf("NO Texture Path : %s\n", data.no);
	printf("SO Texture Path : %s\n", data.so);
	printf("WE Texture Path : %s\n", data.we);
	printf("EA Texture Path : %s\n", data.ea);




/*	ft_putstr_bn("");
	ft_putstr_bn("[1]    66083 segmentation fault  ./cub3D map.cub");
	while (fd < 1000000000)
		fd++;
	ft_putstr_bn("nan j'dec");*/

	return (0);
}
