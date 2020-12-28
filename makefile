NAME	=	cub3D
CC		=	clang
SRC		=	tuto.c
OBJ 	=	$(SRC:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror
MLX_DIR	=	mlx
MLX		=	libmlx.dylib

all: mlx $(NAME)

mlx:
	make -C $(MLX_DIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L $(MLX_DIR) -l $(MLX_DIR)
	install_name_tool -change $(MLX) @loader_path/$(MLX_DIR)/$(MLX) $(NAME)

%.o: %.c $(MLX_DIR)/$(MLX)
	$(CC) $(CFLAGS) -I $(MLX_DIR) -c $< -o $@

bonus: all

clean:
	rm -f $(OBJ)
	make clean -C $(MLX_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all re mlx

#I don't compile the mlx .o where the .c changed again when I do make. Should I fix that ?
#fusion of the L and l flag ?
#my $name rule doesn't work if the mlx is not done yet. is it fine ?
