/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/01/19 15:31:40 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_str_code(char *str, int code)
{
	if (str)
		ft_putstr_fd(str, 1);
	exit(code);
	// todo: using errno
}

int	get_map_content(t_map *map)
{
	char	*buf_line;
	char	**buf_split;
	char	**buf_point;
	int		fd_map;
	int		i;
	t_point	*point;

	fd_map = open(map->name, O_RDONLY);
	//todo: exception
	while (get_next_line(fd_map, &buf_line) == 1)
	{
		buf_split = ft_split(buf_line, ' ');
		//todo: exception
		free(buf_line);
		i = -1;
		while (buf_split[++i])
		{
			buf_point = ft_split(buf_split[i], ',');
			//todo: exception
			point = calloc(1, sizeof(t_point));
			point->z = ft_atoi(buf_point[0]);
			point->color = ft_atoi(buf_point[1]);
			// put into stack or queue
			ft_lstnew(point);
			mgo_free_2ptr(buf_point);
		}
		mgo_free_2ptr(buf_split);
		if (!(map->width))
			map->width = i;
		(map->height)++;
	}
	return (0);
}

void	parse_map(char *file)
{
	t_map	*map;

	// get file name
	/*
	if (ft_strnstr(file, ".fdf", ft_strlen(file)))
		printf("yes\n");
	else
		printf("no\n");
	printf("map: [%s]\n", file);
	*/
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_str_code("malloc failed!\n", 1);
	map->file = file;
	get_content_content(map);
	//set_map_array(map);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;

	if (argc != 2)
		exit_str_code("argument number is wrong!\n", 1);
	parse_map(argv[1]);
	//set_mlx();
	//draw_fdf();
	//handle_fdf();
	//mlx_loop(p_mlx);
	return (0);
}

