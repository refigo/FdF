/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_map_content_array.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 12:20:06 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 18:21:50 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_max_min_altitude(t_map *map, int element_altitude)
{
	if (element_altitude > map->max_altitude)
		map->max_altitude = element_altitude;
	if (element_altitude < map->min_altitude)
		map->min_altitude = element_altitude;
}

static t_element	*pop_element_from_stack(t_list **stack)
{
	t_element	*ret_element;
	t_list		*tmp_node;

	ret_element = (t_element *)((*stack)->content);
	tmp_node = *stack;
	*stack = tmp_node->next;
	free(tmp_node);
	return (ret_element);
}

void	set_map_content_array(t_map *map)
{
	t_element	*tmp_element;
	int			i;

	map->arr_altitude = calloc((map->width * map->height), sizeof(int));
	if (!(map->arr_altitude))
		exit_perror(1);
	map->arr_color = calloc((map->width * map->height), sizeof(int));
	if (!(map->arr_color))
		exit_perror(1);
	i = (map->width * map->height);
	while (--i >= 0)
	{
		tmp_element = pop_element_from_stack(&(map->stack_element));
		map->arr_altitude[i] = tmp_element->altitude;
		map->arr_color[i] = tmp_element->color;
		set_max_min_altitude(map, tmp_element->altitude);
		free(tmp_element);
	}
}
