/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 02:02:12 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/12 16:06:08 by bmerchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define BUFFER_SIZE 4095

typedef struct	s_struct
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	int		curs;
}				t_struct;

typedef struct	s_data
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	unsigned short	x_screen_size;
	unsigned short	y_screen_size;
	int				floor;
	int				ceiling;
	int				y_map;
	int				x_map;
	char			*map[1024];
	char			start_dir;
	double			x_pos;
	double			y_pos;
	double			x_dir;
	double			y_dir;
	double			x_plane;
	double			y_plane;
	int				security[20];
	double			time_frame_now;
	double			time_frame_old;

	void			*mlx;
	void			*img;
    char			*addr;
	void			*win;
    int				bits_per_pixel;
    int				line_length;
    int				endian;
}				t_data;

int				get_next_line(int fd, char **line);
int				get_next_line2(int fd, char **line, t_struct *dta);
int				ft_strlen(char *str);
int				ft_strlenn(char *str);
char			*ft_strjoin(char *s1, char *s2, t_struct *dta);
char			*free_null(char *s1);
int				free_int(char **line);

void			ft_putstr_bn(char *str);
int				ft_atoi(char *str);
int				ft_atoi_parsing(char *str, int *i);
char			*ft_strdup(char *s1);

int				get_t(int i);
int				get_r(int i);
int				get_g(int i);
int				get_b(int i);
int				store_color(int i, int j, int k, int l);

void			store_info(int fd, t_data *data, char *line);

void			print_info(t_data *data);
int				free_struct(t_data *data, int m);

int				security_check(t_data *data);
int				security_cub(int ac, char **av, t_data *data, int fd);
int				security_data(t_data *data);

void			check_map(t_data *data);

void			set_vector_dir(t_data *data);

#endif
