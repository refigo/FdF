/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:14:09 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 18:21:16 by mgo              ###   ########.fr       */
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

int	get_pixel_color(t_pixel current, t_pixel *delta, \
		t_point *start, t_point *dest)
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
