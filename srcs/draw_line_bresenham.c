/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bresenham.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:23:05 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 11:26:22 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

