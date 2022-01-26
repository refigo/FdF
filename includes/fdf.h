/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:36:41 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 11:50:38 by mgo              ###   ########.fr       */
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
# include "libft.h"
# include "mlx.h"
# include "color.h"

/* 
 *	open, read, write, close
 *	malloc, free
 *	perror, strerror
 *	exit
 *	math library
 *	miniLibX library
 */

# define WIN_WIDTH 1280
# define WIN_HEIGHT 1280

typedef enum	e_bool
{
	false,
	true
}				t_bool;

/*
 * value == altitude -> z
 * horizontal position == axis -> width
 * vertical position == ordinate -> height
 */
typedef struct	s_map
{
	char	*file;
	t_list	*stack_element;
	int		*arr_altitude;
	int		*arr_color;
	int		width;
	int		height;
	int		max_altitude;
	int		min_altitude;
}				t_map;

typedef struct	s_element
{
	int		altitude;
	int		color;
}				t_element;

// todo: modify
typedef struct	s_view
{
	int		zoom;
	double	alpha;
	double	beta;
	double	gamma;
	int		x_offset;
	int		y_offset;
	float	z_divisor;

}				t_view;

typedef struct	s_point
{
	int	x_coord;
	int	y_coord;
	int	z_coord;
	int	color;
}				t_point;

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;
	t_map	*map;
	t_view	*view;
}				t_fdf;

// main.c
t_map	*parse_map(char *file);
void	init_mlx_win(t_fdf *fdf);
void	draw_fdf(t_fdf *fdf);
void	handle_fdf(t_fdf *fdf);

// get_map_content.c
void	get_map_content(t_map *map);

// set_map_content_array.c
void	set_map_content_array(t_map *map);

// draw.c
void	draw_background(t_fdf *fdf);
void	draw_horizontal_and_vertical_line(t_fdf *fdf, int x_coord, int y_coord);

// draw_line_bresenham.c
void	draw_line_bresenham(t_fdf *fdf, t_point *start, t_point *dest);
int		get_pixel_color(t_point *current, t_point *start, t_point *dest);
void	put_pixel(t_fdf *fdf, int x, int y, int color);

// point_project_view.c
t_point	*set_and_project_point(t_fdf *fdf, int x_coord, int y_coord);
t_point	*set_point(t_fdf *fdf, int x_coord, int y_coord);
t_point	*project_point(t_fdf *fdf, t_point *point);
void	set_isometric(int *x_coord, int *y_coord, int z_coord);
void	init_view(t_fdf *fdf);
int		get_less(int num_1, int num_2);

// exit.c
void	exit_str_code(char *str, int code);
void	exit_perror(int code_error);

// test_fdf.c
void	test_line_splitted(char **line_splitted);
void	test_point_splitted(t_point *point);
void	test_stack(t_list *stack);
void	test_map(t_map *map);
void	test_mlx_win(t_fdf *fdf);

#endif
