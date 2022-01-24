# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/19 13:30:25 by mgo               #+#    #+#              #
#    Updated: 2022/01/24 13:26:47 by mgo              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	fdf
CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror
CDEBUG		=	-fsanitize=address -g
RM			=	rm -rf

INC_LINK	=	-I./includes/
LIBFT		=	-L./lib/libft -lft
LIBMLX		=	-L./lib/minilibx_macos -lmlx -framework OpenGL -framework AppKit

SRC_PATH	=	./srcs/
SRC_LIST	=	main.c \
				get_map_content.c \
				set_map_content_array.c \
				exit.c \
				test_fdf.c
SRC			=	$(addprefix $(SRC_PATH), $(SRC_LIST))

OBJ_PATH	=	./objs/
OBJ_LIST	=	$(SRC_LIST:.c=.o)
OBJ			=	$(addprefix $(OBJ_PATH), $(OBJ_LIST))

$(NAME)	:	$(OBJ) libft libmlx
	$(CC) $(CDEBUG) $(OBJ) $(INC_LINK) $(LIBFT) $(LIBMLX) -o $(NAME)

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
	@mkdir $(OBJ_PATH) 2> /dev/null || true
	@$(CC) $(CDEBUG) $(CFLAGS) $(INC_LINK) -c $< -o $@

libft	:
	make -C ./lib/libft all

libmlx	:
	make -C ./lib/minilibx_macos all

all		:	$(NAME)

clean	:
	@make -C ./lib/libft clean
	@make -C ./lib/minilibx_macos clean
	$(RM) $(OBJ_PATH)

fclean	: clean
	@make -C ./lib/libft fclean
	$(RM) $(NAME)

re	:	fclean all


test	:
	$(CC) $(OBJ) $(INC_LINK) $(LIBFT) $(LIBMLX) -o $(NAME)

test_mlx	:
	$(CC) toy_mlx.c -I./includes/ -L./lib/minilibx_macos -lmlx -framework OpenGL -framework AppKit

.PHONY	:	all clean fclean re
