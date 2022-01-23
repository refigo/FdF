#include "fdf.h"

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

void	test_point_splitted(t_point *point)
{
	printf("Start --- test_point_splitted\n");

	printf("point->z: [%d]\n", point->z);
	printf("point->color(decimal): [%d]\n", point->color);
	printf("point->color(hexa): [%x]\n", point->color);
	
	printf("Done --- test_point_splitted\n");
}

// test stack

