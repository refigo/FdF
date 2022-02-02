/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:36:19 by mgo               #+#    #+#             */
/*   Updated: 2022/01/26 18:18:58 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_str_code(char *str, int code)
{
	if (str)
		ft_putstr_fd(str, 1);
	exit(code);
	// todo: using errno
}

void	exit_perror(int code_error)
{
	perror(0);
	if (!code_error)
		exit(1);
	else
		exit(code_error);
}
