#include "fdf.h"

void	test_tmp_split(char **buf_split)
{
	int	i;

	printf("test_buf_split:\n");
	i = -1;
	while (buf_split[++i])
	{
		printf("[%s] ", buf_split[i]);
	}
	printf("\ntest_buf_split is done.\n");
}



