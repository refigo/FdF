/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:51:03 by mgo               #+#    #+#             */
/*   Updated: 2022/01/06 16:14:22 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct	s_gnl
{
	int		fd;
	char	*cont;
	void	*next;
}				t_gnl;

// get_next_line.c
char	*get_next_line(int fd);

// get_next_line_utils.c
ssize_t	mgo_strlen(char *str);
int		mgo_strndup(char **dest, char *src, int len);
char	*mgo_strchr(char *str, char chr);
int		mgo_strjoin(char **dest, char *src);

#endif
