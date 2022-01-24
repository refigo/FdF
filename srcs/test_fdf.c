#include "fdf.h"

// test each line content
void	test_line_splitted(char **line_splitted)
{
	int	i;

	printf("Start --- test_line_splitted:\n");

	i = -1;
	while (line_splitted[++i])
	{
		printf("[%s] ", line_splitted[i]);
	}

	printf("\nDone --- test_line_splitted\n");
}

// test each point content 
void	test_point_splitted(t_point *point)
{
	printf("Start --- test_point_splitted\n");

	printf("point->altitude: [%d]\n", point->altitude);
	printf("point->color(decimal): [%d]\n", point->color);
	printf("point->color(hexa): [%x]\n", point->color);
	
	printf("Done --- test_point_splitted\n");
}

// test stack
static void	print_stack(void *content)
{
	t_point	*point;

	point = (t_point *)content;
	if (point->color != -1)
	{
		printf("point->altitude: [%d]\n", point->altitude);
		printf("point->color: [%x]\n", point->color);
	}
}

void	test_stack(t_list *stack)
{
	printf("Start --- test_stack\n");

	//printf("stack list size: [%d]\n", ft_lstsize(stack));
	ft_lstiter(stack, print_stack);

	printf("Done --- test_stack\n");
}

void	test_array(t_map *map, int *array)
{
	int	i;
	int	j;

	printf("Start --- test_array\n");
	i = -1;
	while (++i < map->height)
	{
		printf("%d->[", i);
		j = -1;
		while (++j < map->width)
		{
			printf("%d ", array[(i * map->width) + j]);
		}
		printf("](%d)\n", j);
	}
	printf("Done --- test_array\n");
}

// test map
void	test_map(t_map *map)
{
	printf("Start --- test_map\n");

	//test_stack(map->stack);
	printf("map->arr_altitude\n");
	test_array(map, map->arr_altitude);
	//printf("map->arr_color\n");
	//test_array(map, map->arr_color);

	printf("map->stack list size: [%d]\n", ft_lstsize(map->stack));
	printf("map->width: [%d]\n", map->width);
	printf("map->height: [%d]\n", map->height);

	printf("Done --- test_map\n");
}

