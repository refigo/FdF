/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 18:07:05 by mgo               #+#    #+#             */
/*   Updated: 2022/01/31 15:19:46 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	key_press(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keycode == 53)
		exit(0);
	//if (keycode == KEY_W)
		
	return (0);
}

int	exit_when_closing_win(void *param)
{
	(void)param;
	exit(0);
}

void	handle_fdf(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, key_press, fdf);
	mlx_hook(fdf->win, 17, 0, exit_when_closing_win, fdf);
}

