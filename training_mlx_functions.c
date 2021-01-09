#include "cub3d.h"
/*
void check_map(t_struct *data)
{
	
	
}*/

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

int free_struct(t_data *data)
{
	free(data->sprite);
	free(data->no);
	free(data->so);
	free(data->we);
	free(data->ea);
	return (0);
}

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
		if 
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
			ft_putstr_bn("Error\nData Missing in Map");
			return (free_struct(&data));
		}
		if (data.security[i] > 1)
		{
			ft_putstr_bn("Error\nData Provided Multiple Times");
			return (free_struct(&data));
		}
		i++;
	}
	if (data.x_screen_size > 10000 || data.y_screen_size > 10000)
	{
		ft_putstr_bn("Error\nYour Map resolution is too big");
		return (free_struct(&data));
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
	while (fd < 1500000000)
		fd++;
	ft_putstr_bn("nan j'dec");*/

	return (0);
}
