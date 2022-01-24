/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_content_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:20:06 by mgo               #+#    #+#             */
/*   Updated: 2022/01/24 12:57:54 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_max_min_altitude(t_map *map, int point_altitude)
{
	if (point_altitude > map->max_altitude)
		map->max_altitude = point_altitude;
	if (point_altitude < map->min_altitude)
		map->min_altitude = point_altitude;
}

static t_point	*pop_point_from_stack(t_list **stack)
{
	t_point	*ret_point;
	t_list	*tmp_node;

	ret_point = (t_point *)((*stack)->content);
	tmp_node = *stack;
	*stack = tmp_node->next;
	free(tmp_node);
	return (ret_point);
}

void	set_map_content_array(t_map *map)
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
		set_max_min_altitude(map, tmp_point->altitude);
		free(tmp_point);
	}
}

