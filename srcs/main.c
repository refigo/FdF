/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/01/24 18:14:13 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

// to remove
int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
// to remove

t_map	*parse_map(char *file)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_perror(1);
	// todo: check readable
	map->file = file;
	get_map_content(map);

	printf("map->stack list size: [%d]\n", ft_lstsize(map->stack_element));

	set_map_content_array(map);

	// test map
	test_map(map);
	return (map);
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
	fdf->data_addr = mlx_get_data_addr(fdf->img, &(fdf->bpp), &(fdf->size_line), &(fdf->endian));

	test_mlx_win(fdf);
}

void	set_view(t_fdf *fdf)
{
	t_view	*view;

	view = calloc(1, sizeof(t_view));

	// todo: isometric projection

	fdf->view = view;
}

void	draw_fdf(t_fdf *fdf)
{
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
}

void	handle_fdf(t_fdf *fdf)
{
	// todo: esc to quit
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		exit_str_code("argument number is wrong!\n", 1);
	fdf.map = parse_map(argv[1]);
	init_mlx_win(&fdf);
	set_view(&fdf);
	draw_fdf(&fdf);
	//handle_fdf();
	mlx_loop(fdf.mlx);
	return (0);
}

