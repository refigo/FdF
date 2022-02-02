/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:07:05 by mgo               #+#    #+#             */
/*   Updated: 2022/02/02 17:59:50 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	key_press(int key, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (key == KEY_ESCAPE)
		exit(0);
	if (key == KEY_W || key == KEY_S)
		handle_zoom(key, fdf);
	if (key == KEY_UP || key == KEY_LEFT \
			|| key == KEY_DOWN || key == KEY_RIGHT)
		handle_offset(key, fdf);
	if (key == KEY_L || key == KEY_H)
		handle_altitude_divisor(key, fdf);
	if (key == KEY_X || key == KEY_Y || key == KEY_Z)
		handle_rotate(key, fdf);
	if (key == KEY_I || key == KEY_P)
		handle_projection(key, fdf);
	return (0);
}

static int	exit_when_closing_win(void *param)
{
	(void)param;
	exit(0);
}

void	control_fdf(t_fdf *fdf)
{
	int	win_button_esc;

	win_button_esc = 17;
	mlx_hook(fdf->win, KEYPRESS, 0, key_press, fdf);
	mlx_hook(fdf->win, win_button_esc, 0, exit_when_closing_win, fdf);
}
