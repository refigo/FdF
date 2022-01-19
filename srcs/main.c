#include "fdf.h"

void	exit_str_code(char *str, int code)
{
	if (str)
		ft_putstr_fd(str, 1);
	exit(code);
}

int	get_map(t_map *map)
{
	char	*buf_line;
	char	**buf_split;
	char	**buf_point;
	int		fd_map;
	int		i;
	t_point	*point;

	fd_map = open(map->name, O_RDONLY);
	//todo: exception
	while (1 == get_next_line(fd_map, &buf_line))
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

int	parse_map(char *arg_map)
{
	t_map	*map;

	if (ft_strnstr(arg_map, ".fdf", ft_strlen(arg_map)))
		printf("yes\n");
	else
		printf("no\n");
	printf("map: [%s]\n", arg_map);
	//map = ft_calloc(1, sizeof(t_map));
	//todo: exception
	//map->name = arg_map;
	//get_map(map);
	
	return (1);
}

int	main(int argc, char **argv)
{
	t_fdf	fdf;
	if (argc != 2)
		exit_str_code("argument number is wrong!\n", 1);
	parse_map(argv[1]);
	//set_mlx();
	//draw_fdf();
	// todo: handling minilibX
	//handle_fdf();
	//mlx_loop(p_mlx);
	return (0);
}
