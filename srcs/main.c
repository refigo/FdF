/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:21:17 by mgo               #+#    #+#             */
/*   Updated: 2022/01/24 12:12:50 by mgo              ###   ########.fr       */
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

t_point	*pop_point_from_stack(t_list **stack)
{
	t_point	*ret_point;
	t_list	*tmp_node;

	ret_point = (t_point *)((*stack)->content);
	tmp_node = *stack;
	*stack = tmp_node->next;
	free(tmp_node);
	return (ret_point);
}

void	set_map_array(t_map *map)
{
	t_point	*tmp_point;
	int		i;

	map->arr_altitude = calloc((map->width * map->height), sizeof(int));
	if (!(map->arr_altitude))
		exit_perror(1);
	map->arr_color = calloc((map->width * map->height), sizeof(int));
	if (!(map->arr_color))
		exit_perror(1);
	i = (map->width * map->height);
	while (--i >= 0)
	{
		tmp_point = pop_point_from_stack(&(map->stack));
		map->arr_altitude[i] = tmp_point->altitude;
		map->arr_color[i] = tmp_point->color;
		free(tmp_point);
	}
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

	printf("map->stack list size: [%d]\n", ft_lstsize(map->stack));

	set_map_array(map);

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
	//set_mlx(fdf);
	//draw_fdf();
	//handle_fdf();
	//mlx_loop(p_mlx);
	return (0);
}

