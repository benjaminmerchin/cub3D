NAME	=	cub3D
CC		=	clang
SRC		=	cub3d.c get_next_line.c get_next_line_utils.c utils_basic.c utils_color.c store_map.c \
			utils_parsing.c security.c map_verification.c utils_initialize_struct.c
HEADER	=	cub3d.h
OBJ 	=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror
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

bonus: all

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re mlx bonus

#I don't compile the mlx .o where the .c changed again when I do make. Should I fix that ?
