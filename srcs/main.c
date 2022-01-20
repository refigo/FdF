/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/01/20 18:48:44 by mgo              ###   ########.fr       */
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

void	exit_perror(int code_error)
{
	perror(0);
	if (!code_error)
		exit(1);
	else
		exit(code_error);
}

int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	is_operator(char c)
{

	if (c == '+' || c == '-')
		return (1);
	return (0);
}

void	set_sign(char c, int *sign)
{
	if (c == '-')
		*sign *= -1;
}
	
int	mgo_atoi_hexa(char *str, int base)
{
	long long	ret_num;
	int			sign;
	int			i;

	i = 0;
	while (is_whitespace(str[i]))
		i++;
	sign = 1;
	if (is_operator(str[i]))
		set_sign(str[i], &sign);
	// todo: transfer hexa to decimal
			
	return (ret_num);
}

int	get_map_content(t_map *map)
{
	char	*tmp_line;
	char	**tmp_split;
	char	**tmp_point_split;
	int		fd_map;
	int		i;
	t_point	*point;

	fd_map = open(map->file, O_RDONLY);
	if (fd_map == -1)
		exit_perror(1);
	tmp_line = 0;
	get_next_line(fd_map, &tmp_line);
	while (tmp_line)
	{
		tmp_split = ft_split(tmp_line, ' ');
		if (!tmp_split)
			exit_perror(1);
		free(tmp_line);
		tmp_line = NULL; // because of abort... but why???
		test_tmp_split(tmp_split);

		i = -1;
		while (tmp_split[++i])
		{
			tmp_point_split = ft_split(tmp_split[i], ',');
			//todo: exception
			point = calloc(1, sizeof(t_point));
			point->z = ft_atoi(tmp_point_split[0]);
			point->color = ft_atoi_base(tmp_point_split[1]);
			// put into stack or queue
			ft_lstnew(point);
			mgo_free_2ptr(tmp_point_split);
		}
		mgo_free_2ptr(tmp_split);
		if (!(map->width))
			map->width = i;
		(map->height)++;

		get_next_line(fd_map, &tmp_line);
	}
	close(fd_map);
	return (0);
}

void	parse_map(char *file)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_perror(1);
	map->file = file;
	get_map_content(map);
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

