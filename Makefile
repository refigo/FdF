
NAME	=	test.out
CC		=	gcc

all:
	$(CC) ./srcs/*.c -L./lib/minilibx_macos -lmlx -framework OpenGL -framework AppKit

test:
	$(CC) toy_mlx.c -L./lib/minilibx_macos -lmlx -framework OpenGL -framework AppKit

