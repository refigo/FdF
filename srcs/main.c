/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/01/28 16:56:02 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// main.c
void	handle_fdf(t_fdf *fdf)
{
	mlx_key_hook(fdf->win, key_press, fdf);
	mlx_hook(fdf->win, 17, 0, exit_when_closing_win, fdf);
}

// to move draw file
void	draw_fdf(t_fdf *fdf)
{
	int	x_coord;
	int	y_coord;

	draw_background(fdf);
	y_coord = -1;
	while (++y_coord < (fdf->map->height))
	{
		x_coord = -1;
		while (++x_coord < (fdf->map->width))
			draw_horizontal_and_vertical_line(fdf, x_coord, y_coord);
	}
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void	init_mlx_win(t_fdf *fdf)
{
	// todo: exit with str
	fdf->mlx = mlx_init();
	if (!(fdf->mlx))
		exit_perror(1);
	fdf->win = mlx_new_window(fdf->mlx, WIN_WIDTH, WIN_HEIGHT, "FdF");
	if (!(fdf->win))
		exit_perror(1);
	fdf->img = mlx_new_image(fdf->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!(fdf->img))
		exit_perror(1);
	fdf->data_addr = mlx_get_data_addr(fdf->img, \
			&(fdf->bpp), &(fdf->size_line), &(fdf->endian));

	// test mlx win
	//test_mlx_win(fdf);
}

t_map	*parse_map(char *file)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_perror(1);
	// todo: check readable
	map->file = file;
	get_map_content(map);

	// check list size
	printf("map->stack list size: [%d]\n", ft_lstsize(map->stack_element));

	set_map_content_array(map);

	// test map
	test_map(map);
	return (map);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		exit_str_code("argument number is wrong!\n", 1);
	fdf.map = parse_map(argv[1]);
	init_mlx_win(&fdf);
	init_view(&fdf);
	draw_fdf(&fdf);
	handle_fdf(&fdf);
	mlx_loop(fdf.mlx);
	return (0);
}
