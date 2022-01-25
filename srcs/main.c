/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/01/25 18:53:00 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "color.h"

int	get_less(int num_1, int num_2)
{
	if (num_1 < num_2)
		return (num_1);
	else
		return (num_2);
}

void	init_view(t_fdf *fdf)
{
	t_view	*view;

	view = calloc(1, sizeof(t_view));
	// todo: isometric projection
	view->zoom = get_less((WIN_WIDTH / fdf->map->width / 2), \
			(WIN_HEIGHT / fdf->map->height / 2));
	printf("zoom: [%d]\n", view->zoom);
	fdf->view = view;
}

void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	int	*img;

	img = (int *)(fdf->data_addr);
	if ((0 <= x && x < WIN_WIDTH) && (0 <= y && y < WIN_HEIGHT))
		img[(y * WIN_WIDTH) + x] = color;
}

int	get_pixel_color(t_point *current, t_point *start, t_point *dest)
{
	return (0);
}


void	draw_line_bresenham(t_fdf *fdf, t_point *start, t_point *dest)
{
	t_point	current;
	t_point	delta;
	int		formula;

	delta.x_coord = abs(dest->x_coord - start->x_coord);
	delta.y_coord = abs(dest->y_coord - start->y_coord);
	current.x_coord = start->x_coord;
	current.y_coord = start->y_coord;
	if (delta.x_coord > delta.y_coord)
	{
		formula = 2 * delta.y_coord - delta.x_coord;
		while (current.x_coord <= dest->x_coord)
		{
			put_pixel(fdf, current.x_coord, current.y_coord, CLR_TEXT);
					//get_pixel_color(current, delta, start, dest));
			(current.x_coord)++;
			if (formula < 0)
				formula = formula + 2 * delta.y_coord;
			else
			{
				formula = formula + 2 * delta.y_coord - 2 * delta.x_coord;
				(current.y_coord)++;
			}
		}
	}
	else
	{
		formula = 2 * delta.x_coord - delta.y_coord;
		while (current.y_coord <= dest->y_coord)
		{
			put_pixel(fdf, current.x_coord, current.y_coord, CLR_TEXT);
					//get_pixel_color(current, delta, start, dest));
			(current.y_coord)++;
			if (formula < 0)
				formula = formula + 2 * delta.x_coord;
			else
			{
				formula = formula + 2 * delta.x_coord - 2 * delta.y_coord;
				(current.x_coord)++;
			}
		}
	}
}

// project.c

// 30deg x pi/180 = 0.5236rad
void	set_isometric(int *x_coord, int *y_coord, int z_coord)
{
	int	x_prev;
	int	y_prev;

	x_prev = *x_coord;
	y_prev = *y_coord;
	*x_coord = (x_prev - y_prev) * cos(0.5236);
	*y_coord = (x_prev - y_prev) * sin(0.5236) - z_coord;
}

t_point	*project_point(t_fdf *fdf, t_point *point)
{
	point->x_coord *= fdf->view->zoom;
	point->y_coord *= fdf->view->zoom;
	point->z_coord *= fdf->view->zoom;
	point->x_coord -= (fdf->map->width * fdf->view->zoom) / 2;
	point->y_coord -= (fdf->map->height * fdf->view->zoom) / 2;
	set_isometric(&(point->x_coord), &(point->y_coord), point->z_coord);
	point->x_coord += WIN_WIDTH / 2;
	point->y_coord += WIN_HEIGHT / 2;
	//point->y_coord += fdf->map->height * 2 / 5;
	return (point);
}

// point.c
t_point	*set_point(t_fdf *fdf, int x_coord, int y_coord)
{
	t_point	*point;
	t_map	*map;
	int		index_in_array;

	map = fdf->map;
	point = calloc(1, sizeof(t_point));
	if (!point)
		exit_perror(1);
	point->x_coord = x_coord;
	point->y_coord = y_coord;
	index_in_array = (y_coord * (map->width)) + x_coord;
	point->z_coord = (map->arr_altitude)[index_in_array];
	if ((map->arr_color)[index_in_array] == -1)
		point->color = CLR_TEXT;	// get_basic_color
	else
		point->color = map->arr_color[index_in_array];
	return (point);
}

t_point	*set_and_project_point(t_fdf *fdf, int x_coord, int y_coord)
{
	t_point	*projected;

	projected = project_point(fdf, set_point(fdf, x_coord, y_coord));
	return (projected);
}

// drawing.c
void	draw_horizontal_line(t_fdf *fdf, int x_coord, int y_coord)
{
	t_point	*projected;
	t_point	*projected_next;

	projected = set_and_project_point(fdf, x_coord, y_coord);
	projected_next = set_and_project_point(fdf, x_coord + 1, y_coord);
	draw_line_bresenham(fdf, projected, projected_next);
}

void	draw_vertical_line(t_fdf *fdf, int x_coord, int y_coord)
{
	t_point	*projected;
	t_point	*projected_next;

	projected = set_and_project_point(fdf, x_coord, y_coord);
	projected_next = set_and_project_point(fdf, x_coord, y_coord + 1);
	draw_line_bresenham(fdf, projected, projected_next);
}

void	draw_horizontal_and_vertical_line(t_fdf *fdf, int x_coord, int y_coord)
{
	if (x_coord < fdf->map->width - 1)
		draw_horizontal_line(fdf, x_coord, y_coord);
	if (y_coord < fdf->map->height - 1)
		draw_vertical_line(fdf, x_coord, y_coord);
}

void	draw_background(t_fdf *fdf)
{
	int	*img;
	int	i;
	int	j;

	img = (int *)(fdf->data_addr);
	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
			put_pixel(fdf, j, i, COLOR_BACKGROUND);
	}
}

// main.c
void	handle_fdf(t_fdf *fdf)
{
	// todo: esc to quit
}

void	draw_fdf(t_fdf *fdf)
{
	int	x_coord;
	int	y_coord;

	draw_background(fdf);
	y_coord = -1;
	while (++y_coord < (fdf->map->height))
	{
		x_coord = -1;
		while (++x_coord < (fdf->map->width))
			draw_horizontal_and_vertical_line(fdf, x_coord, y_coord);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void	init_mlx_win(t_fdf *fdf)
{
	// todo: exit with str
	fdf->mlx = mlx_init();
	if (!(fdf->mlx))
		exit_perror(1);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!(fdf->win))
		exit_perror(1);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!(fdf->img))
		exit_perror(1);
	fdf->data_addr = mlx_get_data_addr(fdf->img, \
			&(fdf->bpp), &(fdf->size_line), &(fdf->endian));

	// test mlx win
	//test_mlx_win(fdf);
}

t_map	*parse_map(char *file)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_perror(1);
	// todo: check readable
	map->file = file;
	get_map_content(map);

	printf("map->stack list size: [%d]\n", ft_lstsize(map->stack_element));

	set_map_content_array(map);

	// test map
	test_map(map);
	return (map);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		exit_str_code("argument number is wrong!\n", 1);
	fdf.map = parse_map(argv[1]);
	init_mlx_win(&fdf);
	init_view(&fdf);
	draw_fdf(&fdf);
	//handle_fdf();
	mlx_loop(fdf.mlx);
	return (0);
}

