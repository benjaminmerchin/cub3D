NAME	=	cub3D
CC		=	clang
SRC		=	cub3d.c get_next_line.c get_next_line_utils.c utils_basic.c utils_color.c store_map.c \
			utils_parsing.c security.c verification_map.c utils_initialize_struct_map.c hook.c \
			minimap.c moving.c verification_texture.c screenshot.c utils_mlx.c put_column_image.c \
			utils_store_map.c utils_raycasting.c sprite.c clean_exit.c
SRC_BON	=	cub3d.c get_next_line.c get_next_line_utils.c utils_basic.c utils_color.c store_map.c \
			utils_parsing.c security.c verification_map.c utils_initialize_struct_map.c hook.c \
			minimap.c moving.c verification_texture.c screenshot.c utils_mlx.c put_column_image.c \
			utils_store_map.c utils_raycasting.c sprite.c clean_exit.c
HEADER	=	cub3d.h
OBJ 	=	$(SRC:.c=.o)
OBJ_BON	=	$(SRC_BON:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -fsanitize=address
MLX_DIR	=	mlx
MLX		=	libmlx.dylib

all: $(NAME)

$(NAME): mlx $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l $(MLX_DIR)
	install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)

mlx:
	make -C $(MLX_DIR) 

%.o: %.c $(MLX_DIR)/$(MLX) $(HEADER)
	$(CC) $(CFLAGS) -I $(MLX_DIR) -c $< -o $@

bonus: mlx $(OBJ_BON)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ_BON) -L $(MLX_DIR) -l $(MLX_DIR)
	install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)

clean:
	rm -f $(OBJ) $(OBJ_BON)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re mlx bonus
