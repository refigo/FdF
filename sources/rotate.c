/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ratate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 11:35:01 by mgo               #+#    #+#             */
/*   Updated: 2022/02/03 13:46:12 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// PI/6 == 30degree == 0.523599rad
void	set_isometric(int *x_coord, int *y_coord, int z_coord)
{
	int		x_prev;
	int		y_prev;

	x_prev = *x_coord;
	y_prev = *y_coord;
	*x_coord = (x_prev - y_prev) * cos(0.523599);
	*y_coord = (x_prev + y_prev) * sin(0.523599) - z_coord;
}

void	rotate_x_axis(int *y_coord, int *z_coord, double alpha)
{
	int	y_prev;

	y_prev = *y_coord;
	*y_coord = (y_prev) * cos(alpha) + (*z_coord) * sin(alpha);
	*z_coord = (-y_prev) * sin(alpha) + (*z_coord) * cos(alpha);
}

void	rotate_y_axis(int *x_coord, int *z_coord, double beta)
{
	int	x_prev;

	x_prev = *x_coord;
	*x_coord = (x_prev) * cos(beta) + (*z_coord) * sin(beta);
	*z_coord = (-x_prev) * sin(beta) + (*z_coord) * cos(beta);
}

void	rotate_z_axis(int *x_coord, int *y_coord, double gamma)
{
	int	x_prev;
	int	y_prev;

	x_prev = *x_coord;
	y_prev = *y_coord;
	*x_coord = (x_prev) * cos(gamma) - (y_prev) * sin(gamma);
	*y_coord = (x_prev) * sin(gamma) + (y_prev) * cos(gamma);
}
