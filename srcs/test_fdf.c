#include "fdf.h"
#include "color.h"

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

// test each element content 
void	test_element_splitted(t_element *element)
{
	printf("Start --- test_element_splitted\n");

	printf("element->altitude: [%d]\n", element->altitude);
	printf("element->color(decimal): [%d]\n", element->color);
	printf("element->color(hexa): [%x]\n", element->color);
	
	printf("Done --- test_element_splitted\n");
}

// test stack
static void	print_stack(void *content)
{
	t_element	*element;

	element = (t_element *)content;
	if (element->color != -1)
	{
		printf("element->altitude: [%d]\n", element->altitude);
		printf("element->color: [%x]\n", element->color);
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
		printf("%d->[ ", i);
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

	printf("map->stack list size: [%d]\n", ft_lstsize(map->stack_element));
	printf("map->width: [%d]\n", map->width);
	printf("map->height: [%d]\n", map->height);
	printf("map->max_altitude: [%d]\n", map->max_altitude);
	printf("map->min_altitude: [%d]\n", map->min_altitude);

	printf("Done --- test_map\n");
}

void	test_mlx_win(t_fdf *fdf)
{
	int	*img;
	int	i;
	int	j;

	printf("test mlx win\n");

	img = (int *)(fdf->data_addr);
	i = -1;
	while (++i < WIN_HEIGHT)
	{
		j = -1;
		while (++j < WIN_WIDTH)
		{
			if (i % 2 == 1)
				img[(i * WIN_WIDTH) + j] = CLR_MAIN_SCRN_BG;
			else
				img[(i * WIN_WIDTH) + j] = 0;//0xEC4B27;
		}
	}
}

