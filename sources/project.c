/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   project.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 18:10:37 by mgo               #+#    #+#             */
/*   Updated: 2022/02/02 18:10:43 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotate_projection(t_fdf *fdf, t_point *point)
{
	rotate_x_axis(&(point->y_coord), &(point->z_coord), fdf->view->alpha);
	rotate_y_axis(&(point->x_coord), &(point->z_coord), fdf->view->beta);
	rotate_z_axis(&(point->x_coord), &(point->y_coord), fdf->view->gamma);
	if (fdf->view->projection == ISOMETRIC)
		set_isometric(&(point->x_coord), &(point->y_coord), point->z_coord);
}

static t_point	*project_point(t_fdf *fdf, t_point *point)
{
	int	diff_abs_max_min_alt;

	point->x_coord -= fdf->map->width / 2;
	point->y_coord -= fdf->map->height / 2;
	point->x_coord *= fdf->view->zoom;
	point->y_coord *= fdf->view->zoom;
	point->z_coord *= (double)fdf->view->zoom / fdf->view->altitude_divisor;
	rotate_projection(fdf, point);
	point->x_coord += WIN_WIDTH / 2 + fdf->view->x_offset * fdf->view->zoom;
	point->y_coord += WIN_HEIGHT / 2 + fdf->view->y_offset * fdf->view->zoom;
	diff_abs_max_min_alt = \
		(abs(fdf->map->max_altitude) - abs(fdf->map->min_altitude));
	point->y_coord += diff_abs_max_min_alt * fdf->view->zoom / 3;
	return (point);
}

static t_point	*set_point(t_fdf *fdf, int x_coord, int y_coord)
{
	t_point	*point;
	t_map	*map;
	int		index_in_array;

	map = fdf->map;
	point = calloc(1, sizeof(t_point));
	if (!point)
		exit_perror();
	point->x_coord = x_coord;
	point->y_coord = y_coord;
	index_in_array = (y_coord * (map->width)) + x_coord;
	point->z_coord = (map->arr_altitude)[index_in_array];
	if ((map->arr_color)[index_in_array] == -1)
		point->color = COLOR_TEAL;
	else
		point->color = map->arr_color[index_in_array];
	return (point);
}

t_point	*set_and_project_point(t_fdf *fdf, int x_coord, int y_coord)
{
	t_point	*point;
	t_point	*projected;

	point = set_point(fdf, x_coord, y_coord);
	projected = project_point(fdf, point);
	return (projected);
}
