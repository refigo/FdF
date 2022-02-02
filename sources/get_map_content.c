/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_content.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:35:09 by mgo               #+#    #+#             */
/*   Updated: 2022/02/02 17:34:04 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	transfer_hex_to_denary(int *num, char hex)
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

static int	atoi_hexa_color(char *hexa_color)
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

static int	add_element_to_stack(t_list **stack, t_element *each_element)
{
	t_list	*new;

	new = ft_lstnew(each_element);
	if (!new)
		return (false);
	ft_lstadd_front(stack, new);
	return (true);
}

static void	parse_map_line(t_map *map, char **tmp_line_splitted, t_list **stack)
{
	t_element	*each_element;
	char		**tmp_element_splitted;
	int			i;

	i = -1;
	while (tmp_line_splitted[++i])
	{
		tmp_element_splitted = ft_split(tmp_line_splitted[i], ',');
		if (!tmp_element_splitted)
			exit_perror();
		each_element = calloc(1, sizeof(t_element));
		if (!each_element)
			exit_perror();
		each_element->altitude = ft_atoi(tmp_element_splitted[0]);
		if (tmp_element_splitted[1])
			each_element->color = atoi_hexa_color(tmp_element_splitted[1]);
		else
			each_element->color = -1;
		add_element_to_stack(stack, each_element);
		mgo_free_2ptr(tmp_element_splitted);
	}
	if (!(map->width))
		map->width = i;
}

void	set_map_content_in_stack(t_map *map)
{
	int		fd_map;
	char	*tmp_line;
	char	**tmp_line_splitted;
	t_list	*stack;

	stack = NULL;
	fd_map = open(map->file, O_RDONLY);
	if (fd_map == -1)
		exit_perror();
	tmp_line = NULL;
	while (get_next_line(fd_map, &tmp_line) != -1 && tmp_line)
	{
		tmp_line_splitted = ft_split(tmp_line, ' ');
		if (!tmp_line_splitted)
			exit_perror();
		parse_map_line(map, tmp_line_splitted, &stack);
		mgo_free_2ptr(tmp_line_splitted);
		free(tmp_line);
		tmp_line = NULL;
		(map->height)++;
	}
	close(fd_map);
	map->stack_element = stack;
}
