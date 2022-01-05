/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:31:46 by mgo               #+#    #+#             */
/*   Updated: 2022/01/05 14:56:20 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./minilibx_macos/mlx.h"
#include <unistd.h>
#include <stdio.h>

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		*bits_per_pixel;
	int		*size_line;
	int		*endian;
}				t_mlx;

void	draw_pixel(t_mlx *mlx)
{
	int		i;
	double	pos_pixel;

	i = -1;
	while (++i < 255*255*255)
	{
		pos_pixel = i;
		pos_pixel = 500 * (pos_pixel / (255*255*255));
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pos_pixel, pos_pixel, i);
	}
	mlx_string_put(mlx->mlx_ptr, mlx->win_ptr, 250, 250, 255*255, "Hello!");
}

void	draw_img(t_mlx *mlx)
{
	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 150, 150);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 200, 200);
}

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 500, "Hello");
	draw_pixel(&mlx);
	draw_img(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
