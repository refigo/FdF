/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 13:49:09 by mgo               #+#    #+#             */
/*   Updated: 2022/01/11 12:54:29 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_fdcrnt(t_gnl **st_gnl, t_gnl **crnt_gnl, int fd)
{
	if (!(*st_gnl))
	{
		*st_gnl = malloc(sizeof(t_gnl));
		(*st_gnl)->fd =fd;
		(*st_gnl)->cont = NULL;
		(*st_gnl)->next = NULL;
	}
	*crnt_gnl = *st_gnl;
	while ((*crnt_gnl) && (*crnt_gnl)->fd != fd)
		*crnt_gnl = (*crnt_gnl)->next;
	if (!(*crnt_gnl))
		return (0);
	return (1);
}

void	*del_fdlist(t_gnl **st_gnl, int fd)
{
	t_gnl	*tmp;

	tmp = *st_gnl;
	if (tmp && tmp->fd == fd)
	{
		free(tmp->cont);
		free(tmp);
		*st_gnl = NULL;
	}
	return (NULL);
}

char	*ret_line(t_gnl **st_gnl, t_gnl **crnt, int fd)
{
	char	*line;
	char	*ptr_nl;
	char	*buf;

	ptr_nl = mgo_strchr((*crnt)->cont, '\n');
	if (ptr_nl)
	{
		mgo_strndup(&line, (*crnt)->cont, (ptr_nl - (*crnt)->cont + 1));
		buf = (*crnt)->cont;
		mgo_strndup(&((*crnt)->cont), ptr_nl + 1, mgo_strlen(ptr_nl + 1));
		free(buf);
	}
	else
	{
		mgo_strndup(&line, (*crnt)->cont, mgo_strlen((*crnt)->cont));
		del_fdlist(st_gnl, fd);
	}
	if (line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	static t_gnl	*st_gnl;
	t_gnl			*crnt;
	char			buf[BUFFER_SIZE + 1];
	ssize_t			read_size;

	if (fd < 0 || BUFFER_SIZE <0)
		return (NULL);
	get_fdcrnt(&st_gnl, &crnt, fd);
	read_size = read(fd, buf, BUFFER_SIZE);
	while (read_size >= 0)
	{
		buf[read_size] = '\0';
		if (crnt->cont == NULL)
			mgo_strndup(&(crnt->cont), buf, mgo_strlen(buf));
		else
			mgo_strjoin(&(crnt->cont), buf);
		if (mgo_strchr(crnt->cont, '\n') || read_size == 0)
			break ;
		read_size = read(fd, buf, BUFFER_SIZE);
	}
	if (read_size < 0)
		return (del_fdlist(&st_gnl, fd));
	return (ret_line(&st_gnl, &crnt, fd));
}

