/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_view.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:50:11 by mgo               #+#    #+#             */
/*   Updated: 2022/02/02 15:51:55 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	handle_zoom(int key, t_fdf *fdf)
{
	if (key == KEY_W)
		(fdf->view->zoom)++;
	else if (key == KEY_S)
		(fdf->view->zoom)--;
	if (fdf->view->zoom < 1)
		fdf->view->zoom = 1;
	draw_fdf(fdf);
}

void	handle_offset(int key, t_fdf *fdf)
{
	if (key == KEY_UP)
		(fdf->view->y_offset)++;
	else if (key == KEY_DOWN)
		(fdf->view->y_offset)--;
	else if (key == KEY_LEFT)
		(fdf->view->x_offset)++;
	else if (key == KEY_RIGHT)
		(fdf->view->x_offset)--;
	draw_fdf(fdf);
}

void	handle_altitude_divisor(int key, t_fdf *fdf)
{
	if (key == KEY_L)
		(fdf->view->altitude_divisor)++;
	else if (key == KEY_H)
		(fdf->view->altitude_divisor)--;
	if (fdf->view->altitude_divisor == 0)
		fdf->view->altitude_divisor = 1;
	draw_fdf(fdf);
}

void	handle_rotate(int key, t_fdf *fdf)
{
	if (key == KEY_X)
		(fdf->view->alpha) += 0.1;
	else if (key == KEY_Y)
		(fdf->view->beta) += 0.1;
	else if (key == KEY_Z)
		(fdf->view->gamma) += 0.1;
	draw_fdf(fdf);
}

void	handle_projection(int key, t_fdf *fdf)
{
	(fdf->view->alpha) = 0;
	(fdf->view->beta) = 0;
	(fdf->view->gamma) = 0;
	if (key == KEY_I)
		(fdf->view->projection) = ISOMETRIC;
	else if (key == KEY_P)
		(fdf->view->projection) = PARALLEL;
	draw_fdf(fdf);
}
