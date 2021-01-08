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

int main(int ac, char **av)
{
	int fd;
	int retour;
	char *line;
	t_data data;

	(void)data;
	line = NULL;
	if (ac != 2)
	{
		ft_putstr_bn("Wrong number of arguments");
		return (0);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
	{
		ft_putstr_bn("OpenError");
		return (0);
	}
	while ((retour = get_next_line(fd, &line)) == 1)
	{
		ft_putstr_bn(line);
		free(line);
	}

/*	if (line[0] != 0)
	{
		ft_putstr_bn(line);
		free(line);
	}*/
/*	ft_putstr_bn("");
	ft_putstr_bn("segfaul error[1]");
	while (fd < 1500000000)
		fd++;
	ft_putstr_bn("nan j'dec");*/
	return (0);
}
