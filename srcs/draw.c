/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:12:03 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 14:02:57 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	draw_horizontal_line(t_fdf *fdf, int x_coord, int y_coord)
{
	t_point	*projected;
	t_point	*projected_next;

	projected = set_and_project_point(fdf, x_coord, y_coord);
	projected_next = set_and_project_point(fdf, x_coord + 1, y_coord);
	draw_line_bresenham(fdf, projected, projected_next);
}

static void	draw_vertical_line(t_fdf *fdf, int x_coord, int y_coord)
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
	int		*img;
	t_pixel	pixel;

	img = (int *)(fdf->data_addr);
	pixel.y = -1;
	while (++(pixel.y) < WIN_HEIGHT)
	{
		pixel.x = -1;
		while (++(pixel.x) < WIN_WIDTH)
			put_pixel(fdf, &pixel, COLOR_BACKGROUND);
	}
}

