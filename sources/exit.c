/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 10:36:19 by mgo               #+#    #+#             */
/*   Updated: 2022/02/02 14:44:40 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_error_2msg(char *msg1, char *msg2)
{
	ft_putstr_fd("FdF error: ", 2);
	if (msg1)
		ft_putstr_fd(msg1, 2);
	if (msg2)
		ft_putstr_fd(msg2, 2);
	exit(1);
}

void	exit_perror(void)
{
	perror("FdF error");
	exit(1);
}
