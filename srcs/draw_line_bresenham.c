/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_bresenham.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:23:05 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 16:38:21 by mgo              ###   ########.fr       */
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

double	get_ratio(int start, int dest, int current)
{
	double	ratio;

	if (start == dest)
		return (1.0);
	ratio = (double)(current - start) / (dest - start);
	return (ratio);
}

int	get_pixel_color(t_pixel current, t_pixel *delta, t_point *start, t_point *dest)
{
	double	ratio;
	int		ret_color;
	
	if (start->color == dest->color)
		return (dest->color);
	if (delta->x > delta->y)
		ratio = get_ratio(start->x_coord, dest->x_coord, current.x);
	else
		ratio = get_ratio(start->y_coord, dest->y_coord, current.y);
	ret_color = (int)((ratio) * dest->color + (1 - ratio) * start->color);
	return (ret_color);
}

void	determine_direction_one(t_pixel *direction_one, \
			t_point *start, t_point *dest)
{
	if (start->x_coord < dest->x_coord)
		direction_one->x = +1;
	else
		direction_one->x = -1;
	if (start->y_coord < dest->y_coord)
		direction_one->y = +1;
	else
		direction_one->y = -1;
}

void	determine_current_pixel(int *bresen_formula, t_pixel *current, \
			t_pixel delta, t_pixel direction_one)
{
	(current->x) += direction_one.x;
	if (*bresen_formula < 0)
		*bresen_formula += (2 * delta.y);
	else
	{
		*bresen_formula += ((2 * delta.y) - (2 * delta.x));
		(current->y) += direction_one.y;
	}
}

void	draw_low_gradient_line(t_fdf *fdf, t_pixel *delta, \
			t_point *start, t_point *dest)
{
	t_pixel	current;
	t_pixel	direction_one;
	int		bresen_formula;

	current.x = start->x_coord;
	current.y = start->y_coord;
	determine_direction_one(&direction_one, start, dest);
	bresen_formula = ((2 * delta->y) - (delta->x));
	while (current.x != dest->x_coord)
	{
		put_pixel(fdf, &current, get_pixel_color(current, delta, start, dest));
		(current.x) += direction_one.x;
		if (bresen_formula < 0)
			bresen_formula += (2 * delta->y);
		else
		{
			bresen_formula += ((2 * delta->y) - (2 * delta->x));
			(current.y) += direction_one.y;
		}
	}
}

void	draw_high_gradient_line(t_fdf *fdf, t_pixel *delta, \
			t_point *start, t_point *dest)
{
	t_pixel	current;
	t_pixel	direction_one;
	int		bresen_formula;

	current.x = start->x_coord;
	current.y = start->y_coord;
	determine_direction_one(&direction_one, start, dest);
	bresen_formula = ((2 * delta->x) - (delta->y));
	while (current.y != dest->y_coord)
	{
		put_pixel(fdf, &current, get_pixel_color(current, delta, start, dest));
		(current.y) += direction_one.y;
		if (bresen_formula < 0)
			bresen_formula += (2 * delta->x);
		else
		{
			bresen_formula += ((2 * delta->x) - (2 * delta->y));
			(current.x) += direction_one.x;
		}
	}
}

void	draw_line_bresenham(t_fdf *fdf, t_point *start, t_point *dest)
{
	t_pixel	delta;
	t_pixel	current;
	t_pixel	direction_one;
	int		formula;

	delta.x = abs(dest->x_coord - start->x_coord);
	delta.y = abs(dest->y_coord - start->y_coord);
	if (delta.x > delta.y)
		draw_low_gradient_line(fdf, &delta, start, dest);
	else
		draw_high_gradient_line(fdf, &delta, start, dest);
}

