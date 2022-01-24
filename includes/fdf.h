/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:36:41 by mgo               #+#    #+#             */
/*   Updated: 2022/01/24 11:59:56 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <stdbool.h>
# include "libft.h"
# include "mlx.h"

/* 
 *	open, read, write, close
 *	malloc, free
 *	perror, strerror
 *	exit
 *	math library
 *	miniLibX library
 */

/*
 * value == altitude -> z
 * horizontal position == axis -> width
 * vertical position == ordinate -> height
 */
typedef struct	s_map
{
	char	*file;
	t_list	*stack;
	int		*arr_altitude;
	int		*arr_color;
	int		width;
	int		height;
}				t_map;

typedef struct	s_point
{
	int		altitude;
	int		color;
}				t_point;

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	t_map	*map;
}				t_fdf;

// get_map_content.c
void	get_map_content(t_map *map);

// exit.c
void	exit_str_code(char *str, int code);
void	exit_perror(int code_error);

// test_fdf.c
void	test_line_splitted(char **line_splitted);
void	test_point_splitted(t_point *point);
void	test_stack(t_list *stack);
void	test_map(t_map *map);

#endif
