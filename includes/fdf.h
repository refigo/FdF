/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 15:36:41 by mgo               #+#    #+#             */
/*   Updated: 2022/01/23 14:39:37 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <errno.h>
# include <stdbool.h>
# include "libft.h"
# include "get_next_line.h"
# include "mlx.h"


/* 
 *	open, read, write, close
 *	malloc, free
 *	perror, strerror
 *	exit
 *	math library
 *	miniLibX library
 */


/*
 * value == altitude -> z
 * horizontal position == axis -> width
 * vertical position == ordinate -> height
 */
typedef struct	s_map
{
	char	*file;
	int		*arr_z;
	int		*arr_color;
	int		width;
	int		height;
}				t_map;

typedef struct	s_point
{
	int		z;
	int		color;
}				t_point;

typedef struct	s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	t_map	*map;

}				t_fdf;

# include "test_fdf.h"

#endif
