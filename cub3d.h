/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bmerchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 02:02:12 by bmerchin          #+#    #+#             */
/*   Updated: 2021/01/10 18:57:18 by bmerchin         ###   ########.fr       */
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
	char			starting_direction;
	short			x_player_start;
	short			y_player_start;
	int				security[20];
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

#endif
