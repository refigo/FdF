/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/01/23 17:07:29 by mgo              ###   ########.fr       */
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

bool	transfer_hex_to_denary(int *num, char hex)
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

int	atoi_hexa_color(char *hexa_color)
{
	int	ret_num;
	int	i;

	ret_num = 0;
	if (!ft_strnstr(hexa_color, "0x", 2))
		return (-1);
	i = 1;
	while (hexa_color[++i])
		if (!transfer_hex_to_denary(&ret_num, hexa_color[i]))
			return (-1);
	return (ret_num);
}

bool	add_point_to_stack(t_list **stack, t_point *map_point)
{
	t_list	*new;

	new = ft_lstnew(map_point);
	if (!new)
		return (false);
	ft_lstadd_front(stack, new);
	return (true);
}

void	parse_map_line(t_map *map, char **tmp_line_splitted, t_list **stack)
{
	t_point	*map_point;
	char	**tmp_point_splitted;
	int		i;

	i = -1;
	while (tmp_line_splitted[++i])
	{
		tmp_point_splitted = ft_split(tmp_line_splitted[i], ',');
		if (!tmp_point_splitted)
			exit_perror(1);
		map_point = calloc(1, sizeof(t_point));
		if (!map_point)
			exit_perror(1);
		map_point->z = ft_atoi(tmp_point_splitted[0]);
		if (tmp_point_splitted[1])
			map_point->color = atoi_hexa_color(tmp_point_splitted[1]);
		else
			map_point->color = -1;

		// test point splitted
		/*
		if (tmp_point_splitted[1])
			test_point_splitted(map_point);
		*/

		// put into stack or queue
		add_point_to_stack(stack, map_point);

		mgo_free_2ptr(tmp_point_splitted);
	}
	if (!(map->width))
		map->width = i;
}

void	get_map_content(t_map *map)
{
	int		fd_map;
	char	*tmp_line;
	char	**tmp_line_splitted;
	t_list	*stack;

	stack = NULL;
	fd_map = open(map->file, O_RDONLY);
	if (fd_map == -1)	// todo?: OPEN_MAX and minus
		exit_perror(1);
	tmp_line = NULL;
	while (get_next_line(fd_map, &tmp_line) != -1 && tmp_line)
	{
		tmp_line_splitted = ft_split(tmp_line, ' ');
		if (!tmp_line_splitted)
			exit_perror(1);

		// test tmp line splitted
		//test_line_splitted(tmp_line_splitted);

		parse_map_line(map, tmp_line_splitted, &stack);
		mgo_free_2ptr(tmp_line_splitted);
		free(tmp_line);
		tmp_line = NULL; // because of abort... but why???
		(map->height)++;
	}
	close(fd_map);

	// test_stack
	test_stack(stack);

	map->stack = stack;
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

	// test map
	test_map(map);
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

