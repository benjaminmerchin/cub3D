NAME	=	cub3D
CC		=	clang
SRC		=	training_mlx_functions.c
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

%.o: %.c $(MLX_DIR)/$(MLX)
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
