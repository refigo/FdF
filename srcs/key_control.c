/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:07:05 by mgo               #+#    #+#             */
/*   Updated: 2022/01/31 18:05:54 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//# define KEYPRESS 2

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

void	handle_z_divisor(int key, t_fdf *fdf)
{
	if (key == KEY_L)
		(fdf->view->z_divisor)++;
	else if (key == KEY_H)
		(fdf->view->z_divisor)--;
	if (fdf->view->z_divisor == 0)
		fdf->view->z_divisor = 1;
	draw_fdf(fdf);
}

int	key_press(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == 53)
		exit(0);
	if (key == KEY_W || key == KEY_S)
		handle_zoom(key, fdf);
	if (key == KEY_UP || key == KEY_LEFT \
			|| key == KEY_DOWN || key == KEY_RIGHT)
		handle_offset(key, fdf);
	if (key == KEY_L || key == KEY_H)
		handle_z_divisor(key, fdf);
		
	return (0);
}

int	exit_when_closing_win(void *param)
{
	(void)param;
	exit(0);
}

void	handle_fdf(t_fdf *fdf)
{
	//mlx_key_hook(fdf->win, key_press, fdf);
	mlx_hook(fdf->win, KEYPRESS, 0, key_press, fdf);
	mlx_hook(fdf->win, 17, 0, exit_when_closing_win, fdf);
}

