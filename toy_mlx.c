/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/05 11:31:46 by mgo               #+#    #+#             */
/*   Updated: 2022/01/06 12:12:54 by mgo              ###   ########.fr       */
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
	int		bits_per_pixel;
	int		size_line;
	int		endian;
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
	int	*img_data;
	int	i;

	mlx->img_ptr = mlx_new_image(mlx->mlx_ptr, 150, 150);
	img_data = (int *)mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endian);
	printf("let's get specifics\n");
	i = (mlx->size_line) / 4;
	img_data[i+30] = 0xFFFFFF;
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ptr, 300, 300);
	printf("img_data[%d]: %x\n", i, img_data[i]);
	printf("bits_per_pixel: %d\n", mlx->bits_per_pixel);
	printf("size_line: %d\n", mlx->size_line);
	printf("endian: %d\n",  mlx->endian);

}

int	key_hook(int keycode, void *mlx)
{
	printf("keycode: %d\n", keycode);
	return (0);
}

int	mouse_hook(int button, int x, int y, void *mlx)
{
	printf("button: %d\n", button);
	printf("coordinates: (%d, %d)\n", x, y);
	return (0);
}

int	expose_hook(void *mlx)
{
	printf("in expose hook\n");
	return (0);
}

int	main(void)
{
	t_mlx	mlx;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 500, 500, "Hello");
	draw_pixel(&mlx);
	draw_img(&mlx);
	mlx_key_hook(mlx.win_ptr, &key_hook, &mlx);
	mlx_mouse_hook(mlx.win_ptr, &mouse_hook, &mlx);
	mlx_expose_hook(mlx.win_ptr, &expose_hook, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
