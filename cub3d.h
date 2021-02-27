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

# define MINIMAP_SIZE 5
# define MOVING_SPEED 0.1
# define ROTATION_SPEED 0.035
# define NUM_SPRITE_BOMUS 12

# ifdef __linux__
#  define KEY_FORWARD 119
#  define KEY_BACKWARD 115
#  define KEY_RIGHT 100
#  define KEY_LEFT 97
#  define KEY_TURN_LEFT 65361
#  define KEY_TURN_RIGHT 65363
#  define KEY_CROUCH 0
#  define KEY_ESCAPE 0
#  define KEY_SPRINT 0
#  define KEY_DOOR 0
#  define MACOS 0
#  define LINUX 1
# else
#  define KEY_FORWARD 13
#  define KEY_BACKWARD 1
#  define KEY_RIGHT 2
#  define KEY_LEFT 0
#  define KEY_TURN_LEFT 124
#  define KEY_TURN_RIGHT 123
#  define KEY_CROUCH 8
#  define KEY_ESCAPE 53
#  define KEY_SPRINT 126
#  define KEY_DOOR 40
#  define MACOS 1
#  define LINUX 0
# endif

# ifndef BONUS
#  define BONUS 0
# endif

typedef struct	s_text {
	char	*path;
	void	*img;
	char	*add;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		width;
	int		height;
}				t_text;

typedef struct	s_data
{
	t_text			text[30];
	unsigned short	x_screen_size; //w
	unsigned short	y_screen_size; //h
	int				floor;
	int				ceiling;
	char			start_dir;
	char			*map[1024];
	int				security[20];
	int				save;
	int				x_map; // Taille de la map (plus longue ligne et plus longue colonne) 
	int				y_map;
	int				frame;
	int				time;

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
	double			temp; // Pour stocker une valeur qui est immediatement reutilisee dans le calcul
	int				x_step; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
	int				y_step; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
	int				hit; // 1 si un mur a ete touche, 0 sinon
	int				side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
	int				line_start; // drawStart
	int				line_end; // drawEnd
	int				line_size; // lineHeight

	double			wall_hit;

	void			*mlx;
	void			*img;
	char			*addr;
	void			*win;
	int				bits_per_pixel;
	int				line_length;
	int				endian;

	int				forward;
	int				sprint;
	int				backward;
	int				right;
	int				left;
	int				turn_right;
	int				turn_left;
	double			crouch;
	int				escape;
	int				victory;
	int				life;
	int				door_closed;
	int				v_bool_print_score;
	int				heart[11][11];
	int				the_end[5][36];

	int				sprite_num;
	double			sprite[501][5];
	double			buff[20000];		// ZBuffer
	double			x_sprite;
	double			y_sprite;
	double			matrice; // Utilise pour inverser la matrice // invDet
	double			x_trans; //transformX
	double			y_trans; //transformY
	int				x_sprscr; //spritescreenX
	int				y_sprscr; //spritescreenY
	int				h_sprite; //spriteheight
	int				w_sprite; //spritewidth
	int				x_drawstart; // drawStartX
	int				y_drawstart; // drawStartY
	int				x_drawend; // drawEndX
	int				y_drawend; // drawEndY
	int				x_tex;
	int				y_tex;
	int				x_texture;
	int				y_texture;
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
void			print_map(t_data *data);
void			store_sprite(t_data *data, int x, int y);

int				security_check(t_data *data);
int				security_cub(int ac, char **av, t_data *data, int fd);
int				security_data(t_data *data);

void			check_map(t_data *data);

void			set_vector_dir(t_data *data);
void			fill_map_one(t_data *data);

int				ft_key_hook(int keycode, t_data *data);
int				ft_key_unhook(int keycode, t_data *data);

void			add_minimap_and_company(t_data *data);

void			move_according_to_key_press(t_data *data);

void			texture_check(t_data *data);

void			save_image(t_data *data);

void			ft_mlx_pixel_put(t_data *data, int x, int y, int color);
void			sort_sprite(t_data *data);
void			sprite_dist_calc(t_data *data);
void			init_images_mlx(t_data *data);

void			put_column_image(t_data *data, int column);

void			store_map(int fd, t_data *data);

void			raycasting_initialize(t_data *data, int *i);
void			raycasting_move_until_wall(t_data *data);
void			raycasting_line_position(t_data *data);

void			sprite(t_data *data);

int				clean_exit(int keycode, t_data *data);
void			exit_free(t_data *data);

void			init_images_bonus(t_data *data);
void			initialize_heart(t_data *data);

void			heal_at_spawn(t_data *data);
void			initialize_the_end(t_data *data);
void			echo_the_end(t_data *data);

int				is_in(char c, char *str);
void			victory_exit_check(t_data *data);

void			ft_putnbr(int n);
void			ft_putchar(char c);

void			close_door(t_data *data);
void			open_door(t_data *data);




#endif
