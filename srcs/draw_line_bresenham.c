/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bresenham.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:23:05 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 14:10:01 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_pixel(t_fdf *fdf, t_pixel *pixel, int color)
{
	int	*img;
	int	x;
	int	y;

	img = (int *)(fdf->data_addr);
	x = pixel->x;
	y = pixel->y;
	if ((0 <= x && x < WIN_WIDTH) && (0 <= y && y < WIN_HEIGHT))
		img[(y * WIN_WIDTH) + x] = color;
}

int	get_pixel_color(t_point *current, t_point *start, t_point *dest)
{
	return (0);
}

void	determine_direction(t_pixel *direction, t_point *start, t_point *dest)
{
	if (start->x_coord < dest->x_coord)
		direction->x = +1;
	else
		direction->x = -1;
	if (start->y_coord < dest->y_coord)
		direction->y = +1;
	else
		direction->y = -1;
}

void	draw_line_bresenham(t_fdf *fdf, t_point *start, t_point *dest)
{
	t_pixel	delta;
	t_pixel	current;
	t_pixel	direction;
	int		formula;

	delta.x = abs(dest->x_coord - start->x_coord);
	delta.y = abs(dest->y_coord - start->y_coord);
	current.x = start->x_coord;
	current.y = start->y_coord;
	determine_direction(&direction, start, dest);
	if (delta.x > delta.y)
	{
		formula = 2 * delta.y - delta.x;
		while (current.x != dest->x_coord)
		{
			put_pixel(fdf, &current, CLR_TEXT);
			// todo: get_pixel_color(current, delta, start, dest));
			if (direction.x > 0)
				(current.x)++;
			else
				(current.x)--;
			if (formula < 0)
				formula = formula + 2 * delta.y;
			else
			{
				formula = formula + 2 * delta.y - 2 * delta.x;
				if (direction.y >0)
					(current.y)++;
				else
					(current.y)--;
			}
		}
	}
	else
	{
		formula = 2 * delta.x - delta.y;
		while (current.y != dest->y_coord)
		{
			put_pixel(fdf, &current, CLR_TEXT);
					//get_pixel_color(current, delta, start, dest));
			if (direction.y > 0)
				(current.y)++;
			else
				(current.y)--;
			if (formula < 0)
				formula = formula + 2 * delta.x;
			else
			{
				formula = formula + 2 * delta.x - 2 * delta.y;
				if (direction.x >0)
					(current.x)++;
				else
					(current.x)--;
			}
		}
	}
}

