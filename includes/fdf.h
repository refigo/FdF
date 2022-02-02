/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:36:41 by mgo               #+#    #+#             */
/*   Updated: 2022/02/02 16:18:07 by mgo              ###   ########.fr       */
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
# include "key_macos.h"

/* 
 *	open, read, write, close
 *	malloc, free
 *	perror, strerror
 *	exit
 *	math library
 *	miniLibX library
 */

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

/*
// rotate
# define KEY_W 13
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2

// zoom, translate
# define KEY_UP 126
# define KEY_LEFT 123
# define KEY_DOWN 125
# define KEY_RIGHT 124
*/

typedef enum e_bool
{
	false,
	true
}			t_bool;

typedef enum e_projection
{
	ISOMETRIC,
	PARALLEL
}			t_projection;

/*
 * value == altitude -> z
 * horizontal position == axis -> width
 * vertical position == ordinate -> height
 */
typedef struct s_map
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

typedef struct s_element
{
	int		altitude;
	int		color;
}				t_element;

// todo: modify
typedef struct s_view
{
	int				zoom;
	double			alpha;
	double			beta;
	double			gamma;
	t_projection	projection;
	int				x_offset;
	int				y_offset;
	double			altitude_divisor;
}				t_view;

typedef struct s_point
{
	int	x_coord;
	int	y_coord;
	int	z_coord;
	int	color;
}				t_point;

typedef struct s_pixel
{
	int	x;
	int	y;
}				t_pixel;

typedef struct s_fdf
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

// parse_map.c
t_map	*parse_map(char *file);

// get_map_content.c
void	set_map_content_in_stack(t_map *map);

// draw.c
void	draw_fdf(t_fdf *fdf);

// draw_line_bresenham.c
void	draw_line_bresenham(t_fdf *fdf, t_point *start, t_point *dest);

// point_project_view.c
t_point	*set_and_project_point(t_fdf *fdf, int x_coord, int y_coord);
t_point	*set_point(t_fdf *fdf, int x_coord, int y_coord);
t_point	*project_point(t_fdf *fdf, t_point *point);
void	set_isometric(int *x_coord, int *y_coord, int z_coord);

// rotate.c
void	set_isometric(int *x_coord, int *y_coord, int z_coord);
void	rotate_x_axis(int *y_coord, int *z_coord, double alpha);
void	rotate_y_axis(int *x_coord, int *z_coord, double beta);
void	rotate_z_axis(int *x_coord, int *y_coord, double gamma);

// pixel.c
void	put_pixel(t_fdf *fdf, t_pixel *pixel, int color);
int		get_pixel_color(t_pixel current, t_pixel *delta, \
			t_point *start, t_point *dest);
int		get_lerp(int start, int dest, double ratio);

// key_control.c
void	control_fdf(t_fdf *fdf);
int		key_press(int keycode, void *param);
int		exit_when_closing_win(void *param);

// handle_view.c
void	handle_zoom(int key, t_fdf *fdf);
void	handle_offset(int key, t_fdf *fdf);
void	handle_altitude_divisor(int key, t_fdf *fdf);
void	handle_rotate(int key, t_fdf *fdf);
void	handle_projection(int key, t_fdf *fdf);

// utils.c
double	get_ratio(int start, int dest, int current);
int		get_less(int first, int second);
void	put_pixel(t_fdf *fdf, t_pixel *pixel, int color);

// exit.c
void	exit_error_2msg(char *msg1, char *msg2);
void	exit_perror(void);

// test_fdf.c
void	test_line_splitted(char **line_splitted);
void	test_point_splitted(t_point *point);
void	test_stack(t_list *stack);
void	test_map(t_map *map);
void	test_mlx_win(t_fdf *fdf);

#endif
