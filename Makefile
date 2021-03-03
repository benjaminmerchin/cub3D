NAME	=	cub3D
CC		=	clang
OS		=	$(shell uname -s)
SRC		=	cub3d.c get_next_line.c get_next_line_utils.c utils_basic.c utils_color.c store_map.c \
			utils_parsing.c security.c verification_map.c utils_initialize_struct_map.c hook.c \
			minimap.c moving.c verification_texture.c screenshot.c utils_mlx.c put_column_image.c \
			utils_store_map.c utils_raycasting.c sprite.c clean_exit.c utils_bonus.c utils_bonus2.c \
			utils_bonus3.c utils_libft.c door.c bonus_texture_id.c minimap2.c utils_space.c
HEADER	=	cub3d.h
OBJ 	=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -g#-fsanitize=address
MLX_DIR	=	mlx
MLX_LNX	=	mlx-linux
MLX		=	libmlx.dylib
BONUS	=	-D BONUS=1

ifeq ($(OS), Darwin)
all: $(NAME)

$(NAME): mlx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l $(MLX_DIR)
	install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)

mlx:
	make -C $(MLX_DIR) 

%.o: %.c $(MLX_DIR)/$(MLX) $(HEADER)
	$(CC) $(CFLAGS) -I $(MLX_DIR) -c $< -o $@

bonus: CFLAGS	=	-Wall -Wextra -Werror $(BONUS)

bonus: mlx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l $(MLX_DIR)
	install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)
endif

ifeq ($(OS), Linux)
all: $(NAME)

$(NAME): mlx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L ./mlx-linux -lmlx -lXext -lX11 -lm

mlx:
	make -C $(MLX_LNX)

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

bonus: CFLAGS	=	-Wall -Wextra -Werror $(BONUS)

bonus: mlx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L ./mlx-linux -lmlx -lXext -lX11 -lm

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_LNX)
endif

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re mlx bonus
