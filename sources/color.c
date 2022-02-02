/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:14:09 by mgo               #+#    #+#             */
/*   Updated: 2022/02/02 18:02:02 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	get_lerp(int start, int dest, double ratio)
{
	int	ret;

	ret = ratio * dest + (1 - ratio) * start;
	return (ret);
}

static int	get_lerp_each_rgb(int start, int dest, double ratio)
{
	int	ret;
	int	mask_1byte;

	mask_1byte = 0xFF;
	ret = get_lerp(start & mask_1byte, dest & mask_1byte, ratio);
	return (ret);
}

int	get_pixel_color(t_pixel current, t_pixel *delta, \
		t_point *start, t_point *dest)
{
	double	ratio;
	int		red;
	int		green;
	int		blue;

	if (start->color == dest->color)
		return (dest->color);
	if (delta->x > delta->y)
		ratio = get_ratio(start->x_coord, dest->x_coord, current.x);
	else
		ratio = get_ratio(start->y_coord, dest->y_coord, current.y);
	red = get_lerp_each_rgb((start->color >> 16), (dest->color >> 16), ratio);
	green = get_lerp_each_rgb((start->color >> 8), (dest->color >> 8), ratio);
	blue = get_lerp_each_rgb((start->color), (dest->color), ratio);
	return ((red << 16) | (green << 8) | blue);
}
