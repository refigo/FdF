/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/01/23 14:42:44 by mgo              ###   ########.fr       */
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

// to remove
int	is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
			|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	transfer_hex_to_denary(int *num, char hex)
{
	const char	*hexa_digits = "0123456789ABCDEF";
	char		upper_hex;
	int			i;

	upper_hex = ft_toupper(hex);
	i = -1;
	while (hexa_digits[++i])
	{
		if (hexa_digits[i] == upper_hex)
		{
			(*num) = ((*num) * 16) + i;
			return (true);
		}
	}
	return (false);
}

int	atoi_hexa_color(char *str)
{
	int	ret_num;
	int	i;

	ret_num = 0;
	if (!ft_strnstr(str, "0x", 2))
		return (-1);
	i = 1;
	while (str[++i])
		if (!transfer_hex_to_denary(&ret_num, str[i]))
			return (-1);
	return (ret_num);
}

int	get_map_content(t_map *map)
{
	char	*tmp_line;
	char	**tmp_line_splitted;
	char	**tmp_point_splitted;
	int		fd_map;
	int		i;
	t_point	*point;

	fd_map = open(map->file, O_RDONLY);
	if (fd_map == -1)	// OPEN_MAX and minus
		exit_perror(1);
	tmp_line = NULL;
	get_next_line(fd_map, &tmp_line);
	while (tmp_line)
	{
		tmp_line_splitted = ft_split(tmp_line, ' ');
		if (!tmp_line_splitted)
			exit_perror(1);

		test_line_splitted(tmp_line_splitted);	// test tmp split

		i = -1;
		while (tmp_line_splitted[++i])
		{
			tmp_point_splitted = ft_split(tmp_line_splitted[i], ',');
			//todo: exception
			point = calloc(1, sizeof(t_point));
			point->z = ft_atoi(tmp_point_splitted[0]);
			if (tmp_point_splitted[1])
				point->color = atoi_hexa_color(tmp_point_splitted[1]);
			else
				point->color = -1;
			// test point splitted
			if (tmp_point_splitted[1])
				test_point_splitted(point);

			// put into stack or queue
			//ft_lstnew(point);
			mgo_free_2ptr(tmp_point_splitted);
		}
		mgo_free_2ptr(tmp_line_splitted);
		if (!(map->width))
			map->width = i;
		(map->height)++;

		free(tmp_line);
		tmp_line = NULL; // because of abort... but why???
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

