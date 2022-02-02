/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:11:10 by mgo               #+#    #+#             */
/*   Updated: 2022/01/31 16:56:27 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

double	get_ratio(int start, int dest, int current)
{
	double	ratio;

	if (start == dest)
		return (1.0);
	ratio = (double)(current - start) / (dest - start);
	return (ratio);
}

int	get_less(int first, int second)
{
	if (first < second)
		return (first);
	else
		return (second);
}

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
