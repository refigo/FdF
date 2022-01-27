/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/06 15:49:20 by mgo               #+#    #+#             */
/*   Updated: 2022/01/06 16:15:57 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	mgo_strlen(char *str)
{
	ssize_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int		mgo_strndup(char **dest, char *src, int len)
{
	int	i;

	*dest = malloc(len + 1);
	i = -1;
	while(src[++i] && len--)
	{
		(*dest)[i] = src[i];
	}
	(*dest)[i] = '\0';
	return (1);
}

char	*mgo_strchr(char *str, char chr)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == chr)
			return (&(str[i]));
	}
	return (NULL);
}

int		mgo_strjoin(char **dest, char *src)
{
	char	*buf;
	int		i;

	buf = malloc(mgo_strlen(*dest) + mgo_strlen(src) + 1);
	i = -1;
	while ((*dest)[++i])
		buf[i] = (*dest)[i];
	while (*src)
	{
		buf[i++] = *(src++);
	}
	buf[i] = '\0';
	free(*dest);
	*dest = buf;
	return (1);
}

