/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/02/03 14:44:22 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	adjust_zoom_according_altitude(t_view *view, t_map *map)
{
	int		max_altitude;
	int		min_altitude;
	int		total_altitude_zoomed;

	max_altitude = map->max_altitude;
	min_altitude = map->min_altitude;
	total_altitude_zoomed = ((max_altitude - min_altitude) * view->zoom);
	if (total_altitude_zoomed >= WIN_HEIGHT)
		view->zoom = WIN_HEIGHT / (max_altitude - min_altitude) * 2 / 3;
}

static void	init_view(t_fdf *fdf)
{
	t_view	*view;

	view = calloc(1, sizeof(t_view));
	view->zoom = get_less((WIN_WIDTH / fdf->map->width / 2), \
						(WIN_HEIGHT / fdf->map->height / 2));
	adjust_zoom_according_altitude(view, fdf->map);
	view->altitude_divisor = 1;
	fdf->view = view;
}

static void	init_mlx_win(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!(fdf->mlx))
		exit_error_2msg("mlx_init error\n", NULL);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!(fdf->win))
		exit_error_2msg("mlx_new_window error\n", NULL);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!(fdf->img))
		exit_error_2msg("mlx_new_image error\n", NULL);
	fdf->data_addr = mlx_get_data_addr(fdf->img, \
			&(fdf->bpp), &(fdf->size_line), &(fdf->endian));
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		exit_error_2msg("argument number is wrong.\n", \
				"Please input one fdf file.\n");
	fdf.map = parse_map(argv[1]);
	init_mlx_win(&fdf);
	init_view(&fdf);
	draw_fdf(&fdf);
	control_fdf(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
