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
# include <math.h>

# define BUFFER_SIZE 4095

typedef struct	s_struct
{
	char	buff[BUFFER_SIZE + 1];
	int		ret;
	int		curs;
}				t_struct;

# define MINIMAP_SIZE 8
# define MOVING_SPEED 0.03

# define KEY_FORWARD 13
# define KEY_BACKWARD 1
# define KEY_RIGHT 2
# define KEY_LEFT 0
# define KEY_TURN_LEFT 123
# define KEY_TURN_RIGHT 124

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
	char			start_dir;
	char			*map[1024];
	int				security[20];
	int				x_map; // Taille de la map (plus longue ligne et plus longue colonne) 
	int				y_map; 

	int				x_raymap; // Position sans chiffres apres la virgule // mapX
	int				y_raymap;
	double			x_pos; // Position precise de la personnes sur la map // posX
	double			y_pos;
	double			x_dir; // Direction de la personne (set au debut) // dirX
	double			y_dir;
	double			x_plane; // Direction du plan de la camera (set au debut) // planeX
	double			y_plane;
	double			x_ray_dir; // Calcul de la directin du rayon
	double			y_ray_dir;
	double			x_side_dist; // Distance parcourue jusqu'au peochain cote x;
	double			y_side_dist;
	double			dist_wall;	// Distance avec le mur // perpWallDist
	double			x_delta_dist; // Distance parcourue entre chaque point d'intersection vertical
	double			y_delta_dist;
	double			pos_plane; // Position sur le plan de la camera (delta de -1 a 1 avec 0 au milieu) // cameraX
	int				x_step; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int				y_step; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int				hit; // 1 si un mur a ete touche, 0 sinon
	int				side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	int				line_start;
	int				line_end;
	int				line_lenght;

	void			*mlx;
	void			*img;
	char			*addr;
	void			*win;
	int				bits_per_pixel;
	int				line_length;
	int				endian;

	int				forward;
	int				backward;
	int				right;
	int				left;
	int				turn_right;
	int				turn_left;
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
void			fill_map_one(t_data *data);

#endif
