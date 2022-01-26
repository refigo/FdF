/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_project_view.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:17:27 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 12:08:08 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

// project.c

// 30deg x pi/180 = 0.5236rad
void	set_isometric(int *x_coord, int *y_coord, int z_coord)
{
	int	x_prev;
	int	y_prev;

	x_prev = *x_coord;
	y_prev = *y_coord;
	*x_coord = (x_prev - y_prev) * cos(0.5236);
	*y_coord = (x_prev + y_prev) * sin(0.5236) - z_coord;
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

