/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 16:42:12 by mgo               #+#    #+#             */
/*   Updated: 2022/02/03 14:46:09 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_max_min_altitude(t_map *map, int element_altitude)
{
	if (element_altitude > (map->max_altitude))
		(map->max_altitude) = element_altitude;
	if (element_altitude < (map->min_altitude))
		(map->min_altitude) = element_altitude;
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

static void	set_map_content_array(t_map *map)
{
	t_element	*tmp_element;
	int			i;

	map->arr_altitude = calloc((map->width * map->height), sizeof(int));
	if (!(map->arr_altitude))
		exit_perror();
	map->arr_color = calloc((map->width * map->height), sizeof(int));
	if (!(map->arr_color))
		exit_perror();
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

t_map	*parse_map(char *file)
{
	t_map	*map;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		exit_perror();
	map->file = file;
	set_map_content_in_stack(map);
	set_map_content_array(map);
	return (map);
}
