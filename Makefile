NAME	=	cub3D
CC		=	clang
SRC		=	cub3d.c get_next_line.c get_next_line_utils.c utils_basic.c utils_color.c store_map.c \
			utils_parsing.c security.c verification_map.c utils_initialize_struct_map.c hook.c \
			minimap.c moving.c verification_texture.c screenshot.c utils_mlx.c put_column_image.c \
			utils_store_map.c utils_raycasting.c sprite.c clean_exit.c utils_bonus.c
HEADER	=	cub3d.h
OBJ 	=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror #-fsanitize=address
MLX_DIR	=	mlx
MLX		=	libmlx.dylib
BONUS	=	-D BONUS=1

all: $(NAME)

$(NAME): mlx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l $(MLX_DIR)
	install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)

mlx:
	make -C $(MLX_DIR) 

%.o: %.c $(MLX_DIR)/$(MLX) $(HEADER)
	$(CC) $(CFLAGS) -I $(MLX_DIR) -c $< -o $@

bonus: CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address -D BONUS=1

bonus: mlx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l $(MLX_DIR)
	install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re mlx bonus
