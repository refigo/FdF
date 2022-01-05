/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:31:46 by mgo               #+#    #+#             */
/*   Updated: 2022/01/05 11:59:04 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx_macos/mlx.h"
#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	void	*mlx_ptr;
	void	*mlx_win;

	mlx_ptr = 0;
	mlx_ptr = mlx_init();
	mlx_win = mlx_new_window(mlx_ptr, 500, 500, "Hello");
	printf("mlx_ptr:%p\n", mlx_ptr);
	printf("mlx_win:%p\n", mlx_win);
	mlx_loop(mlx_ptr);
	return (0);
}
