
NAME	=	test.out
CC		=	gcc

all:
	$(CC) test_mlx.c -L./minilibx_macos -lmlx -framework OpenGL -framework AppKit


